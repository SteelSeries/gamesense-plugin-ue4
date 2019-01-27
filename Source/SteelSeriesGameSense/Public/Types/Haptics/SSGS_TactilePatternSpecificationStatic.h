#pragma once


#include "SSGS_TactilePatternSpecification.h"
#include "SSGS_TactilePatternStatic.h"
#include "SSGS_TactilePatternSpecificationStatic.generated.h"


UCLASS( BlueprintType, meta = ( Category = "GameSense|Types" ) )
class STEELSERIESGAMESENSE_API USSGS_TactilePatternSpecificationStatic : public USSGS_TactilePatternSpecification {

    GENERATED_BODY()

public:

    /**
    * Properly constructs USSGS_TactilePatternSpecificationStatic object.
    *
    * @param    pattern Array of variant (predefined/custom) pattern objects.
    * @return   USSGS_TactilePatternSpecificationStatic object.
    */
    UFUNCTION( BlueprintCallable, BlueprintPure, Category = "GameSense|TactilePatternSpecification" )
    static USSGS_TactilePatternSpecificationStatic* MakeStaticTactilePattern( const TArray< FSSGS_TactilePatternStatic >& pattern );

    /**
    * Construct a predefined static pattern variant.
    *
    * @param    type Predefined tactile pattern. Use USSGS_PredefinedTactilePatternFactory to obtain correct value.
    * @param    delay_ms Delay amount in milliseconds.
    * @return   FSSGS_TactilePatternStatic object.
    */
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc, Category = "GameSense|TactilePatternSpecification" ) )
    static FSSGS_TactilePatternStatic MakeStaticWithPredefinedEffect( const FSSGS_PredefinedTactilePattern& type, int32 delay_ms = 0 );

    /**
    * Construct a custom static pattern variant.
    *
    * @param    length_ms Duration of the effect in milliseconds.
    * @param    delay_ms Delay amount in milliseconds.
    * @return   FSSGS_TactilePatternStatic object.
    */
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc, Category = "GameSense|TactilePatternSpecification" ) )
    static FSSGS_TactilePatternStatic MakeStaticWithCustomEffect( int32 length_ms, int32 delay_ms = 0 );

    TSharedPtr< FJsonValue > Convert() const;

private:

    TArray< FSSGS_TactilePatternStatic > _pattern;

};
