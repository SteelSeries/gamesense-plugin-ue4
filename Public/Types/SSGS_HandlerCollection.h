#pragma once


#include "SSGS_HandlerColor.h"
#include "SSGS_HandlerTactile.h"
#include "SSGS_HandlerCollection.generated.h"


UCLASS( BlueprintType, meta = ( Category = "GameSense|Types" ) )
class STEELSERIESGAMESENSE_API USSGS_HandlerCollection : public UObject, public FSSGS_JsonConvertable {

    GENERATED_BODY()

public:

    USSGS_HandlerCollection();
    ~USSGS_HandlerCollection();

    void AddColorHandler( const FSSGS_HandlerColor& handler );
    void AddTactileHandler( const FSSGS_HandlerTactile& handler );

    UFUNCTION( BlueprintCallable, Category = "GameSense|HandlerCollection" )
    static USSGS_HandlerCollection* MakeHandlerCollection();

    UFUNCTION( BlueprintCallable, Category = "GameSense|HandlerCollection" )
    void AddColorHandler( UPARAM( DisplayName = "Device-Zone" )             const FSSGS_IlluminationDeviceZone& deviceZone,
                          UPARAM( DisplayName = "Illumination Mode" )       ESSGS_IlluminationMode mode,
                          UPARAM( DisplayName = "ColorSpecification", ref ) USSGS_ColorEffectSpecification*& colorSpec,
                          UPARAM( DisplayName = "RateSpecification" )       USSGS_RateSpecification* rateSpec = nullptr );

    UFUNCTION( BlueprintCallable, Category = "GameSense|HandlerCollection" )
    void AddTactileHandler( UPARAM( DisplayName = "Device-Zone" )               const FSSGS_TactileDeviceZone& deviceZone,
                            UPARAM( DisplayName = "PatternSpecification", ref ) USSGS_TactilePatternSpecification*& pattern,
                            UPARAM( DisplayName = "RateSpecification" )         USSGS_RateSpecification* rate = nullptr );

    TSharedPtr< FJsonValue > Convert() const;

private:

    TArray< FSSGS_HandlerColor > _colorHandlers;
    TArray< FSSGS_HandlerTactile > _tactileHandlers;

};