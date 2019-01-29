#include "SSGS_ClientPrivate.h"
#include "SSGS_Misc.h"

#include <functional>

#include "Async/Async.h"
#include "RunnableThread.h"
#include "FileHelper.h"
#include "JsonUtilities.h"
#include "Http.h"


DEFINE_LOG_CATEGORY( SSGS_Client );
#define LOG( lvl, format, ... ) UE_LOG( SSGS_Client, lvl, format, ##__VA_ARGS__ )


namespace ssgs {


FString _dummy;

/**
* Base for message classes.
*/
struct _i_queue_msg_ {
    //_i_queue_msg_() {};
    virtual ~_i_queue_msg_() {}
    virtual bool IsCritical() { return true; }
    virtual const FString& GetUri() { return _dummy; }
  
    virtual FSSGS_JsonConvertable* GetConvertable() { return nullptr; }
    FString GetJsonString() {
        FString payload;

        FSSGS_JsonConvertable* pConvertable = GetConvertable();
        if ( !pConvertable ) {
            LOG( Error, TEXT( "Could not obtain FSSGS_JsonConvertable: Invalid message type" ) );
            return payload;
        }

        TSharedPtr< FJsonValue > pJsonValue = pConvertable->Convert();
        if ( !pJsonValue.IsValid() ) {
            LOG( Error, TEXT( "Could not convert message" ) );
            return payload;
        }

        if ( pJsonValue->Type != EJson::Object ) {
            LOG( Error, TEXT( "Message did not convert to an object" ) );
            return payload;
        }

        TSharedRef< TJsonWriter< TCHAR > > pWriter = TJsonWriterFactory< TCHAR >::Create( &payload, 0 );
        if ( !FJsonSerializer::Serialize( pJsonValue, TEXT( "" ), pWriter ) ) {
            LOG( Error, TEXT( "Could not serialize message" ) );
        }

        return payload;
    }
};

/**
* Tags to quickly identify a message type.
*/
enum _queue_msg_tag_ {
    qmt_invalid = 0,
    qmt_game_metadata,
    qmt_register_game_event,
    qmt_bind_game_event,
    qmt_game_event,
    qmt_game_heartbeat,
    qmt_remove_game_event,
    qmt_remove_game
};

/**
* Enumerate endpoint names.
*/
FString ENDPOINT_INVALID( TEXT( "invalid" ) );
FString ENDPOINT_GAME_METADATA( TEXT( "game_metadata" ) );
FString ENDPOINT_REGISTER_GAME_EVENT( TEXT( "register_game_event" ) );
FString ENDPOINT_BIND_GAME_EVENT( TEXT( "bind_game_event" ) );
FString ENDPOINT_GAME_EVENT( TEXT( "game_event" ) );
FString ENDPOINT_GAME_HEARTBEAT( TEXT( "game_heartbeat" ) );
FString ENDPOINT_REMOVE_GAME_EVENT(  TEXT( "remove_game_event" ) );
FString ENDPOINT_REMOVE_GAME( TEXT( "remove_game" ) );

/**
* Template for all the messages.
*/
template < _queue_msg_tag_ msgTag, typename T, const FString& endpoint, bool critical >
struct _queue_msg_ : public _i_queue_msg_ {
    static FString _uri;
    static const _queue_msg_tag_ tag = msgTag;
    T data;
    static void setBaseUri( const FString& base ) {
        _uri = base + TEXT( "/" ) + *endpoint;
    }

    bool IsCritical() { return critical; }
    const FString& GetUri() { return _uri; }
    FSSGS_JsonConvertable* GetConvertable() { return ( FSSGS_JsonConvertable* )&data; }

