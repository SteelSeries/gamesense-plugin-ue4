#pragma once


#include "SSGS_ColorEffectSpecification.generated.h"


UCLASS( BlueprintType, Abstract, meta = ( DisplayName = "AbstractColorEffectSpecification" ) )
class STEELSERIESGAMESENSE_API USSGS_ColorEffectSpecification : public UObject, public FSSGS_JsonConvertable {

    GENERATED_BODY()

public:

    virtual TSharedPtr< FJsonValue > Convert() const { return TSharedPtr< FJsonValue >( nullptr ); }

protected:

    USSGS_ColorEffectSpecification() {};

};