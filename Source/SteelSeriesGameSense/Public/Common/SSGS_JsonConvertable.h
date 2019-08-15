/**
* Authors: sharkgoesmad
*
* Copyright (c) 2019 SteelSeries ApS. All Rights Reserved.
*/
#pragma once


#include "Dom/JsonValue.h"
#include "SSGS_JsonConvertable.generated.h"


USTRUCT()
struct STEELSERIESGAMESENSE_API FSSGS_JsonConvertable
{
    GENERATED_BODY()

    virtual ~FSSGS_JsonConvertable() {};
    virtual void Decorate( TSharedPtr< FJsonObject > obj ) const {}
    virtual TSharedPtr< FJsonValue > Convert() const {
        return TSharedPtr< FJsonValue >( nullptr );
    }

};