    _queue_msg_< msgTag, T, endpoint, critical >() {};
    _queue_msg_< msgTag, T, endpoint, critical >( const T& v ) : data( v ) {}
};

#define DECL_QUEUE_MSG(tag,type,endpoint,critical,name) \
    typedef _queue_msg_< tag, type, endpoint, critical > name; \
    template<> FString _queue_msg_< tag, type, endpoint, critical >::_uri("");

/**
* Declare message types.
*/
DECL_QUEUE_MSG( qmt_invalid, FSSGS_JsonConvertable, ENDPOINT_INVALID, false, _msg_invalid_ )
DECL_QUEUE_MSG( qmt_game_metadata, FSSGS_GameInfo, ENDPOINT_GAME_METADATA, true, _msg_register_game_ )
DECL_QUEUE_MSG( qmt_register_game_event, FSSGS_EventInfo, ENDPOINT_REGISTER_GAME_EVENT, true, _msg_register_event_ )
DECL_QUEUE_MSG( qmt_bind_game_event, FSSGS_EventBinding, ENDPOINT_BIND_GAME_EVENT, true, _msg_bind_event_ )
DECL_QUEUE_MSG( qmt_game_event, FSSGS_EventUpdate, ENDPOINT_GAME_EVENT, false, _msg_send_event_ )
DECL_QUEUE_MSG( qmt_game_heartbeat, FSSGS_Game, ENDPOINT_GAME_HEARTBEAT, false, _msg_heartbeat_ )
DECL_QUEUE_MSG( qmt_remove_game_event, FSSGS_Event, ENDPOINT_REMOVE_GAME_EVENT, false, _msg_remove_event_ )
DECL_QUEUE_MSG( qmt_remove_game, FSSGS_Game, ENDPOINT_REMOVE_GAME, true, _msg_remove_game_ )

/**
* Reconfigures endpoint URLs with new base address.
*/
void _initializedUris( const FString& base ) {
    _msg_register_game_::setBaseUri( base );
    _msg_register_event_::setBaseUri( base );
    _msg_bind_event_::setBaseUri( base );
    _msg_send_event_::setBaseUri( base );
    _msg_heartbeat_::setBaseUri( base );
    _msg_remove_event_::setBaseUri( base );
    _msg_remove_game_::setBaseUri( base );
}

/**
* Provides single storage for all message types.
* Wraps a union to cleanly and safely manage non-pod types.
*/
class _queue_msg_wrapper_ {

    _queue_msg_tag_ _activeTag = qmt_invalid;
    union _queue_msg_variant_ {
        _msg_invalid_ invalid = _msg_invalid_();
        _msg_register_game_ register_game;
        _msg_register_event_ register_event;
        _msg_bind_event_ bind_event;
        _msg_send_event_ send_event;
        _msg_heartbeat_ hearbeat;
        _msg_remove_event_ remove_event;
        _msg_remove_game_ remove_game;

#pragma warning(disable:4582)
        _queue_msg_variant_() : invalid() {}
#pragma warning(default:4582)
#pragma warning(disable:4583)
        ~_queue_msg_variant_() {}
#pragma warning(default:4583)
    } _v;


    void _destroyByTag() {
        switch ( _activeTag ) {

        case qmt_invalid: _v.invalid.~_msg_invalid_(); break;
        case qmt_game_metadata: _v.register_game.~_msg_register_game_(); break;
        case qmt_register_game_event: _v.register_event.~_msg_register_event_(); break;
        case qmt_bind_game_event: _v.bind_event.~_msg_bind_event_(); break;
        case qmt_game_event: _v.send_event.~_msg_send_event_(); break;
        case qmt_game_heartbeat: _v.hearbeat.~_msg_heartbeat_(); break;
        case qmt_remove_game_event: _v.remove_event.~_msg_remove_event_(); break;
        case qmt_remove_game: _v.remove_game.~_msg_remove_game_(); break;

        }
    }

    void _assignByTag( _queue_msg_tag_ tag, const _queue_msg_variant_& v ) {
        switch ( tag ) {

        case qmt_invalid: new ( &_v.invalid ) _msg_invalid_( v.invalid ); break;
        case qmt_game_metadata: new ( &_v.register_game ) _msg_register_game_( v.register_game ); break;
        case qmt_register_game_event: new ( &_v.register_event ) _msg_register_event_( v.register_event ); break;
        case qmt_bind_game_event: new ( &_v.bind_event ) _msg_bind_event_( v.bind_event ); break;
        case qmt_game_event: new ( &_v.send_event ) _msg_send_event_( v.send_event ); break;
        case qmt_game_heartbeat: new ( &_v.hearbeat ) _msg_heartbeat_( v.hearbeat ); break;
        case qmt_remove_game_event: new ( &_v.remove_event ) _msg_remove_event_( v.remove_event ); break;
        case qmt_remove_game: new ( &_v.remove_game ) _msg_remove_game_( v.remove_game ); break;

        }

        _activeTag = tag;
    }

public:

