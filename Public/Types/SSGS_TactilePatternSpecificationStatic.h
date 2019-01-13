#pragma once


#include "SSGS_TactileEffectPredefined.h"
#include "SSGS_TactileEffectCustom.h"
#include "SSGS_TactilePatternSpecificationStatic.generated.h"


UCLASS( BlueprintType, meta = ( Category = "GameSense|Types" ) )
class STEELSERIESGAMESENSE_API USSGS_TactilePatternSpecificationStatic : public USSGS_TactilePatternSpecification {

    GENERATED_BODY()

public:

    void AddPredefinedEffect( const FSSGS_TactileEffectPredefined& v );
    void AddCustomEffect( const FSSGS_TactileEffectCustom& v );

    UFUNCTION( BlueprintCallable, Category = "GameSense|TactilePatternSpecification" )
    void AddPredefinedEffect( const FSSGS_PredefinedTactilePattern& pattern, int32 delay_ms = 0 );

    UFUNCTION( BlueprintCallable, Category = "GameSense|TactilePatternSpecification" )
    void AddCustomEffect( int32 length_ms, int32 delay_ms = 0 );

    TSharedPtr< FJsonValue > Convert() const;

private:

    struct _staticPattern {
        ESSGS_TactilePatternStaticType type;
        TUnion< FSSGS_TactileEffectPredefined, FSSGS_TactileEffectCustom > pattern;
    };

    TArray< _staticPattern > _pattern;

};
