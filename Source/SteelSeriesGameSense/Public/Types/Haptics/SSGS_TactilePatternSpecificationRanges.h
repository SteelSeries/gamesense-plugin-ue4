/**
* Authors: sharkgoesmad
*
* Copyright (c) 2019 SteelSeries ApS. All Rights Reserved.
*/
#pragma once


#include "SSGS_TactilePatternSpecification.h"
#include "SSGS_TactilePatternRange.h"
#include "SSGS_TactilePatternSpecificationRanges.generated.h"


UCLASS( BlueprintType, meta = ( Category = "Gamesense|Types" ) )
class STEELSERIESGAMESENSE_API USSGS_TactilePatternSpecificationRanges : public USSGS_TactilePatternSpecification {

    GENERATED_BODY()

public:

    /**
    * Properly constructs USSGS_TactilePatternSpecificationRanges object.
    *
    * @param    ranges Array of ranges.
    * @return   USSGS_HandlerCollection object.
    */
    UFUNCTION( BlueprintCallable, BlueprintPure, Category = "Gamesense|TactilePatternSpecification" )
    static USSGS_TactilePatternSpecificationRanges* MakeRangedTactilePattern( const TArray< FSSGS_TactilePatternRange >& ranges );

    TSharedPtr< FJsonValue > Convert() const;

private:

    TArray< FSSGS_TactilePatternRange > _pattern;

};
