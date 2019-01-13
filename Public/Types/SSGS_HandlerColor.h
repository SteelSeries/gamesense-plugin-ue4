#pragma once


#include "SSGS_HandlerColor.generated.h"


USTRUCT( BlueprintType, meta = ( Category = "GameSense|Types" ) )
struct STEELSERIESGAMESENSE_API FSSGS_HandlerColor : public FSSGS_JsonConvertable {

    GENERATED_BODY()

    FSSGS_HandlerColor();
    FSSGS_HandlerColor( const FSSGS_HandlerColor& other );
    FSSGS_HandlerColor( const FSSGS_IlluminationDeviceZone& deviceZone, SSGS_IlluminationMode mode, USSGS_ColorEffectSpecification* colorSpec, USSGS_RateSpecification* rateSpec = nullptr );
    const FSSGS_HandlerColor& operator=( const FSSGS_HandlerColor& other );
    ~FSSGS_HandlerColor();


    UPROPERTY( EditAnywhere, BlueprintReadWrite, meta = ( DisplayName = "Device - Zone" ) )
    FSSGS_IlluminationDeviceZone deviceZone;
    UPROPERTY( EditAnywhere, BlueprintReadWrite )
    SSGS_IlluminationMode mode;
    UPROPERTY( EditAnywhere, BlueprintReadWrite, meta = ( DisplayName = "Color Specification" ) )
    USSGS_ColorEffectSpecification* color;
    UPROPERTY( EditAnywhere, BlueprintReadWrite, meta = ( DisplayName = "Rate Specification" ) )
    USSGS_RateSpecification* rate;

    TSharedPtr< FJsonValue > Convert() const;

};