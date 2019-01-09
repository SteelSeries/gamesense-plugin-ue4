#pragma once


#include "SSGS_ColorRangeGradient.generated.h"


USTRUCT( BlueprintType )
struct STEELSERIESGAMESENSE_API FSSGS_ColorRangeGradient {

    GENERATED_BODY()

    FSSGS_ColorRangeGradient() {};
    FSSGS_ColorRangeGradient( uint8, uint8, const FSSGS_ColorGradient& );

    UPROPERTY( EditAnywhere, BlueprintReadWrite ) uint8 low;
    UPROPERTY( EditAnywhere, BlueprintReadWrite ) uint8 high;
    UPROPERTY( EditAnywhere, BlueprintReadWrite ) FSSGS_ColorGradient color;

};