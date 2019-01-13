#pragma once


#include "SSGS_TactilePatternSpecification.generated.h"


UCLASS( BlueprintType, Abstract, meta = ( DisplayName = "AbstractTactilePatternSpecification" ) )
class STEELSERIESGAMESENSE_API USSGS_TactilePatternSpecification : public UObject, public FSSGS_JsonConvertable {

    GENERATED_BODY()

public:

    TSharedPtr< FJsonValue > Convert() const { return TSharedPtr< FJsonValue >( nullptr ); }

protected:

    USSGS_TactilePatternSpecification() {};

};
