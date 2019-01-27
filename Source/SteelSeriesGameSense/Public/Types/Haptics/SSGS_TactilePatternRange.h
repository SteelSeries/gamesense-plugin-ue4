#pragma once


#include "SSGS_TactilePatternStatic.h"
#include "SSGS_TactilePatternRange.generated.h"


USTRUCT( BlueprintType, meta = ( Category = "GameSense|Types" ) )
struct STEELSERIESGAMESENSE_API FSSGS_TactilePatternRange : public FSSGS_JsonConvertable {

    GENERATED_BODY()

    FSSGS_TactilePatternRange() {}
    FSSGS_TactilePatternRange( int32 low, int32 int32, const TArray< FSSGS_TactilePatternStatic >& pattern );

    TSharedPtr< FJsonValue > Convert() const;

    UPROPERTY( EditAnywhere, BlueprintReadWrite ) int32 low;
    UPROPERTY( EditAnywhere, BlueprintReadWrite ) int32 high;
    UPROPERTY( EditAnywhere, BlueprintReadWrite ) TArray< FSSGS_TactilePatternStatic > pattern;

};