    _queue_msg_wrapper_() {}

    _queue_msg_wrapper_( const _queue_msg_wrapper_& other ) {
        _destroyByTag();
        _assignByTag( other._activeTag, other._v );
    }

    template < typename msg_type >
    _queue_msg_wrapper_( const msg_type& v ) :
        _activeTag( msg_type::tag )
    {
        set( v );
    }

#pragma warning(disable:4583)
    ~_queue_msg_wrapper_() {
        _destroyByTag();
    }
#pragma warning(default:4583)

    _queue_msg_wrapper_& operator=( const _queue_msg_wrapper_& rhs ) {
        if ( this != &rhs ) {
            _destroyByTag();
            _assignByTag( rhs._activeTag, rhs._v );
        }

        return *this;
    }

    _queue_msg_wrapper_& operator=( _queue_msg_wrapper_&& rhs ) {
        if ( this != &rhs ) {
            _destroyByTag();
            _assignByTag( rhs._activeTag, rhs._v );
            rhs.reset();
        }

        return *this;
    }

    template < typename msg_type >
    void set( const msg_type& v ) {
        _destroyByTag();
        _activeTag = msg_type::tag;
        new ( &_v ) msg_type( v );
    }

    void reset() {
        set( _msg_invalid_() );
    }

    _i_queue_msg_* get() {
        return reinterpret_cast< _i_queue_msg_* >( &_v );
    }

