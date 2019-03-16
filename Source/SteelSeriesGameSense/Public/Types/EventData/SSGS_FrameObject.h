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
#include "Types/EventData/SSGS_Frame.h"
#include "SSGS_FrameObject.generated.h"


USTRUCT( BlueprintType, meta = ( Category = "Gamesense|Types" ) )
struct STEELSERIESGAMESENSE_API FSSGS_KeyValuePair : public FSSGS_JsonConvertable {

    GENERATED_BODY()

    typedef TArray< FSSGS_KeyValuePair > TSSGS_ObjectDef;

public:

    FSSGS_KeyValuePair() : _type( Invalid ) {};

    FSSGS_KeyValuePair( const FString& n, bool v ) :
        _name( n ), _type( Bool ), _variant( v ) {}

    FSSGS_KeyValuePair( const FString& n, uint8 v ) :
        _name( n ), _type( Uint8 ), _variant( v ) {}

    FSSGS_KeyValuePair( const FString& n, int32 v ) :
        _name( n ), _type( Int32 ), _variant( v ) {}

    FSSGS_KeyValuePair( const FString& n, float v ) :
        _name( n ), _type( Float ), _variant( v ) {}

    FSSGS_KeyValuePair( const FString& n, const FString& v ) :
        _name( n ), _type( String ), _variant( v ) {}

    FSSGS_KeyValuePair( const FString& n, const TSSGS_ObjectDef& v ) :
        _name( n ), _type( Object ), _variant( v ) {}

    FSSGS_KeyValuePair( const FString& n, const TArray< bool >& v ) :
        _name( n ), _type( BoolArray ), _variant( v ) {}

    FSSGS_KeyValuePair( const FString& n, const TArray< uint8 >& v ) :
        _name( n ), _type( Uint8Array ), _variant( v ) {}

    FSSGS_KeyValuePair( const FString& n, const TArray< int32 >& v ) :
        _name( n ), _type( Int32Array ), _variant( v ) {}

    FSSGS_KeyValuePair( const FString& n, const TArray< float >& v ) :
        _name( n ), _type( FloatArray ), _variant( v ) {}

    FSSGS_KeyValuePair( const FString& n, const TArray< FString >& v ) :
        _name( n ), _type( StringArray ), _variant( v ) {}

    FSSGS_KeyValuePair( const FString& n, const TArray< FSSGS_PropertyContainer >& v ) :
        _name( n ), _type( ObjectArray ), _variant( v ) {}


    void Decorate( TSharedPtr< FJsonObject > obj ) const;

private:

    enum _pv_type_ {
        Invalid = 0,
        Bool,
        Uint8,
        Int32,
        Float,
        String,
        Object,
        BoolArray,
        Uint8Array,
        Int32Array,
        FloatArray,
        StringArray,
        ObjectArray
    };

    typedef ssgs::Union< bool, uint8, int32, float, FString, TSSGS_ObjectDef > Type;
    typedef ssgs::Union< TArray< bool >,
        TArray< uint8 >,
        TArray< int32 >,
        TArray< float >,
        TArray< FString >,
        TArray< FSSGS_PropertyContainer > > ArrayType;

private:

    FString _name;
    _pv_type_ _type;
    ssgs::Union< Type, ArrayType > _variant;

};

USTRUCT( BlueprintType, meta = ( Category = "Gamesense|Types" ) )
struct FSSGS_PropertyContainer {

    GENERATED_BODY()

    UPROPERTY( EditAnywhere, BlueprintReadWrite ) TArray< FSSGS_KeyValuePair > properties;

};

typedef TArray< FSSGS_KeyValuePair > TSSGS_ObjectDef;

UCLASS( BlueprintType, meta = ( Category = "Gamesense|Types" ) )
class STEELSERIESGAMESENSE_API USSGS_FrameObject : public USSGS_Frame {

    GENERATED_BODY()

public:

    UFUNCTION( BlueprintCallable, BlueprintPure, Category = "Gamesense|EventData" )
    static USSGS_FrameObject* MakeFrameObject( const TArray< FSSGS_KeyValuePair >& properties );

    UFUNCTION( BlueprintCallable, BlueprintPure, Category = "Gamesense|EventData" )
    static FSSGS_KeyValuePair MakePropertyBool( const FString& name, bool value );

    UFUNCTION( BlueprintCallable, BlueprintPure, Category = "Gamesense|EventData" )
    static FSSGS_KeyValuePair MakePropertyByte( const FString& name, uint8 value );

    UFUNCTION( BlueprintCallable, BlueprintPure, Category = "Gamesense|EventData" )
    static FSSGS_KeyValuePair MakePropertyInt( const FString& name, int32 value );

    UFUNCTION( BlueprintCallable, BlueprintPure, Category = "Gamesense|EventData" )
    static FSSGS_KeyValuePair MakePropertyFloat( const FString& name, float value );

    UFUNCTION( BlueprintCallable, BlueprintPure, Category = "Gamesense|EventData" )
    static FSSGS_KeyValuePair MakePropertyString( const FString& name, const FString& value );

    UFUNCTION( BlueprintCallable, BlueprintPure, Category = "Gamesense|EventData" )
    static FSSGS_KeyValuePair MakePropertyObject( const FString& name, const TArray< FSSGS_KeyValuePair >& objectProperties );

    UFUNCTION( BlueprintCallable, BlueprintPure, Category = "Gamesense|EventData" )
    static FSSGS_KeyValuePair MakePropertyBoolArray( const FString& name, const TArray< bool >& value );

    UFUNCTION( BlueprintCallable, BlueprintPure, Category = "Gamesense|EventData" )
    static FSSGS_KeyValuePair MakePropertyByteArray( const FString& name, const TArray< uint8 >& value );

    UFUNCTION( BlueprintCallable, BlueprintPure, Category = "Gamesense|EventData" )
    static FSSGS_KeyValuePair MakePropertyIntArray( const FString& name, const TArray< int32 >& value );

    UFUNCTION( BlueprintCallable, BlueprintPure, Category = "Gamesense|EventData" )
    static FSSGS_KeyValuePair MakePropertyFloatArray( const FString& name, const TArray< float >& value );

    UFUNCTION( BlueprintCallable, BlueprintPure, Category = "Gamesense|EventData" )
    static FSSGS_KeyValuePair MakePropertyStringArray( const FString& name, const TArray< FString >& value );

    UFUNCTION( BlueprintCallable, BlueprintPure, Category = "Gamesense|EventData" )
    static FSSGS_KeyValuePair MakePropertyObjectArray( const FString& name, const TArray< FSSGS_PropertyContainer >& value );

    TSharedPtr< FJsonValue > Convert() const;

public:

    UPROPERTY() TArray< FSSGS_KeyValuePair > properties;

};
