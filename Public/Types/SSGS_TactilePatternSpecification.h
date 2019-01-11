#pragma once


#include "SSGS_TactileEffectSimple.h"
#include "SSGS_TactileEffectCustom.h"
#include "SSGS_TactilePatternSpecification.generated.h"


UCLASS( BlueprintType, meta = ( Category = "GameSense|Types" ) )
class STEELSERIESGAMESENSE_API USSGS_TactilePatternSpecification : public UObject, public FSSGS_JsonConvertable {

    GENERATED_BODY()

public:

    USSGS_TactilePatternSpecification();

    UFUNCTION( BlueprintCallable, Category = "GameSense|TactilePatternSpecification" )
    void SetSimplePattern( const TArray< FSSGS_TactileEffectSimple >& v );

    UFUNCTION( BlueprintCallable, Category = "GameSense|TactilePatternSpecification" )
    void SetCustomPattern( const TArray< FSSGS_TactileEffectCustom >& v );

    TSharedPtr< FJsonValue > Convert() const;

private:

    SSGS_TactilePatternType _type;
    TUnion< TArray< FSSGS_TactileEffectSimple >, TArray< FSSGS_TactileEffectCustom > > _pattern;

};