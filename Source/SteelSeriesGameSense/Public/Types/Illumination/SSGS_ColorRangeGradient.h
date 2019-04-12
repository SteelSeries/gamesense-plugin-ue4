/**
* Authors: sharkgoesmad
*
* Copyright (c) 2019 SteelSeries ApS. All Rights Reserved.
*/
#pragma once


#include "SSGS_RGB.h"
#include "SSGS_ColorGradient.h"
#include "SSGS_ColorRangeGradient.generated.h"


USTRUCT( BlueprintType, meta = ( Category = "Gamesense|Types" ) )
struct STEELSERIESGAMESENSE_API FSSGS_ColorRangeGradient {

    GENERATED_BODY()

    FSSGS_ColorRangeGradient() {};
    FSSGS_ColorRangeGradient( int32 low, int32 high, const FSSGS_RGB& zero, const FSSGS_RGB& hundred );

    UPROPERTY( EditAnywhere, BlueprintReadWrite ) int32 low;
    UPROPERTY( EditAnywhere, BlueprintReadWrite ) int32 high;
    UPROPERTY( EditAnywhere, BlueprintReadWrite ) FSSGS_ColorGradient color;

};
