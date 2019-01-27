#pragma once


#include "SSGS_Frequency.h"
#include "SSGS_RepeatLimit.h"
#include "SSGS_FrequencyRepeatLimitPair.h"
#include "SSGS_RateRange.generated.h"


USTRUCT( BlueprintType, meta = ( Category = "GameSense|Types" ) )
struct STEELSERIESGAMESENSE_API FSSGS_RateRange {

    GENERATED_BODY()

    FSSGS_RateRange();
    FSSGS_RateRange( const TArray< FSSGS_Frequency >& frequency, const TArray< FSSGS_RepeatLimit >& repeatLimit = TArray< FSSGS_RepeatLimit >() );
    FSSGS_RateRange( const TArray< FSSGS_FrequencyRepeatLimitPair >& v );

    UPROPERTY( EditAnywhere, BlueprintReadWrite ) TArray< FSSGS_Frequency > frequency;
    UPROPERTY( EditAnywhere, BlueprintReadWrite ) TArray< FSSGS_RepeatLimit > repeat_limit;

};
