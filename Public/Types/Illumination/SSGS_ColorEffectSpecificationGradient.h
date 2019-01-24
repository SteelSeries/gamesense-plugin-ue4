#pragma once


#include "SSGS_RGB.h"
#include "SSGS_Gradient.h"
#include "SSGS_ColorGradient.h"
#include "SSGS_ColorEffectSpecificationGradient.generated.h"


UCLASS( BlueprintType, meta = ( Category = "GameSense|Types" ) )
class STEELSERIESGAMESENSE_API USSGS_ColorEffectSpecificationGradient : public USSGS_ColorEffectSpecification {

    GENERATED_BODY()

public:

    UFUNCTION( BlueprintCallable, BlueprintPure, Category = "GameSense|ColorEffectSpecification" )
    static USSGS_ColorEffectSpecificationGradient* MakeGradientColorEffect( UPARAM( DisplayName = "Start Color" ) const FSSGS_RGB& zero, UPARAM( DisplayName = "End Color" ) const FSSGS_RGB& hundred );

    TSharedPtr< FJsonValue > Convert() const;

    UPROPERTY() FSSGS_ColorGradient gradient;

};