/**
* Authors: sharkgoesmad
*
* Copyright (c) 2019 SteelSeries ApS. All Rights Reserved.
*/
#pragma once


#include "Common/SSGS_JsonConvertable.h"
#include "Types/SSGS_DeviceZone.h"
#include "Types/SSGS_Enums.h"
#include "Types/Illumination/SSGS_ColorEffectSpecification.h"
#include "Types/Rate/SSGS_RateSpecification.h"
#include "SSGS_HandlerColor.generated.h"


USTRUCT( BlueprintType, meta = ( Category = "Gamesense|Types" ) )
struct STEELSERIESGAMESENSE_API FSSGS_HandlerColor : public FSSGS_JsonConvertable {

    GENERATED_BODY()

    FSSGS_HandlerColor();
    FSSGS_HandlerColor( const FSSGS_HandlerColor& other );
    FSSGS_HandlerColor( const FSSGS_IlluminationDeviceZone& deviceZone, ESSGS_IlluminationMode mode, USSGS_ColorEffectSpecification* colorSpec, USSGS_RateSpecification* rateSpec = nullptr );
    const FSSGS_HandlerColor& operator=( const FSSGS_HandlerColor& other );
    ~FSSGS_HandlerColor();


    UPROPERTY( EditAnywhere, BlueprintReadWrite, meta = ( DisplayName = "Device - Zone" ), Category="Mandatory" )
    FSSGS_IlluminationDeviceZone deviceZone;
    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Mandatory" )
    ESSGS_IlluminationMode mode;
    UPROPERTY( EditAnywhere, BlueprintReadWrite, meta = ( DisplayName = "Color Specification" ), Category="Mandatory" )
    USSGS_ColorEffectSpecification* color;
    UPROPERTY( EditAnywhere, BlueprintReadWrite, meta = ( DisplayName = "Rate Specification" ), Category="Optional" )
    USSGS_RateSpecification* rate;

    TSharedPtr< FJsonValue > Convert() const;

};