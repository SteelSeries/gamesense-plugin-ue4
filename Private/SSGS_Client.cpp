#include "SSGSPrivatePCH.h"


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

USSGS_RateSpecification* MakeRateSpecification()
{
    return _createUObj< USSGS_RateSpecification >();
}

USSGS_HandlerCollection* MakeHandlerCollection()
{
    return _createUObj< USSGS_HandlerCollection >();
}

USSGS_ColorEffectSpecificationStatic* MakeColorEffectSpecificationStatic()
{
    return _createUObj< USSGS_ColorEffectSpecificationStatic >();
}

USSGS_ColorEffectSpecificationGradient* MakeColorEffectSpecificationGradient()
{
    return _createUObj< USSGS_ColorEffectSpecificationGradient >();
}

USSGS_ColorEffectSpecificationRanges* MakeColorEffectSpecificationRanges()
{
    return _createUObj< USSGS_ColorEffectSpecificationRanges >();
}

USSGS_TactilePatternSpecificationStatic* MakeTactilePatternSpecificationStatic()
{
    return _createUObj< USSGS_TactilePatternSpecificationStatic >();
}

USSGS_TactilePatternSpecificationRanges* MakeTactilePatternSpecificationRanges()
{
    return _createUObj< USSGS_TactilePatternSpecificationRanges >();
}


}
