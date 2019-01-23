#pragma once


#include "SSGS_ColorRange.h"
#include "SSGS_ColorEffectSpecificationRanges.generated.h"


UCLASS( BlueprintType, meta = ( Category = "GameSense|Types" ) )
class STEELSERIESGAMESENSE_API USSGS_ColorEffectSpecificationRanges : public USSGS_ColorEffectSpecification {

    GENERATED_BODY()

public:

    UFUNCTION( BlueprintCallable, BlueprintPure, Category = "GameSense|ColorEffectSpecification" )
    static USSGS_ColorEffectSpecificationRanges* MakeRangeColorEffect( const TArray< FSSGS_ColorRange >& v );

    UFUNCTION( BlueprintCallable, BlueprintPure, Category = "GameSense|ColorEffectSpecification" )
    static FSSGS_ColorRange MakeStaticColorRange( uint8 low, uint8 high, const FSSGS_RGB& color );

    UFUNCTION( BlueprintCallable, BlueprintPure, Category = "GameSense|ColorEffectSpecification" )
    static FSSGS_ColorRange MakeGradientColorRange( uint8 low, uint8 high, UPARAM( DisplayName = "Start Color" ) const FSSGS_RGB& zero, UPARAM( DisplayName = "End Color" ) const FSSGS_RGB& hundred );

    TSharedPtr< FJsonValue > Convert() const;

    UPROPERTY() TArray< FSSGS_ColorRange > ranges;

};