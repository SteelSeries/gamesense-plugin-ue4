#pragma once


#include "SSGS_ColorRangeGradient.generated.h"


USTRUCT( BlueprintType, meta = ( Category = "GameSense|Types" ) )
struct STEELSERIESGAMESENSE_API FSSGS_ColorRangeGradient {

    GENERATED_BODY()

    FSSGS_ColorRangeGradient() {};
    FSSGS_ColorRangeGradient( uint8, uint8, const FSSGS_RGB& zero, const FSSGS_RGB& hundred );

    UPROPERTY( EditAnywhere, BlueprintReadWrite ) uint8 low;
    UPROPERTY( EditAnywhere, BlueprintReadWrite ) uint8 high;
    UPROPERTY( EditAnywhere, BlueprintReadWrite ) FSSGS_ColorGradient color;

};