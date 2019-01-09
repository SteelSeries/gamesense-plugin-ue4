#pragma once


#include "SSGS_RateStatic.h"
#include "SSGS_RateRange.h"
#include "SSGS_RateSpecification.generated.h"


UCLASS( BlueprintType )
class STEELSERIESGAMESENSE_API USSGS_RateSpecification : public UObject, public FSSGS_JsonConvertable {

    GENERATED_BODY()

public:

    UFUNCTION( BlueprintCallable, Category = SSGS_CATEGORY )
    void SetStaticRate( const FSSGS_RateStatic& v );

    UFUNCTION( BlueprintCallable, Category = SSGS_CATEGORY )
    void SetRangedRate( const FSSGS_RateRange& v );

    TSharedPtr< FJsonValue > Convert() const;

private:

    SSGS_RateMode _mode;
    TUnion< FSSGS_RateStatic, FSSGS_RateRange > _rate;

};