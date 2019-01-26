#pragma once


#include "Common/SSGS_JsonConvertable.h"
#include "Common/SSGS_Union.h"
#include "Types/SSGS_Enums.h"
#include "SSGS_FrequencyRepeatLimitPair.h"
#include "SSGS_RateStatic.h"
#include "SSGS_RateRange.h"
#include "SSGS_RateSpecification.generated.h"


UCLASS( BlueprintType, meta = ( Category = "GameSense|Types" ) )
class STEELSERIESGAMESENSE_API USSGS_RateSpecification : public UObject, public FSSGS_JsonConvertable {

    GENERATED_BODY()

public:

    UFUNCTION( BlueprintCallable, BlueprintPure, Category = "GameSense|RateSpecification" )
    static USSGS_RateSpecification* MakeStaticRate( int32 frequency, int32 repeat_limit );

    UFUNCTION( BlueprintCallable, BlueprintPure, Category = "GameSense|RateSpecification" )
    static USSGS_RateSpecification* MakeRangedRate( UPARAM( DisplayName = "Frequency - RepeatLimit Pairs" ) const TArray< FSSGS_FrequencyRepeatLimitPair >& v );

    TSharedPtr< FJsonValue > Convert() const;

private:

    ESSGS_RateMode _mode;
    ssgs::Union< FSSGS_RateStatic, FSSGS_RateRange > _rate;

};