/**
* Authors: sharkgoesmad
*
* Copyright (c) 2019 SteelSeries ApS. All Rights Reserved.
*/
#pragma once


#include "SSGS_Frequency.generated.h"


USTRUCT( BlueprintType, meta = ( Category = "Gamesense|Types" ) )
struct STEELSERIESGAMESENSE_API FSSGS_Frequency {

    GENERATED_BODY()

    UPROPERTY( EditAnywhere, BlueprintReadWrite ) int32 low;
    UPROPERTY( EditAnywhere, BlueprintReadWrite ) int32 high;
    UPROPERTY( EditAnywhere, BlueprintReadWrite ) int32 frequency;

};