    bool isValid() {
        return _activeTag != qmt_invalid;
    }

};

/**
* Error indicating message sending failures.
*/
enum _send_msg_err_ {
    smerr_ok = 0,
    smerr_requesttimedout,
    smerr_serverdown,
    smerr_msgillformed,
    smerr_unknown
};

/**
* Client's static resources
*/
Client* Client::_mpInstance = nullptr;
TQueue< _queue_msg_wrapper_, EQueueMode::Mpsc > _msg_queue;
TSharedPtr< TPromise< bool > > _preq_completion;

/**
* Return per platform path to server coreProps.
*/
FString _serverPropsPath() {
#if PLATFORM_WINDOWS
    //"%PROGRAMDATA%/SteelSeries/SteelSeries Engine 3/coreProps.json"
    TCHAR bfr[ _MAX_PATH+1 ];
    FWindowsPlatformMisc::GetEnvironmentVariable( L"PROGRAMDATA", bfr, _MAX_PATH );
    FString programData( bfr );
    return FString( bfr + FString(L"\\SteelSeries\\SteelSeries Engine 3\\coreProps.json") );
#elif PLATFORM_MAC
    return FString( "/Library/Application Support/SteelSeries Engine 3/coreProps.json" );
#else
    return FString();
#endif
}

/**
* Read SSE3 coreProps.
*/
FString _readProps() {
    FString propsPath = _serverPropsPath();
    FString propsJson;

    if ( !FFileHelper::LoadFileToString(propsJson, *propsPath) ) {
        LOG( Error, TEXT("Could not read server props file (\"%s\")"), *propsPath );
    }

    return propsJson;
}

/**
* Obtains and parses GameSense server port.
*/
FString _getServerPort() {
    FString propsJson = _readProps();
    FString port;
    FServerProps props;

    bool success = FJsonObjectConverter::JsonObjectStringToUStruct( propsJson, &props, 0, 0 );

    if ( success ) {
        FString dummy;

        props.address.Split( ":", &dummy, &port, ESearchCase::IgnoreCase, ESearchDir::FromStart );
    }

    return port;
}

/**
* Configures the request with URL, data and common header entries
*/
void _configureRequest( const FHttpRequestPtr& pRequest, const FString& uri, const FString& data ) {

    pRequest->SetVerb( TEXT( "POST" ) );
    pRequest->SetHeader( TEXT( "Content-Type" ), TEXT( "application/json" ) );
    pRequest->SetURL( uri );
    pRequest->SetContentAsString( data );

}

/**
* Request completion delegate. Sets the completion status for our waiting thread.
*/
void _onRequestComplete( FHttpRequestPtr pReq, FHttpResponsePtr pResp, bool completed )
{
    _preq_completion->SetValue( completed );
}

/**
* Configure the request and send it.
*
* @return   Future object that synchronizes with request completion.
*/
TFuture< bool > _sendMsg( const FHttpRequestPtr& request, const FString& uri, const FString& data ){
    // reset the promise
    *_preq_completion = TPromise< bool >();
    TFuture< bool > result = _preq_completion->GetFuture();

    request->OnProcessRequestComplete().BindStatic( &_onRequestComplete );

    _configureRequest( request, uri, data );

    if ( !request->ProcessRequest() ) {
        _preq_completion->SetValue( false );
    }

    return result;
}

/**
* Dispatch a message and wait for it to get processed.
*
* @return   _send_msg_err_ indicating an error kind
*/
_send_msg_err_ _submitMsg( _queue_msg_wrapper_& msg ) {

    _send_msg_err_ err = smerr_unknown;
    _i_queue_msg_* pMsg = msg.get();
    FString data = pMsg->GetJsonString();
    if ( data.IsEmpty() ) {
        return smerr_msgillformed;
    }

    LOG( VeryVerbose, TEXT( "%s" ), *data );

    FHttpRequestPtr request = FHttpModule::Get().CreateRequest();
    TFuture< bool > result = _sendMsg( request, pMsg->GetUri(), data );

    // wait for the request to complete
    result.Get();
    switch ( request->GetStatus() ) {

    case EHttpRequestStatus::Failed:
    case EHttpRequestStatus::Succeeded: {
        FHttpResponsePtr response = request->GetResponse();
        if ( response.IsValid() ) {
            int32 code = response->GetResponseCode();

            switch ( code ) {

            case EHttpResponseCodes::Ok:
                LOG( Verbose, TEXT( "%s" ), *response->GetContentAsString() );
                err = smerr_ok;
                break;

            case EHttpResponseCodes::GatewayTimeout:
                err = smerr_serverdown;
                break;

            case EHttpResponseCodes::BadRequest:
            case EHttpResponseCodes::ServerError:
                LOG( Warning, TEXT( "%s" ), *response->GetContentAsString() );
                err = smerr_msgillformed;
                break;

            default:
                err = smerr_unknown;
                break;
            }
        }

        break;
    }

    case EHttpRequestStatus::Failed_ConnectionError:
        err = smerr_serverdown;
        break;

    default:
        err = smerr_unknown;
        break;

    }

    return err;
}

/**
* Client destructor
*/
Client::~Client()
{}

/**
* Client constructor
*/
Client::Client() :
    _mShouldRun( true ),
    _mClientState( Disabled ),
    _mGameName(),
    _gsWorkerReturnStatus()
{}

/**
* Client's worker thread.
*
* @return 0 on success.
*/
Client::_gsWorkerReturnType_ Client::_gsWorkerFn()
{
    _queue_msg_wrapper_ pendingMsg;
    const float msgCheckInterval = 0.01f;   // 10 ms
    const float serverProbeInterval = 5.0f;   // 5s
    const double maxIdleTimeBeforeHeartbeat = 5.0;   // 5 seconds
    double tLastMsg = FPlatformTime::Seconds();
    double tNow = tLastMsg;
    _mClientState = Probing;
    _preq_completion = TSharedPtr< TPromise< bool > >( new ( std::nothrow ) TPromise< bool >() );

    // Ensure http module is loaded
    FHttpModule::Get();

    // Drop any stale messages
    _msg_queue.Empty();

    LOG( Display, TEXT( "GameSense worker starting" ) );

    while (_mShouldRun) {
        switch ( _mClientState ) {


        case Active: {
            _queue_msg_wrapper_ msg;

            if ( pendingMsg.isValid() ) {

                // try to push through a pending message
                msg = std::move( pendingMsg );

            } else {

                // spin here waiting for messages
                while ( !_msg_queue.Dequeue( msg ) && _mShouldRun ) {
                    FPlatformProcess::Sleep( msgCheckInterval );
                    tNow = FPlatformTime::Seconds();
                    if ( tNow - tLastMsg > maxIdleTimeBeforeHeartbeat && !_mGameName.IsEmpty() ) {
                        // send a heartbeat to the server if its due
                        msg.set( _msg_heartbeat_( FSSGS_Game( _mGameName ) ) );
                        break;
                    }
                }
            }

            if ( !msg.isValid() ) {
                // sanity check
                // silently drop an invalid message
                break;
            }

            _send_msg_err_ err = _submitMsg( msg );
            if ( err == smerr_ok ) {

                // grab current timestamp so that heartbeat is not redundant
                tLastMsg = FPlatformTime::Seconds();

            } else if ( err == smerr_requesttimedout && !_mShouldRun ) {
                // TODO
                break;
            } else if ( err == smerr_serverdown ) {

                LOG( Error, TEXT( "Failed connecting to GameSense server" ) );
                pendingMsg = std::move( msg );
                _mClientState = Probing;
                FPlatformProcess::Sleep( serverProbeInterval );

            } else if ( err == smerr_msgillformed && msg.get()->IsCritical() ) {

                // message that was critically important is not well defined
                // in this case, abort
                LOG( Error, TEXT( "Message ill-formed" ) );
                _mClientState = Disabled;

            } else if ( err == smerr_unknown ) {
                
                // abort
                LOG( Error, TEXT( "Unknown error occurred" ) );
                _mClientState = Disabled;

            }

            break;
        }


        case Probing: {
            
            // obtain GameSense server port
            FString serverPort = _getServerPort();
            if ( serverPort == "" ) {
                // SSE3 not installed or coreprops.json garbled
                // this failure is beyond anything we can do, GameSense will remain disabled
                LOG( Error, TEXT("GameSense server port could not be obtained") );
                _mClientState = Disabled;
            } else {
                // successfully  obtained server port
                _initializedUris( FString( TEXT( "http://127.0.0.1:" ) + serverPort ) );
                _mClientState = Active;

            }

            break;
        }


        case Disabled:
            LOG( Warning, TEXT( "Disabling GameSense client" ) );
            _mShouldRun = false;
            break;


        default:
            LOG( Error, TEXT( "Undefined GameSense client state tranistion" ) );
            _mClientState = Disabled;
            break;

        }
    }

    _preq_completion.Reset();
    _msg_queue.Empty();
    LOG( Display, TEXT("GameSense worker exiting") );
    // TODO report err
    return 0;
}

Client* Client::Instance()
{
    return _mpInstance;
}

bool Client::Initialize()
{
    if ( !_mpInstance ) {
        _mpInstance = new ( std::nothrow ) Client;
        if ( _mpInstance ) {
            // spawn the worker thread
            TFunction< _gsWorkerReturnType_( void ) > fn( std::bind( &Client::_gsWorkerFn, _mpInstance ) );
            _mpInstance->_gsWorkerReturnStatus = AsyncThread( fn ).Share();
        }
    }

    return _mpInstance != nullptr;
}

void Client::Release()
{
    if ( _mpInstance ) {

        // sync with thread exiting
        _mpInstance->_mShouldRun = false;
        _mpInstance->_gsWorkerReturnStatus.Get();

        delete _mpInstance;
        _mpInstance = nullptr;
    }
}

/**
* Client API.
*/
void Client::RegisterGame( const FSSGS_GameInfo& v )
{
    if ( _isDisabled() ) return;

    _mGameName = v.game;
    _msg_queue.Enqueue( _queue_msg_wrapper_( _msg_register_game_( v ) ) );
}

void Client::RegisterEvent( const FSSGS_EventInfo& v )
{
    if ( _isDisabled() ) return;
    _msg_queue.Enqueue( _queue_msg_wrapper_( _msg_register_event_( v ) ) );
}

void Client::BindEvent( const FSSGS_EventBinding& v )
{
    if ( _isDisabled() ) return;
    _msg_queue.Enqueue( _queue_msg_wrapper_( _msg_bind_event_( v ) ) );
}

void Client::SendEvent( const FSSGS_EventUpdate& v )
{
    if ( !_isActive() ) return;
    _msg_queue.Enqueue( _queue_msg_wrapper_( _msg_send_event_( v ) ) );
}

void Client::RemoveEvent( const FSSGS_Event& v )
{
    if ( !_isActive() ) return;
    _msg_queue.Enqueue( _queue_msg_wrapper_( _msg_remove_event_( v ) ) );
}

void Client::RemoveGame( const FSSGS_Game& v )
{
    if ( !_isActive() ) return;
    _msg_queue.Enqueue( _queue_msg_wrapper_( _msg_remove_game_( v ) ) );
}


};
