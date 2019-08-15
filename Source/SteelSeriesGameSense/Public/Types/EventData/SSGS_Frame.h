/**
* Authors: sharkgoesmad
*
* Copyright (c) 2019 SteelSeries ApS. All Rights Reserved.
*/
#pragma once


#include "SSGS_Frame.generated.h"


UCLASS( BlueprintType, Abstract, meta = ( DisplayName = "AbstractFrame" ) )
class STEELSERIESGAMESENSE_API USSGS_Frame : public UObject, public FSSGS_JsonConvertable {

    GENERATED_BODY()

public:

    virtual ~USSGS_Frame() {}
    virtual TSharedPtr< FJsonValue > Convert() const { return TSharedPtr< FJsonValue >( nullptr ); }

protected:

    USSGS_Frame() {};

};
