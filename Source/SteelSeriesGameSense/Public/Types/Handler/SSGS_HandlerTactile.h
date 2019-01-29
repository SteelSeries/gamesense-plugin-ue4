/**
* authors: sharkgoesmad
*
* Copyright (c) 2019 SteelSeries
*
* Permission is hereby granted, free of charge, to any person obtaining
* a copy of this software and associated documentation files (the
* "Software"), to deal in the Software without restriction, including
* without limitation the rights to use, copy, modify, merge, publish,
* distribute, sublicense, and/or sell copies of the Software, and to
* permit persons to whom the Software is furnished to do so, subject to
* the following conditions:
*
* The above copyright notice and this permission notice shall be
* included in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#pragma once


#include "Common/SSGS_JsonConvertable.h"
#include "Types/SSGS_DeviceZone.h"
#include "Types/Haptics/SSGS_TactilePatternSpecification.h"
#include "Types/Rate/SSGS_RateSpecification.h"
#include "SSGS_HandlerTactile.generated.h"


USTRUCT( BlueprintType, meta = ( Category = "GameSense|Types" ) )
struct STEELSERIESGAMESENSE_API FSSGS_HandlerTactile : public FSSGS_JsonConvertable {

    GENERATED_BODY()

    FSSGS_HandlerTactile();
    FSSGS_HandlerTactile( const FSSGS_HandlerTactile& other );
    FSSGS_HandlerTactile( const FSSGS_TactileDeviceZone& deviceZone, USSGS_TactilePatternSpecification* pattern, USSGS_RateSpecification* rate = nullptr );
    const FSSGS_HandlerTactile& operator=( const FSSGS_HandlerTactile& rhs );
    ~FSSGS_HandlerTactile();

    UPROPERTY( EditAnywhere, BlueprintReadWrite, meta = ( DisplayName = "Device - Zone" ) )
    FSSGS_TactileDeviceZone deviceZone;
    UPROPERTY( EditAnywhere, BlueprintReadOnly )
    FString mode = TEXT( "vibrate" );
    UPROPERTY( EditAnywhere, BlueprintReadWrite, meta = ( DisplayName = "Pattern Specification" ) )
    USSGS_TactilePatternSpecification* pattern;
    UPROPERTY( EditAnywhere, BlueprintReadWrite, meta = ( DisplayName = "Rate Specification" ) )
    USSGS_RateSpecification* rate;

    TSharedPtr< FJsonValue > Convert() const;

};