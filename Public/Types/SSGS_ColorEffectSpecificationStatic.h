#pragma once


#include "SSGS_RGB.h"
#include "SSGS_ColorEffectSpecificationStatic.generated.h"


UCLASS( BlueprintType, meta = ( Category = "GameSense|Types" ) )
class STEELSERIESGAMESENSE_API USSGS_ColorEffectSpecificationStatic : public USSGS_ColorEffectSpecification {

    GENERATED_BODY()

public:

    UFUNCTION( BlueprintCallable, Category = "GameSense|ColorEffectSpecification" )
    void SetColor( const FSSGS_RGB& color );

    TSharedPtr< FJsonValue > Convert() const;

    UPROPERTY() FSSGS_RGB color;

};