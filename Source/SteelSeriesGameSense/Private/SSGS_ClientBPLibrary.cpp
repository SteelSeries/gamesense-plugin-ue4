#include "ISteelSeriesGameSense.h"
#include "SSGS_ClientBPLibrary.h"
#include "SSGS_ClientPrivate.h"


using namespace ssgs;


bool USSGS_ClientBPLibrary::Start()
{
#if STEELSERIESGAMESENSE_SUPPORTED_PLATFORMS
    return Client::Initialize();
#else
    return false;
#endif
}

void USSGS_ClientBPLibrary::Stop()
{
#if STEELSERIESGAMESENSE_SUPPORTED_PLATFORMS
    Client::Release();
#endif
}

void USSGS_ClientBPLibrary::RegisterGame( const FString& gameName, const FString& gameDisplayName, ESSGS_IconColor iconColor )
{
#if STEELSERIESGAMESENSE_SUPPORTED_PLATFORMS
    Client::Instance()->RegisterGame( FSSGS_GameInfo( gameName,
                                                      gameDisplayName,
                                                      iconColor ) );
#endif
}

void USSGS_ClientBPLibrary::RegisterEvent( const FString& gameName, const FString& eventName, int32 minValue, int32 maxValue, ESSGS_EventIconId iconId )
{
#if STEELSERIESGAMESENSE_SUPPORTED_PLATFORMS
    Client::Instance()->RegisterEvent( FSSGS_EventInfo( gameName,
                                                        eventName,
                                                        minValue,
                                                        maxValue,
                                                        iconId ) );
#endif
}

void USSGS_ClientBPLibrary::BindEvent( const FString& gameName, const FString& eventName, int32 minValue, int32 maxValue, ESSGS_EventIconId iconId, USSGS_HandlerCollection*& handlers )
{
#if STEELSERIESGAMESENSE_SUPPORTED_PLATFORMS
    Client::Instance()->BindEvent(
        FSSGS_EventBinding( gameName,
                            eventName,
                            minValue,
                            maxValue,
                            iconId,
                            handlers ) );
#endif
}

void USSGS_ClientBPLibrary::SendEvent( const FString& gameName, const FString& eventName, const FSSGS_EventData& data )
{
#if STEELSERIESGAMESENSE_SUPPORTED_PLATFORMS
    Client::Instance()->SendEvent( FSSGS_EventUpdate( gameName,
                                                      eventName,
                                                      data ) );
#endif
}

void USSGS_ClientBPLibrary::RemoveEvent( const FString& gameName, const FString& eventName )
{
#if STEELSERIESGAMESENSE_SUPPORTED_PLATFORMS
    Client::Instance()->RemoveEvent( FSSGS_Event{ gameName, eventName } );
#endif
}

void USSGS_ClientBPLibrary::RemoveGame( const FString& gameName )
{
#if STEELSERIESGAMESENSE_SUPPORTED_PLATFORMS
    Client::Instance()->RemoveGame( FSSGS_Game{ gameName } );
#endif
}
