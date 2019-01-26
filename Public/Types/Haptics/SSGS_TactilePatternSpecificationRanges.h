#pragma once


#include "SSGS_TactilePatternSpecification.h"
#include "SSGS_TactilePatternRange.h"
#include "SSGS_TactilePatternSpecificationRanges.generated.h"


UCLASS( BlueprintType, meta = ( Category = "GameSense|Types" ) )
class STEELSERIESGAMESENSE_API USSGS_TactilePatternSpecificationRanges : public USSGS_TactilePatternSpecification {

    GENERATED_BODY()

public:

    UFUNCTION( BlueprintCallable, BlueprintPure, Category = "GameSense|TactilePatternSpecification" )
    static USSGS_TactilePatternSpecificationRanges* MakeRangedTactilePattern( const TArray< FSSGS_TactilePatternRange >& ranges );

    TSharedPtr< FJsonValue > Convert() const;

private:

    TArray< FSSGS_TactilePatternRange > _pattern;

};
