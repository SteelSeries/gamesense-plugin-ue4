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
    static void RegisterGame( const FSSGS_GameInfo& v );
    
    UFUNCTION( BlueprintCallable, Category = "GameSense|Client" )
    static void RegisterEvent( const FSSGS_EventInfo& v );
    
    UFUNCTION( BlueprintCallable, Category = "GameSense|Client" )
    static void BindEvent( const FSSGS_EventBinding& v );
    
    UFUNCTION( BlueprintCallable, Category = "GameSense|Client" )
    static void SendEvent( const FSSGS_EventUpdate& v );
   
    UFUNCTION( BlueprintCallable, Category = "GameSense|Client" )
    static void RemoveEvent( const FSSGS_Event& v );
    
    UFUNCTION( BlueprintCallable, Category = "GameSense|Client" )
    static void RemoveGame( const FSSGS_Game& v );

};
