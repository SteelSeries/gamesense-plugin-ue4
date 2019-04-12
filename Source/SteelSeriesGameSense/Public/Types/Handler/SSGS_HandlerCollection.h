/**
* Authors: sharkgoesmad
*
* Copyright (c) 2019 SteelSeries ApS. All Rights Reserved.
*/
#pragma once


#include "Types/Illumination/SSGS_ColorEffectSpecificationStatic.h"
#include "Types/Illumination/SSGS_ColorEffectSpecificationGradient.h"
#include "Types/Illumination/SSGS_ColorEffectSpecificationRanges.h"
#include "Types/Haptics/SSGS_TactilePatternSpecificationStatic.h"
#include "Types/Haptics/SSGS_TactilePatternSpecificationRanges.h"
#include "SSGS_HandlerColor.h"
#include "SSGS_HandlerTactile.h"
#include "SSGS_HandlerCollection.generated.h"


UCLASS( BlueprintType, meta = ( Category = "Gamesense|Types" ) )
class STEELSERIESGAMESENSE_API USSGS_HandlerCollection : public UObject, public FSSGS_JsonConvertable {

    GENERATED_BODY()

public:

    ~USSGS_HandlerCollection();

    void AddColorHandler( const FSSGS_HandlerColor& handler );
    void AddTactileHandler( const FSSGS_HandlerTactile& handler );

    /**
    * Properly constructs USSGS_HandlerCollection object.
    *
    * @return   USSGS_HandlerCollection object.
    */
    UFUNCTION( BlueprintCallable, Category = "Gamesense|HandlerCollection" )
    static USSGS_HandlerCollection* MakeHandlerCollection();

    /**
    * Add a color handler to the collection.
    *
    * @param	deviceZone Illumination device-zone structure.
    * @param	mode The mode of illumination on the color zone.
    * @param	colorSpec Specification of color effect (static, gradient, ranges).
    * @param	rateSpec Specification of the flasher for the specified zone. Optional.
    */
    UFUNCTION( BlueprintCallable, Category = "Gamesense|HandlerCollection" )
    void AddColorHandler( UPARAM( DisplayName = "Device-Zone" )             const FSSGS_IlluminationDeviceZone& deviceZone,
                          UPARAM( DisplayName = "Illumination Mode" )       ESSGS_IlluminationMode mode,
                          UPARAM( DisplayName = "ColorSpecification", ref ) USSGS_ColorEffectSpecification*& colorSpec,
                          UPARAM( DisplayName = "RateSpecification" )       USSGS_RateSpecification* rateSpec = nullptr );
    /**
    * Add a color handler to the collection.
    *
    * @param	deviceZone Tactile device-zone structure.
    * @param	pattern Specification of tactile pattern (static, ranges).
    * @param	rateSpec Specifies frequency and repeat count for the tactile pattern. Optional.
    */
    UFUNCTION( BlueprintCallable, Category = "Gamesense|HandlerCollection" )
    void AddTactileHandler( UPARAM( DisplayName = "Device-Zone" )               const FSSGS_TactileDeviceZone& deviceZone,
                            UPARAM( DisplayName = "PatternSpecification", ref ) USSGS_TactilePatternSpecification*& pattern,
                            UPARAM( DisplayName = "RateSpecification" )         USSGS_RateSpecification* rate = nullptr );

    TSharedPtr< FJsonValue > Convert() const;

private:

    TArray< FSSGS_HandlerColor > _colorHandlers;
    TArray< FSSGS_HandlerTactile > _tactileHandlers;

};