#pragma once


#include "SSGS_Gradient.generated.h"


USTRUCT( BlueprintType, meta = ( Category = "GameSense|Types" ) )
struct STEELSERIESGAMESENSE_API FSSGS_Gradient {

    GENERATED_BODY()

    UPROPERTY( EditAnywhere, BlueprintReadWrite ) FSSGS_RGB zero;
    UPROPERTY( EditAnywhere, BlueprintReadWrite ) FSSGS_RGB hundred;

};
