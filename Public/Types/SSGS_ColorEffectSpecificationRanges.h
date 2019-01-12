#pragma once


#include "SSGS_ColorRangeStatic.h"
#include "SSGS_ColorRangeGradient.h"
#include "SSGS_ColorEffectSpecificationRanges.generated.h"


UCLASS( BlueprintType, meta = ( Category = "GameSense|Types" ) )
class STEELSERIESGAMESENSE_API USSGS_ColorEffectSpecificationRanges : public USSGS_ColorEffectSpecification {

    GENERATED_BODY()

public:

    void AddStatic( const FSSGS_ColorRangeStatic& v );
    void AddGradient( const FSSGS_ColorRangeGradient& v );

    UFUNCTION( BlueprintCallable, Category = "GameSense|ColorEffectSpecification" )
    void AddStatic( uint8 low, uint8 high, const FSSGS_RGB& color );

    UFUNCTION( BlueprintCallable, Category = "GameSense|ColorEffectSpecification" )
    void AddGradient( uint8 low, uint8 high, const FSSGS_RGB& zero, const FSSGS_RGB& hundred );

    TSharedPtr< FJsonValue > Convert() const;

    UPROPERTY() TArray< FSSGS_ColorRangeStatic > staticRanges;
    UPROPERTY() TArray< FSSGS_ColorRangeGradient > gradientRanges;

};