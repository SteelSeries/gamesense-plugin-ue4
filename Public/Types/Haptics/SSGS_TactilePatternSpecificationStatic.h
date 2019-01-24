#pragma once


#include "SSGS_TactileEffectPredefined.h"
#include "SSGS_TactileEffectCustom.h"
#include "SSGS_TactilePatternSpecificationStatic.generated.h"


UCLASS( BlueprintType, meta = ( Category = "GameSense|Types" ) )
class STEELSERIESGAMESENSE_API USSGS_TactilePatternSpecificationStatic : public USSGS_TactilePatternSpecification {

    GENERATED_BODY()

public:

    UFUNCTION( BlueprintCallable, BlueprintPure, Category = "GameSense|TactilePatternSpecification" )
    static USSGS_TactilePatternSpecificationStatic* MakeStaticTactilePattern( const TArray< FSSGS_TactilePatternStatic >& pattern );

    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc, Category = "GameSense|TactilePatternSpecification" ) )
    static FSSGS_TactilePatternStatic MakeStaticWithPredefinedEffect( const FSSGS_PredefinedTactilePattern& type, int32 delay_ms = 0 );

    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc, Category = "GameSense|TactilePatternSpecification" ) )
    static FSSGS_TactilePatternStatic MakeStaticWithCustomEffect( int32 length_ms, int32 delay_ms = 0 );

    TSharedPtr< FJsonValue > Convert() const;

private:

    TArray< FSSGS_TactilePatternStatic > _pattern;

};
