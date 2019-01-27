#pragma once


#include "SSGS_RGB.h"
#include "SSGS_ColorRangeStatic.generated.h"


USTRUCT( BlueprintType, meta = ( Category = "GameSense|Types" ) )
struct STEELSERIESGAMESENSE_API FSSGS_ColorRangeStatic {

    GENERATED_BODY()

    FSSGS_ColorRangeStatic() {};
    FSSGS_ColorRangeStatic( int32 low, int32 high, const FSSGS_RGB& );

    UPROPERTY( EditAnywhere, BlueprintReadWrite ) int32 low;
    UPROPERTY( EditAnywhere, BlueprintReadWrite ) int32 high;
    UPROPERTY( EditAnywhere, BlueprintReadWrite ) FSSGS_RGB color;

};
