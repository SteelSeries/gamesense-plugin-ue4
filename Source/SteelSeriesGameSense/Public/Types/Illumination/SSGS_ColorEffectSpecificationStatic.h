/**
* Authors: sharkgoesmad
*
* Copyright (c) 2019 SteelSeries ApS. All Rights Reserved.
*/
#pragma once


#include "SSGS_ColorEffectSpecification.h"
#include "SSGS_RGB.h"
#include "SSGS_ColorEffectSpecificationStatic.generated.h"


UCLASS( BlueprintType, meta = ( Category = "Gamesense|Types" ) )
class STEELSERIESGAMESENSE_API USSGS_ColorEffectSpecificationStatic : public USSGS_ColorEffectSpecification {

    GENERATED_BODY()

public:

    /**
    * Properly constructs USSGS_ColorEffectSpecificationStatic object.
    *
    * @param    color Object specifying RGB components.
    * @return   USSGS_ColorEffectSpecificationStatic object.
    */
    UFUNCTION( BlueprintCallable, BlueprintPure, Category = "Gamesense|ColorEffectSpecification" )
    static USSGS_ColorEffectSpecificationStatic* MakeStaticColorEffect( const FSSGS_RGB& color );

    TSharedPtr< FJsonValue > Convert() const;

    UPROPERTY() FSSGS_RGB color;

};