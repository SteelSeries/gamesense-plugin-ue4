#pragma once


#include "SSGS_RGB.h"
#include "SSGS_ColorRangeStatic.generated.h"


USTRUCT( BlueprintType )
struct STEELSERIESGAMESENSE_API FSSGS_ColorRangeStatic {

    GENERATED_BODY()

    FSSGS_ColorRangeStatic() {};
    FSSGS_ColorRangeStatic( uint8, uint8, const FSSGS_RGB& );

    UPROPERTY( EditAnywhere, BlueprintReadWrite ) uint8 low;
    UPROPERTY( EditAnywhere, BlueprintReadWrite ) uint8 high;
    UPROPERTY( EditAnywhere, BlueprintReadWrite ) FSSGS_RGB color;

};