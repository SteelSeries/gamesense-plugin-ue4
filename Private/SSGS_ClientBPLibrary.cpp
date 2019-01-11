#include "SSGSPrivatePCH.h"


using namespace ssgs;


bool USSGS_ClientBBLibrary::Start()
{
    return Client::Initialize();
}

void USSGS_ClientBBLibrary::Stop()
{
    Client::Release();
}

void USSGS_ClientBBLibrary::RegisterGame( const FString& gameName, const FString& gameDisplayName, SSGS_IconColor iconColor )
{
    Client::Instance()->RegisterGame( FSSGS_GameInfo( gameName,
                                                      gameDisplayName,
                                                      iconColor ) );
}

void USSGS_ClientBBLibrary::RegisterEvent( const FString& gameName, const FString& eventName, int32 minValue, int32 maxValue, SSGS_EventIconId iconId )
{
    Client::Instance()->RegisterEvent( FSSGS_EventInfo( gameName,
                                                        eventName,
                                                        minValue,
                                                        maxValue,
                                                        iconId ) );
}

void USSGS_ClientBBLibrary::BindEvent( const FString& gameName, const FString& eventName, int32 minValue, int32 maxValue, SSGS_EventIconId iconId, USSGS_HandlerCollection* handlers )
{
    Client::Instance()->BindEvent(
        FSSGS_EventBinding( gameName,
                            eventName,
                            minValue,
                            maxValue,
                            iconId,
                            handlers ) );
}

void USSGS_ClientBBLibrary::SendEvent( const FString& gameName, const FString& eventName, int32 value )
{
    Client::Instance()->SendEvent( FSSGS_EventUpdate( gameName,
                                                      eventName,
                                                      FSSGS_EventData{ value } ) );
}

void USSGS_ClientBBLibrary::RemoveEvent( const FString& gameName, const FString& eventName )
{
    Client::Instance()->RemoveEvent( FSSGS_Event{ gameName, eventName } );
}

void USSGS_ClientBBLibrary::RemoveGame( const FString& gameName )
{
    Client::Instance()->RemoveGame( FSSGS_Game{ gameName } );
}

USSGS_RateSpecification* USSGS_ClientBBLibrary::MakeRateSpecification()
{
    return _createUObj< USSGS_RateSpecification >();
}

USSGS_HandlerCollection* USSGS_ClientBBLibrary::MakeHandlerCollection()
{
    return _createUObj< USSGS_HandlerCollection >();
}

USSGS_ColorEffectSpecificationStatic* USSGS_ClientBBLibrary::MakeColorEffectSpecificationStatic()
{
    return _createUObj< USSGS_ColorEffectSpecificationStatic >();
}

USSGS_ColorEffectSpecificationGradient* USSGS_ClientBBLibrary::MakeColorEffectSpecificationGradient()
{
    return _createUObj< USSGS_ColorEffectSpecificationGradient >();
}

USSGS_ColorEffectSpecificationRanges* USSGS_ClientBBLibrary::MakeColorEffectSpecificationRanges()
{
    return _createUObj< USSGS_ColorEffectSpecificationRanges >();
}

USSGS_TactilePatternSpecification* USSGS_ClientBBLibrary::MakeTactilePatternSpecification()
{
    return _createUObj< USSGS_TactilePatternSpecification >();
}
