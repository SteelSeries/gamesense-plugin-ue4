#include "SSGSPrivatePCH.h"


using namespace ssgs;


bool USSGS_ClientBPLibrary::Start()
{
    return Client::Initialize();
}

void USSGS_ClientBPLibrary::Stop()
{
    Client::Release();
}

void USSGS_ClientBPLibrary::RegisterGame( const FString& gameName, const FString& gameDisplayName, SSGS_IconColor iconColor )
{
    Client::Instance()->RegisterGame( FSSGS_GameInfo( gameName,
                                                      gameDisplayName,
                                                      iconColor ) );
}

void USSGS_ClientBPLibrary::RegisterEvent( const FString& gameName, const FString& eventName, int32 minValue, int32 maxValue, SSGS_EventIconId iconId )
{
    Client::Instance()->RegisterEvent( FSSGS_EventInfo( gameName,
                                                        eventName,
                                                        minValue,
                                                        maxValue,
                                                        iconId ) );
}

void USSGS_ClientBPLibrary::BindEvent( const FString& gameName, const FString& eventName, int32 minValue, int32 maxValue, SSGS_EventIconId iconId, USSGS_HandlerCollection*& handlers )
{
    Client::Instance()->BindEvent(
        FSSGS_EventBinding( gameName,
                            eventName,
                            minValue,
                            maxValue,
                            iconId,
                            handlers ) );
}

void USSGS_ClientBPLibrary::SendEvent( const FString& gameName, const FString& eventName, int32 value )
{
    Client::Instance()->SendEvent( FSSGS_EventUpdate( gameName,
                                                      eventName,
                                                      FSSGS_EventData{ value } ) );
}

void USSGS_ClientBPLibrary::RemoveEvent( const FString& gameName, const FString& eventName )
{
    Client::Instance()->RemoveEvent( FSSGS_Event{ gameName, eventName } );
}

void USSGS_ClientBPLibrary::RemoveGame( const FString& gameName )
{
    Client::Instance()->RemoveGame( FSSGS_Game{ gameName } );
}

USSGS_RateSpecification* USSGS_ClientBPLibrary::MakeRateSpecification()
{
    return _createUObj< USSGS_RateSpecification >();
}

USSGS_HandlerCollection* USSGS_ClientBPLibrary::MakeHandlerCollection()
{
    return _createUObj< USSGS_HandlerCollection >();
}

USSGS_ColorEffectSpecificationStatic* USSGS_ClientBPLibrary::MakeColorEffectSpecificationStatic()
{
    return _createUObj< USSGS_ColorEffectSpecificationStatic >();
}

USSGS_ColorEffectSpecificationGradient* USSGS_ClientBPLibrary::MakeColorEffectSpecificationGradient()
{
    return _createUObj< USSGS_ColorEffectSpecificationGradient >();
}

USSGS_ColorEffectSpecificationRanges* USSGS_ClientBPLibrary::MakeColorEffectSpecificationRanges()
{
    return _createUObj< USSGS_ColorEffectSpecificationRanges >();
}

USSGS_TactilePatternSpecification* USSGS_ClientBPLibrary::MakeTactilePatternSpecification()
{
    return _createUObj< USSGS_TactilePatternSpecification >();
}
