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
#include "Common/SSGS_Union.h"
#include "SSGS_LineData.generated.h"



USTRUCT( BlueprintType, meta = ( Category = "Gamesense|Types" ) )
struct STEELSERIESGAMESENSE_API FSSGS_LineDataAccessor : public FSSGS_JsonConvertable {

    GENERATED_BODY()

    FSSGS_LineDataAccessor() : _type( UpdateValue ) {}

    /**
    * Construct FSSGS_LineDataAccessor object to specify the name of the property in
    * context frame of event update object.
    *
    * @param    key The name of the property in context frame.
    * @return   FSSGS_LineDataAccessor object.
    */
    static FSSGS_LineDataAccessor ContextFrameKey( const FString& key ) { return { FrameKey, key }; }

    /**
    * Construct FSSGS_LineDataAccessor object to specify GoLisp expression allowing to
    * obtain and transform a value for the frame.
    *
    * @param    expr GoLisp expression.
    * @return   FSSGS_LineDataAccessor object.
    */
    static FSSGS_LineDataAccessor GoLispExpression( const FString& expr ) { return { GoLispExpr, expr }; }

    void Decorate( TSharedPtr< FJsonObject > obj ) const;

private:

    enum _type_ {
        UpdateValue = 0,
        FrameKey,
        GoLispExpr
    };

private:

    FSSGS_LineDataAccessor( _type_ t, const FString& v ) : _type( t ), _value( v ) {}

private:

    _type_ _type;
    FString _value;

};

USTRUCT( BlueprintType, meta = ( Category = "Gamesense|Types" ) )
struct STEELSERIESGAMESENSE_API FSSGS_LineDataText {
    
    GENERATED_BODY()

    FSSGS_LineDataText() : has_text( true ), prefix(), suffix(), bold( false ), wrap( 0 ) {}
    FSSGS_LineDataText( const FString& prefix, const FString& suffix, bool bold, int32 wrap ) :
        has_text( true ), prefix( prefix ), suffix( suffix ), bold( bold ), wrap( wrap ) {}

    UPROPERTY()                                   bool has_text;
    UPROPERTY( EditAnywhere, BlueprintReadWrite ) FString prefix;
    UPROPERTY( EditAnywhere, BlueprintReadWrite ) FString suffix;
    UPROPERTY( EditAnywhere, BlueprintReadWrite ) bool bold;
    UPROPERTY( EditAnywhere, BlueprintReadWrite ) int32 wrap;

};

struct STEELSERIESGAMESENSE_API FSSGS_LineDataProgressBar {

    FSSGS_LineDataProgressBar() : has_progress_bar( true ) {}

    bool has_progress_bar;

};

USTRUCT( BlueprintType, meta = ( Category = "Gamesense|Types" ) )
struct STEELSERIESGAMESENSE_API FSSGS_LineData : public FSSGS_JsonConvertable {

    GENERATED_BODY()

    FSSGS_LineData() : FSSGS_LineData( FSSGS_LineDataText() ) {}
    FSSGS_LineData( const FSSGS_LineDataText& v, const FSSGS_LineDataAccessor& a = FSSGS_LineDataAccessor() ) :
        _variant_type( TxtModifiers ), _variant( v ), _dataAccessor( a ) {}
    FSSGS_LineData( const FSSGS_LineDataProgressBar& v, const FSSGS_LineDataAccessor& a = FSSGS_LineDataAccessor() ) :
        _variant_type( ProgressBar ), _variant( v ), _dataAccessor( a ) {}

    TSharedPtr< FJsonValue > Convert() const;

private:

    enum _type_ {
        TxtModifiers = 0,
        ProgressBar
    };

private:

    _type_ _variant_type;
    ssgs::Union< FSSGS_LineDataText, FSSGS_LineDataProgressBar > _variant;
    FSSGS_LineDataAccessor _dataAccessor;

};
