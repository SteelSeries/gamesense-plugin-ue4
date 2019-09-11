/**
* Authors: sharkgoesmad
*
* Copyright (c) 2019 SteelSeries ApS. All Rights Reserved.
*/
#pragma once


#include "SSGS_FrequencyRepeatLimitPair.generated.h"


USTRUCT( BlueprintType, meta = ( Category = "Gamesense|Types" ) )
struct STEELSERIESGAMESENSE_API FSSGS_FrequencyRepeatLimitPair {

    GENERATED_BODY()

    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Mandatory" ) int32 low;
    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Mandatory" ) int32 high;
    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Mandatory" ) int32 frequency;
    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Mandatory" ) int32 repeat_limit;

};
