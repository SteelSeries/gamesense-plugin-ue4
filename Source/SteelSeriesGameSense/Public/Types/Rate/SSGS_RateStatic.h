/**
* Authors: sharkgoesmad
*
* Copyright (c) 2019 SteelSeries ApS. All Rights Reserved.
*/
#pragma once


#include "SSGS_RateStatic.generated.h"


USTRUCT( BlueprintType, meta = ( Category = "Gamesense|Types" ) )
struct STEELSERIESGAMESENSE_API FSSGS_RateStatic {

    GENERATED_BODY()

    UPROPERTY( EditAnywhere, BlueprintReadWrite ) int32 frequency;
    UPROPERTY( EditAnywhere, BlueprintReadWrite ) int32 repeat_limit;

};
