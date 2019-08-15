/**
* Authors: sharkgoesmad
*
* Copyright (c) 2019 SteelSeries ApS. All Rights Reserved.
*/
#pragma once


#include "SSGS_Gradient.h"
#include "SSGS_ColorGradient.generated.h"


USTRUCT( BlueprintType, meta = ( Category = "Gamesense|Types" ) )
struct STEELSERIESGAMESENSE_API FSSGS_ColorGradient {

    GENERATED_BODY()
    
    UPROPERTY( EditAnywhere, BlueprintReadWrite ) FSSGS_Gradient gradient;

};
