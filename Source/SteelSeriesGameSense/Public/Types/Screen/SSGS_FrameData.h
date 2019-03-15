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


#include "SSGS_FrameDataSingleLine.h"
#include "SSGS_FrameDataMultiLine.h"
#include "SSGS_FrameDataImage.h"
#include "SSGS_FrameData.generated.h"


USTRUCT( BlueprintType, meta = ( Category = "Gamesense|Types" ) )
struct STEELSERIESGAMESENSE_API FSSGS_FrameData : public FSSGS_JsonConvertable {

    GENERATED_BODY()

    FSSGS_FrameData() : FSSGS_FrameData( FSSGS_FrameDataSingleLine() ) {};
    FSSGS_FrameData( const FSSGS_FrameDataSingleLine& v ) : _variant_type( SingleLine ), _variant( v ) {}
    FSSGS_FrameData( const FSSGS_FrameDataMultiLine& v ) : _variant_type( MultiLine ), _variant( v ) {}
    FSSGS_FrameData( const FSSGS_FrameDataImage& v ) : _variant_type( Image ), _variant( v ) {}

    TSharedPtr< FJsonValue > Convert() const;

private:

    enum _type_ {
        SingleLine = 0,
        MultiLine,
        Image
    };

private:

    _type_ _variant_type;
    ssgs::Union< FSSGS_FrameDataSingleLine, FSSGS_FrameDataMultiLine, FSSGS_FrameDataImage > _variant;

};
