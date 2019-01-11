#pragma once


#include "SSGS_TactileEffectCustom.generated.h"


USTRUCT( BlueprintType, meta = ( Category = "GameSense|Types" ) )
struct STEELSERIESGAMESENSE_API FSSGS_TactileEffectCustom : public FSSGS_JsonConvertable {

    GENERATED_BODY()

    FSSGS_TactileEffectCustom() {}
    FSSGS_TactileEffectCustom( int32 length_ms, int32 delay_ms = 0 ) : length_ms( length_ms ), delay_ms( delay_ms ) {}

    UPROPERTY( EditAnywhere, BlueprintReadOnly ) FString type = TEXT( "custom" );
    UPROPERTY( EditAnywhere, BlueprintReadWrite ) int32 length_ms;
    UPROPERTY( EditAnywhere, BlueprintReadWrite ) int32 delay_ms;

    TSharedPtr< FJsonValue > Convert() const;

};