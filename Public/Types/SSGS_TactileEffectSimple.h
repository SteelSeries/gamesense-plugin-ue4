#pragma once


#include "SSGS_TactileEffectSimple.generated.h"


USTRUCT( BlueprintType )
struct STEELSERIESGAMESENSE_API FSSGS_TactileEffectSimple : public FSSGS_JsonConvertable {

    GENERATED_BODY()

    FSSGS_TactileEffectSimple() {}
    FSSGS_TactileEffectSimple( const FPredefinedTactilePattern& type, int32 delay_ms = 0 ) : type( type ), delay_ms( delay_ms ) {}

    UPROPERTY( EditAnywhere, BlueprintReadWrite ) FPredefinedTactilePattern type;
    UPROPERTY( EditAnywhere, BlueprintReadWrite ) int32 delay_ms;

    TSharedPtr< FJsonValue > Convert() const;

};