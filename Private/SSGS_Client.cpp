#include "SSGS_PrivatePCH.h"


namespace ssgs {


bool STEELSERIESGAMESENSE_API Start()
{
    return Client::Initialize();
}

void STEELSERIESGAMESENSE_API Stop()
{
    Client::Release();
}

void STEELSERIESGAMESENSE_API RegisterGame( const FSSGS_GameInfo& v )
{
    Client::Instance()->RegisterGame( v );
}

void STEELSERIESGAMESENSE_API RegisterEvent( const FSSGS_EventInfo& v )
{
    Client::Instance()->RegisterEvent( v );
}

void STEELSERIESGAMESENSE_API BindEvent( const FSSGS_EventBinding& v )
{
    Client::Instance()->BindEvent( v );
}

void STEELSERIESGAMESENSE_API SendEvent( const FSSGS_EventUpdate& v )
{
    Client::Instance()->SendEvent( v );
}

void STEELSERIESGAMESENSE_API RemoveEvent( const FSSGS_Event& v )
{
    Client::Instance()->RemoveEvent( v );
}

void STEELSERIESGAMESENSE_API RemoveGame( const FSSGS_Game& v )
{
    Client::Instance()->RemoveGame( v );
}


}
