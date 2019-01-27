#pragma once


#include "SSGS_RGB.h"
#include "SSGS_Gradient.generated.h"


USTRUCT( BlueprintType, meta = ( Category = "GameSense|Types" ) )
struct STEELSERIESGAMESENSE_API FSSGS_Gradient {

    GENERATED_BODY()

    UPROPERTY( EditAnywhere, BlueprintReadWrite, DisplayName = "Start Color" ) FSSGS_RGB zero;
    UPROPERTY( EditAnywhere, BlueprintReadWrite, DisplayName = "End Color" ) FSSGS_RGB hundred;

};
