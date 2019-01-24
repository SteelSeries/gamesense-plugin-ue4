#pragma once


#include "SSGS_TactileEffectPredefined.generated.h"


USTRUCT( BlueprintType, meta = ( Category = "GameSense|Types" ) )
struct STEELSERIESGAMESENSE_API FSSGS_TactileEffectPredefined : public FSSGS_JsonConvertable {

    GENERATED_BODY()

    FSSGS_TactileEffectPredefined() {}
    FSSGS_TactileEffectPredefined( const FSSGS_PredefinedTactilePattern& type, int32 delay_ms = 0 ) : type( type ), delay_ms( delay_ms ) {}

    UPROPERTY( EditAnywhere, BlueprintReadWrite ) FSSGS_PredefinedTactilePattern type;
    UPROPERTY( EditAnywhere, BlueprintReadWrite ) int32 delay_ms;

    TSharedPtr< FJsonValue > Convert() const;

};