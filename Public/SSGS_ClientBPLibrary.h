#pragma once


#include "SteelSeriesGameSensePCH.h"
#include "SSGS_Payload.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SSGS_ClientBPLibrary.generated.h"


UCLASS( BlueprintType )
class STEELSERIESGAMESENSE_API USSGS_ClientBBLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:

    UFUNCTION( BlueprintCallable, Category = "GameSense|Client" )
    static bool Start();

    UFUNCTION( BlueprintCallable, Category = "GameSense|Client" )
    static void Stop();

    UFUNCTION( BlueprintCallable, Category = "GameSense|Client" )
    static void RegisterGame( const FString& gameName, const FString& gameDisplayName, SSGS_IconColor iconColor );
    
    UFUNCTION( BlueprintCallable, Category = "GameSense|Client" )
    static void RegisterEvent( const FString& gameName, const FString& eventName, int32 minValue, int32 maxValue, SSGS_EventIconId iconId );
    
    UFUNCTION( BlueprintCallable, Category = "GameSense|Client" )
    static void BindEvent( const FString& gameName, const FString& eventName, int32 minValue, int32 maxValue, SSGS_EventIconId iconId, USSGS_HandlerCollection* handlers );
    
    UFUNCTION( BlueprintCallable, Category = "GameSense|Client" )
    static void SendEvent( const FString& gameName, const FString& eventName, int32 value );
   
    UFUNCTION( BlueprintCallable, Category = "GameSense|Client" )
    static void RemoveEvent( const FString& gameName, const FString& eventName );
    
    UFUNCTION( BlueprintCallable, Category = "GameSense|Client" )
    static void RemoveGame( const FString& gameName );


    // convenience functions

    UFUNCTION( BlueprintCallable, Category = "GameSense|Client" )
    static USSGS_RateSpecification* MakeRateSpecification();

    UFUNCTION( BlueprintCallable, Category = "GameSense|Client" )
    static USSGS_HandlerCollection* MakeHandlerCollection();

    UFUNCTION( BlueprintCallable, Category = "GameSense|Client" )
    static USSGS_ColorEffectSpecificationStatic* MakeColorEffectSpecificationStatic();

    UFUNCTION( BlueprintCallable, Category = "GameSense|Client" )
    static USSGS_ColorEffectSpecificationGradient* MakeColorEffectSpecificationGradient();

    UFUNCTION( BlueprintCallable, Category = "GameSense|Client" )
    static USSGS_ColorEffectSpecificationRanges* MakeColorEffectSpecificationRanges();

    UFUNCTION( BlueprintCallable, Category = "GameSense|Client" )
    static USSGS_TactilePatternSpecification* MakeTactilePatternSpecification();

};
