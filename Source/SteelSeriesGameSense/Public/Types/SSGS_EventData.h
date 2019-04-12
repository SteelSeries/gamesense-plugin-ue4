/**
* Authors: sharkgoesmad
*
* Copyright (c) 2019 SteelSeries ApS. All Rights Reserved.
*/
#pragma once


#include "SSGS_EventData.generated.h"


USTRUCT( BlueprintType, meta = ( Category = "Gamesense|Types" ) )
struct STEELSERIESGAMESENSE_API FSSGS_EventData {

    GENERATED_BODY()

    UPROPERTY( EditAnywhere, BlueprintReadWrite ) int32 value;

};
