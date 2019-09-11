/**
* Authors: sharkgoesmad
*
* Copyright (c) 2019 SteelSeries ApS. All Rights Reserved.
*/
#pragma once


#include "SSGS_RepeatLimit.generated.h"


USTRUCT( BlueprintType, meta = ( Category = "Gamesense|Types" ) )
struct STEELSERIESGAMESENSE_API FSSGS_RepeatLimit {

    GENERATED_BODY()

    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Mandatory" ) int32 low;
    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Mandatory" ) int32 high;
    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Mandatory" ) int32 repeat_limit;

};
