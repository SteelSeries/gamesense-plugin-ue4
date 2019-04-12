/**
* Authors: sharkgoesmad
*
* Copyright (c) 2019 SteelSeries ApS. All Rights Reserved.
*/
#pragma once


#include "Common/SSGS_JsonConvertable.h"
#include "SSGS_TactilePatternSpecification.generated.h"


UCLASS( BlueprintType, Abstract, meta = ( DisplayName = "AbstractTactilePatternSpecification" ) )
class STEELSERIESGAMESENSE_API USSGS_TactilePatternSpecification : public UObject, public FSSGS_JsonConvertable {

    GENERATED_BODY()

public:

    virtual ~USSGS_TactilePatternSpecification() {};
    TSharedPtr< FJsonValue > Convert() const { return TSharedPtr< FJsonValue >( nullptr ); }

protected:

    USSGS_TactilePatternSpecification() {};

};
