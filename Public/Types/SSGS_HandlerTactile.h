#pragma once


#include "SSGS_HandlerTactile.generated.h"


USTRUCT( BlueprintType )
struct STEELSERIESGAMESENSE_API FSSGS_HandlerTactile : public FSSGS_JsonConvertable {

    GENERATED_BODY()

    FSSGS_HandlerTactile();
    FSSGS_HandlerTactile( const FSSGS_HandlerTactile& other );
    FSSGS_HandlerTactile( const FTactileDeviceZone& deviceZone, USSGS_TactilePatternSpecification* pattern, USSGS_RateSpecification* rate = nullptr );
    const FSSGS_HandlerTactile& operator=( const FSSGS_HandlerTactile& rhs );
    ~FSSGS_HandlerTactile();

    UPROPERTY( EditAnywhere, BlueprintReadWrite ) FTactileDeviceZone deviceZone;
    UPROPERTY( EditAnywhere, BlueprintReadOnly ) FString mode = TEXT( "vibrate" );
    UPROPERTY( EditAnywhere, BlueprintReadWrite ) USSGS_TactilePatternSpecification* pattern;
    UPROPERTY( EditAnywhere, BlueprintReadWrite ) USSGS_RateSpecification* rate;

    TSharedPtr< FJsonValue > Convert() const;

};