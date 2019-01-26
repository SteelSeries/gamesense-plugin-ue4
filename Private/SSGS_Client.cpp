#include "SSGS_Client.h"
#include "SSGS_ClientPrivate.h"
#include "Types/SSGS_Payload.h"


namespace ssgs {


bool Start()
{
    return Client::Initialize();
}

void Stop()
{
    Client::Release();
}

void RegisterGame( const FSSGS_GameInfo& v )
{
    Client::Instance()->RegisterGame( v );
}

void RegisterEvent( const FSSGS_EventInfo& v )
{
    Client::Instance()->RegisterEvent( v );
}

void BindEvent( const FSSGS_EventBinding& v )
{
    Client::Instance()->BindEvent( v );
}

void SendEvent( const FSSGS_EventUpdate& v )
{
    Client::Instance()->SendEvent( v );
}

void RemoveEvent( const FSSGS_Event& v )
{
    Client::Instance()->RemoveEvent( v );
}

void RemoveGame( const FSSGS_Game& v )
{
    Client::Instance()->RemoveGame( v );
}


}
