#pragma once


#include "SSGS_TactilePatternStatic.h"
#include "SSGS_TactilePatternRange.generated.h"


USTRUCT( BlueprintType, meta = ( Category = "GameSense|Types" ) )
struct STEELSERIESGAMESENSE_API FSSGS_TactilePatternRange : public FSSGS_JsonConvertable {

    GENERATED_BODY()

    FSSGS_TactilePatternRange() {}
    FSSGS_TactilePatternRange( uint8 low, uint8 high, const TArray< FSSGS_TactilePatternStatic >& pattern );

    TSharedPtr< FJsonValue > Convert() const;

    UPROPERTY( EditAnywhere, BlueprintReadWrite ) uint8 low;
    UPROPERTY( EditAnywhere, BlueprintReadWrite ) uint8 high;
    UPROPERTY( EditAnywhere, BlueprintReadWrite ) TArray< FSSGS_TactilePatternStatic > pattern;

};
