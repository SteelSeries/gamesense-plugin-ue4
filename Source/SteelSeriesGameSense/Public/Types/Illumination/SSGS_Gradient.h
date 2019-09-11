/**
* Authors: sharkgoesmad
*
* Copyright (c) 2019 SteelSeries ApS. All Rights Reserved.
*/
#pragma once


#include "SSGS_RGB.h"
#include "SSGS_Gradient.generated.h"


USTRUCT( BlueprintType, meta = ( Category = "Gamesense|Types" ) )
struct STEELSERIESGAMESENSE_API FSSGS_Gradient {

    GENERATED_BODY()

    UPROPERTY( EditAnywhere, BlueprintReadWrite, DisplayName = "Start Color", Category="Mandatory" ) FSSGS_RGB zero;
    UPROPERTY( EditAnywhere, BlueprintReadWrite, DisplayName = "End Color", Category="Mandatory" ) FSSGS_RGB hundred;

};
