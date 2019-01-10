#pragma once


#include "SSGS_RGB.h"
#include "SSGS_Gradient.h"
#include "SSGS_ColorGradient.h"
#include "SSGS_ColorEffectSpecificationGradient.generated.h"


UCLASS( BlueprintType )
class STEELSERIESGAMESENSE_API USSGS_ColorEffectSpecificationGradient : public USSGS_ColorEffectSpecification {

    GENERATED_BODY()

public:

    ~USSGS_ColorEffectSpecificationGradient();

    UFUNCTION( BlueprintCallable, Category = SSGS_CATEGORY )
    void SetGradientWithColors( const FSSGS_RGB& zero, const FSSGS_RGB& hundred );

    UFUNCTION( BlueprintCallable, Category = SSGS_CATEGORY )
    void SetGradient( const FSSGS_Gradient& gradient );

    TSharedPtr< FJsonValue > Convert() const;

    UPROPERTY() FSSGS_ColorGradient gradient;

};