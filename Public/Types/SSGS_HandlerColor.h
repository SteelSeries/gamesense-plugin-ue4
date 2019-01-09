#pragma once


#include "SSGS_HandlerColor.generated.h"


USTRUCT( BlueprintType )
struct STEELSERIESGAMESENSE_API FSSGS_HandlerColor : public FSSGS_JsonConvertable {

    GENERATED_BODY()

    FSSGS_HandlerColor();
    FSSGS_HandlerColor( const FSSGS_HandlerColor& other );
    FSSGS_HandlerColor( const FIlluminationDeviceZone&, const SSGS_IlluminationMode&, USSGS_ColorEffectSpecification* colorSpec, USSGS_RateSpecification* rateSpec = nullptr );
    const FSSGS_HandlerColor& operator=( const FSSGS_HandlerColor& other );
    ~FSSGS_HandlerColor();


    UPROPERTY( EditAnywhere, BlueprintReadWrite )
    FIlluminationDeviceZone deviceZone;
    UPROPERTY( EditAnywhere, BlueprintReadWrite )
    SSGS_IlluminationMode mode;
    UPROPERTY( EditAnywhere, BlueprintReadWrite )
    USSGS_ColorEffectSpecification* color;
    UPROPERTY( EditAnywhere, BlueprintReadWrite )
    USSGS_RateSpecification* rate;

    TSharedPtr< FJsonValue > Convert() const;

};