/**
* Authors: sharkgoesmad
*
* Copyright (c) 2019 SteelSeries ApS. All Rights Reserved.
*/
#pragma once


#include "SSGS_ColorEffectSpecification.h"
#include "SSGS_RGB.h"
#include "SSGS_ColorGradient.h"
#include "SSGS_ColorEffectSpecificationGradient.generated.h"


UCLASS( BlueprintType, meta = ( Category = "Gamesense|Types" ) )
class STEELSERIESGAMESENSE_API USSGS_ColorEffectSpecificationGradient : public USSGS_ColorEffectSpecification {

    GENERATED_BODY()

public:

    /**
    * Properly constructs USSGS_ColorEffectSpecificationGradient object.
    *
    * @param    zero Start color for the gradient.
    * @param    hundred End color for the gradient.
    * @return   USSGS_ColorEffectSpecificationGradient object.
    */
    UFUNCTION( BlueprintCallable, BlueprintPure, Category = "Gamesense|ColorEffectSpecification" )
    static USSGS_ColorEffectSpecificationGradient* MakeGradientColorEffect( UPARAM( DisplayName = "Start Color" ) const FSSGS_RGB& zero, UPARAM( DisplayName = "End Color" ) const FSSGS_RGB& hundred );

    TSharedPtr< FJsonValue > Convert() const;

    UPROPERTY() FSSGS_ColorGradient gradient;

};