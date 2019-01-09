#pragma once


#include "SSGS_JsonConvertable.generated.h"


USTRUCT()
struct STEELSERIESGAMESENSE_API FSSGS_JsonConvertable
{
    GENERATED_BODY()

    virtual ~FSSGS_JsonConvertable() {};
    virtual TSharedPtr< FJsonValue > Convert() const;
};
