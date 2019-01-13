#pragma once


#include "SSGS_RateStatic.h"
#include "SSGS_RateRange.h"
#include "SSGS_RateSpecification.generated.h"


UCLASS( BlueprintType, meta = ( Category = "GameSense|Types" ) )
class STEELSERIESGAMESENSE_API USSGS_RateSpecification : public UObject, public FSSGS_JsonConvertable {

    GENERATED_BODY()

public:

    void SetStaticRate( const FSSGS_RateStatic& v );
    void SetRangedRate( const FSSGS_RateRange& v );

    UFUNCTION( BlueprintCallable, Category = "GameSense|RateSpecification" )
    void SetStaticRate( int32 frequency, int32 repeat_limit );

    UFUNCTION( BlueprintCallable, Category = "GameSense|RateSpecification" )
    void SetRangedRate( UPARAM( DisplayName = "Frequency - RepeatLimit Pairs" ) const TArray< FSSGS_FrequencyRepeatLimitPair >& v );

    TSharedPtr< FJsonValue > Convert() const;

private:

    SSGS_RateMode _mode;
    TUnion< FSSGS_RateStatic, FSSGS_RateRange > _rate;

};