#include "SSGSPrivatePCH.h"


bool USSGS_ClientBBLibrary::Start()
{
    return ssgs::Client::Initialize();
}

void USSGS_ClientBBLibrary::Stop()
{
    ssgs::Client::Release();
}

void USSGS_ClientBBLibrary::RegisterGame( const FSSGS_GameInfo& v )
{
    ssgs::Client::Instance()->RegisterGame( v );
}

void USSGS_ClientBBLibrary::RegisterEvent( const FSSGS_EventInfo& v )
{
    ssgs::Client::Instance()->RegisterEvent( v );
}

void USSGS_ClientBBLibrary::BindEvent( const FSSGS_EventBinding& v )
{
    ssgs::Client::Instance()->BindEvent( v );
}

void USSGS_ClientBBLibrary::SendEvent( const FSSGS_EventUpdate& v )
{
    ssgs::Client::Instance()->SendEvent( v );
}

void USSGS_ClientBBLibrary::RemoveEvent( const FSSGS_Event& v )
{
    ssgs::Client::Instance()->RemoveEvent( v );
}

void USSGS_ClientBBLibrary::RemoveGame( const FSSGS_Game& v )
{
    ssgs::Client::Instance()->RemoveGame( v );
}


