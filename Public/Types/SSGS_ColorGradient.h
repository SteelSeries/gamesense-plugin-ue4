#pragma once


#include "SSGS_Gradient.h"
#include "SSGS_ColorGradient.generated.h"


USTRUCT( BlueprintType, meta = ( Category = "GameSense|Types" ) )
struct STEELSERIESGAMESENSE_API FSSGS_ColorGradient {

    GENERATED_BODY()
    
    UPROPERTY( EditAnywhere, BlueprintReadWrite ) FSSGS_Gradient gradient;

};
