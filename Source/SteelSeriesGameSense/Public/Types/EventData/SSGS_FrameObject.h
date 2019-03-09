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


enum ESSGS_PropertyVariant {
    PropertyVariant_Invalid = 0,
    PropertyVariant_Bool,
    PropertyVariant_Uint8,
    PropertyVariant_Int32,
    PropertyVariant_Float,
    PropertyVariant_String,
    PropertyVariant_BoolArray,
    PropertyVariant_Uint8Array,
    PropertyVariant_Int32Array,
    PropertyVariant_FloatArray,
    PropertyVariant_StringArray
};

USTRUCT( BlueprintType, meta = ( Category = "Gamesense|Types" ) )
struct STEELSERIESGAMESENSE_API FSSGS_PropertyValuePair : public FSSGS_JsonConvertable {

    GENERATED_BODY()

public:

    FSSGS_PropertyValuePair() : _type( PropertyVariant_Invalid ) {};
    FSSGS_PropertyValuePair( const FString& n, bool v ) : _name( n ), _type( PropertyVariant_Bool ), _variant( v ) {}
    FSSGS_PropertyValuePair( const FString& n, uint8 v ) : _name( n ), _type( PropertyVariant_Uint8 ), _variant( v ) {}
    FSSGS_PropertyValuePair( const FString& n, int32 v ) : _name( n ), _type( PropertyVariant_Int32 ), _variant( v ) {}
    FSSGS_PropertyValuePair( const FString& n, float v ) : _name( n ), _type( PropertyVariant_Float ), _variant( v ) {}
    FSSGS_PropertyValuePair( const FString& n, const FString& v ) : _name( n ), _type( PropertyVariant_String ), _variant( v ) {}
    FSSGS_PropertyValuePair( const FString& n, const TArray< bool >& v ) : _name( n ), _type( PropertyVariant_BoolArray ), _variant( v ) {}
    FSSGS_PropertyValuePair( const FString& n, const TArray< uint8 >& v ) : _name( n ), _type( PropertyVariant_Uint8Array ), _variant( v ) {}
    FSSGS_PropertyValuePair( const FString& n, const TArray< int32 >& v ) : _name( n ), _type( PropertyVariant_Int32Array ), _variant( v ) {}
    FSSGS_PropertyValuePair( const FString& n, const TArray< float >& v ) : _name( n ), _type( PropertyVariant_FloatArray ), _variant( v ) {}
    FSSGS_PropertyValuePair( const FString& n, const TArray< FString >& v ) : _name( n ), _type( PropertyVariant_StringArray ), _variant( v ) {}

    void Decorate( TSharedPtr< FJsonObject > obj ) const;

private:

    typedef ssgs::Union< bool, uint8, int32, float, FString > Type;
    typedef ssgs::Union< TArray< bool >,
        TArray< uint8 >,
        TArray< int32 >,
        TArray< float >,
        TArray< FString > > ArrayType;

    FString _name;
    ESSGS_PropertyVariant _type;
    ssgs::Union< Type, ArrayType > _variant;

};

typedef TArray< FSSGS_PropertyValuePair > TSSGS_ObjectDef;

UCLASS( BlueprintType, meta = ( Category = "Gamesense|Types" ) )
class STEELSERIESGAMESENSE_API USSGS_FrameObject : public USSGS_Frame {

    GENERATED_BODY()

public:

    UFUNCTION( BlueprintCallable, BlueprintPure, Category = "Gamesense|EventData" )
    static USSGS_FrameObject* MakeFrameObject( const TArray< FSSGS_PropertyValuePair >& properties );

    UFUNCTION( BlueprintCallable, BlueprintPure, Category = "Gamesense|EventData" )
    static FSSGS_PropertyValuePair MakePropertyBool( const FString& name, bool value );

    UFUNCTION( BlueprintCallable, BlueprintPure, Category = "Gamesense|EventData" )
    static FSSGS_PropertyValuePair MakePropertyByte( const FString& name, uint8 value );

    UFUNCTION( BlueprintCallable, BlueprintPure, Category = "Gamesense|EventData" )
    static FSSGS_PropertyValuePair MakePropertyInt( const FString& name, int32 value );

    UFUNCTION( BlueprintCallable, BlueprintPure, Category = "Gamesense|EventData" )
    static FSSGS_PropertyValuePair MakePropertyFloat( const FString& name, float value );

    UFUNCTION( BlueprintCallable, BlueprintPure, Category = "Gamesense|EventData" )
    static FSSGS_PropertyValuePair MakePropertyString( const FString& name, const FString& value );

    UFUNCTION( BlueprintCallable, BlueprintPure, Category = "Gamesense|EventData" )
    static FSSGS_PropertyValuePair MakePropertyBoolArray( const FString& name, const TArray< bool >& value );

    UFUNCTION( BlueprintCallable, BlueprintPure, Category = "Gamesense|EventData" )
    static FSSGS_PropertyValuePair MakePropertyByteArray( const FString& name, const TArray< uint8 >& value );

    UFUNCTION( BlueprintCallable, BlueprintPure, Category = "Gamesense|EventData" )
    static FSSGS_PropertyValuePair MakePropertyIntArray( const FString& name, const TArray< int32 >& value );

    UFUNCTION( BlueprintCallable, BlueprintPure, Category = "Gamesense|EventData" )
    static FSSGS_PropertyValuePair MakePropertyFloatArray( const FString& name, const TArray< float >& value );

    UFUNCTION( BlueprintCallable, BlueprintPure, Category = "Gamesense|EventData" )
    static FSSGS_PropertyValuePair MakePropertyStringArray( const FString& name, const TArray< FString >& value );

    TSharedPtr< FJsonValue > Convert() const;

    UPROPERTY() TArray< FSSGS_PropertyValuePair > properties;

};
