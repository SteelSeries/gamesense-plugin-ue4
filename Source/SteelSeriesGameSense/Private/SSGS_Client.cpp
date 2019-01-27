#include "ISteelSeriesGameSense.h"
#include "SSGS_Client.h"
#include "SSGS_ClientPrivate.h"
#include "Types/SSGS_Payload.h"


namespace ssgs {


bool Start()
{
#if STEELSERIESGAMESENSE_SUPPORTED_PLATFORMS
    return Client::Initialize();
#else
    return false;
#endif
}

void Stop()
{
#if STEELSERIESGAMESENSE_SUPPORTED_PLATFORMS
    Client::Release();
#endif
}

void RegisterGame( const FSSGS_GameInfo& v )
{
#if STEELSERIESGAMESENSE_SUPPORTED_PLATFORMS
    Client::Instance()->RegisterGame( v );
#endif
}

void RegisterEvent( const FSSGS_EventInfo& v )
{
#if STEELSERIESGAMESENSE_SUPPORTED_PLATFORMS
    Client::Instance()->RegisterEvent( v );
#endif
}

void BindEvent( const FSSGS_EventBinding& v )
{
#if STEELSERIESGAMESENSE_SUPPORTED_PLATFORMS
    Client::Instance()->BindEvent( v );
#endif
}

void SendEvent( const FSSGS_EventUpdate& v )
{
#if STEELSERIESGAMESENSE_SUPPORTED_PLATFORMS
    Client::Instance()->SendEvent( v );
#endif
}

void RemoveEvent( const FSSGS_Event& v )
{
#if STEELSERIESGAMESENSE_SUPPORTED_PLATFORMS
    Client::Instance()->RemoveEvent( v );
#endif
}

void RemoveGame( const FSSGS_Game& v )
{
#if STEELSERIESGAMESENSE_SUPPORTED_PLATFORMS
    Client::Instance()->RemoveGame( v );
#endif
}


}
