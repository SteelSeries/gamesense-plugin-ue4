#pragma once


#include "Types/SSGS_Payload.h"
DECLARE_LOG_CATEGORY_EXTERN( SSGS_Client, Log, All );


namespace ssgs {

// TODO STEELSERIESGAMESENSE_API
class STEELSERIESGAMESENSE_API Client {

    typedef uint32 _gsWorkerReturnType_;

    enum _state_ {
        Probing = 0,
        Active,
        Disabled
    };

public:

    ~Client();

    void RegisterGame( const FSSGS_GameInfo& v );
    void RegisterEvent( const FSSGS_EventInfo& v );
    void BindEvent( const FSSGS_EventBinding& v );
    void SendEvent( const FSSGS_EventUpdate& v );
    void RemoveEvent( const FSSGS_Event& v );
    void RemoveGame( const FSSGS_Game& v );

    static Client* Instance();
    // will set defaults to run RegisterGame msg
    static bool Initialize();
    static void Release();

    void RegisterGame( const FString& gameName, const FString& gameDisplayName, ESSGS_IconColor iconColor ) {
        RegisterGame( FSSGS_GameInfo( gameName, gameDisplayName, iconColor ) );
    }

    void RegisterEvent( const FString& gameName, const FString& eventName, int32 minValue, int32 maxValue, ESSGS_EventIconId iconId ) {
        RegisterEvent( FSSGS_EventInfo{ gameName, eventName, minValue, maxValue, iconId } );
    }

    void BindEvent( const FString& gameName, const FString& eventName, int32 minValue, int32 maxValue, ESSGS_EventIconId iconId, USSGS_HandlerCollection* handlers ) {
        BindEvent( FSSGS_EventBinding( gameName, eventName, minValue, maxValue, iconId, handlers ) );
    }

    void SendEvent( const FString& gameName, const FString& eventName, int32 value ) {
        SendEvent( FSSGS_EventUpdate( gameName, eventName, FSSGS_EventData{ value } ) );
    }

    void RemoveEvent( const FString& gameName, const FString& eventName ) {
        RemoveEvent( FSSGS_Event{ gameName, eventName } );
    }

    void RemoveGame( const FString& gameName ) {
        RemoveGame( FSSGS_Game{ gameName } );
    }

private:

    Client();
    Client( const Client& other ) = delete;
    Client( const Client&& other ) = delete;
    Client& operator=( const Client& rhs ) = delete;
    bool _isActive() { return _mClientState == Active; }
    bool _isDisabled() { return _mClientState == Disabled; }

    _gsWorkerReturnType_ _gsWorkerFn();

private:

    static Client* _mpInstance;

private:

    bool _mShouldRun;
    _state_ _mClientState;
    FString _mGameName;
    TSharedFuture< _gsWorkerReturnType_ > _gsWorkerReturnStatus;

};


}