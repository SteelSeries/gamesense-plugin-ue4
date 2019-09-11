/**
* Authors: sharkgoesmad
*
* Copyright (c) 2019 SteelSeries ApS. All Rights Reserved.
*/
#pragma once


#include "Common/SSGS_JsonConvertable.h"
#include "Types/SSGS_DeviceZone.h"
#include "Types/Haptics/SSGS_TactilePatternSpecification.h"
#include "Types/Rate/SSGS_RateSpecification.h"
#include "SSGS_HandlerTactile.generated.h"


USTRUCT( BlueprintType, meta = ( Category = "Gamesense|Types" ) )
struct STEELSERIESGAMESENSE_API FSSGS_HandlerTactile : public FSSGS_JsonConvertable {

    GENERATED_BODY()

    FSSGS_HandlerTactile();
    FSSGS_HandlerTactile( const FSSGS_HandlerTactile& other );
    FSSGS_HandlerTactile( const FSSGS_TactileDeviceZone& deviceZone, USSGS_TactilePatternSpecification* pattern, USSGS_RateSpecification* rate = nullptr );
    const FSSGS_HandlerTactile& operator=( const FSSGS_HandlerTactile& rhs );
    ~FSSGS_HandlerTactile();

    UPROPERTY( EditAnywhere, BlueprintReadWrite, meta = ( DisplayName = "Device - Zone" ), Category="Mandatory" )
    FSSGS_TactileDeviceZone deviceZone;
    UPROPERTY( EditAnywhere, BlueprintReadOnly, Category="Mandatory" )
    FString mode = TEXT( "vibrate" );
    UPROPERTY( EditAnywhere, BlueprintReadWrite, meta = ( DisplayName = "Pattern Specification" ), Category="Mandatory" )
    USSGS_TactilePatternSpecification* pattern;
    UPROPERTY( EditAnywhere, BlueprintReadWrite, meta = ( DisplayName = "Rate Specification" ), Category="Optional" )
    USSGS_RateSpecification* rate;

    TSharedPtr< FJsonValue > Convert() const;

};