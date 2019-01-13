#pragma once


#include "SSGS_TactileEffectPredefined.h"
#include "SSGS_TactileEffectCustom.h"
#include "SSGS_TactilePatternSpecification.generated.h"


UCLASS( BlueprintType, meta = ( Category = "GameSense|Types" ) )
class STEELSERIESGAMESENSE_API USSGS_TactilePatternSpecification : public UObject, public FSSGS_JsonConvertable {

    GENERATED_BODY()

public:

    UFUNCTION( BlueprintCallable, Category = "GameSense|TactilePatternSpecification" )
    void SetSimplePattern( const TArray< FSSGS_TactileEffectPredefined >& v );

    UFUNCTION( BlueprintCallable, Category = "GameSense|TactilePatternSpecification" )
    void SetCustomPattern( const TArray< FSSGS_TactileEffectCustom >& v );

    TSharedPtr< FJsonValue > Convert() const;

private:

    ESSGS_TactilePatternType _type;
    TUnion< TArray< FSSGS_TactileEffectPredefined >, TArray< FSSGS_TactileEffectCustom > > _pattern;

};
