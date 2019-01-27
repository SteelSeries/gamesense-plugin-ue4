#pragma once


#include "Common/SSGS_JsonConvertable.h"
#include "SSGS_TactileEffectCustom.generated.h"


USTRUCT( BlueprintType, meta = ( Category = "GameSense|Types" ) )
struct STEELSERIESGAMESENSE_API FSSGS_TactileEffectCustom : public FSSGS_JsonConvertable {

    GENERATED_BODY()


    FSSGS_TactileEffectCustom() : _type( TEXT( "custom" ) ) {}
    FSSGS_TactileEffectCustom( int32 length_ms, int32 delay_ms = 0 ) : length_ms( length_ms ), delay_ms( delay_ms ), _type( TEXT( "custom" ) ) {}

    UPROPERTY( EditAnywhere, BlueprintReadWrite ) int32 length_ms;
    UPROPERTY( EditAnywhere, BlueprintReadWrite ) int32 delay_ms;

    TSharedPtr< FJsonValue > Convert() const;
    const FString& type() { return _type; }

private:

    FString _type;

};