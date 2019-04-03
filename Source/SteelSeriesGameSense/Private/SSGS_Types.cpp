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


#include <algorithm>
#include "Types/SSGS_Payload.h"
#include "Runtime/JsonUtilities/Public/JsonObjectConverter.h"


#define LOG( lvl, format, ... ) UE_LOG( SSGS_Client, lvl, format, ##__VA_ARGS__ )


template <typename T>
FString _getEnumString( const FString& name, T value )
{
    static const UEnum* pEnum;
    if ( !pEnum ) {
        pEnum = FindObject< UEnum >( ( UObject* )ANY_PACKAGE, *name, true );
        if ( !pEnum ) {
            return FString( TEXT( "Enum class \"" ) ) + name + FString( TEXT( "\" not found" ) );
        }
    }

    return pEnum->GetDisplayNameTextByValue( ( int64 )value ).ToString();
}

#define GetEnumString(TYPE,VALUE) _getEnumString( #TYPE, VALUE )

template <typename T>
T* _createUObj()
{
    T* p = NewObject< T >();
    p->AddToRoot();
    return p;
}

typedef TArray< TSharedPtr < FJsonValue > > TJsonValues;

template < typename CustomUStructType >
TJsonValues _getArrayOfJsonValuesFromUStructs( const TArray< CustomUStructType >& arr )
{
    TJsonValues ret;

    for ( const CustomUStructType& obj : arr ) {
        TSharedPtr< FJsonObject > jsonObj = FJsonObjectConverter::UStructToJsonObject< CustomUStructType >( obj );
        ret.Add( MakeShared< FJsonValueObject >( jsonObj ) );
    }

    return ret;
}

template < typename T >
TJsonValues _getArrayOfJsonValues( const TArray< T >& arr )
{
    TJsonValues ret;

    static_assert( std::is_base_of< FSSGS_JsonConvertable, T >::value,
                   "invalid template argument" );

    for ( const T& obj : arr ) {
        ret.Add( obj.Convert() );
    }

    return ret;
}

template < typename T >
TJsonValues _getArrayOfJsonValues( const TArray< T* >& arr )
{
    TJsonValues ret;

    static_assert( std::is_base_of< FSSGS_JsonConvertable, T >::value,
                   "invalid template argument" );

    for ( const T* obj : arr ) {
        ret.Add( obj->Convert() );
    }

    return ret;
}

template < typename NumberType >
TJsonValues _getArrayOfJsonValuesNumbers( const TArray< NumberType >& arr )
{
    TJsonValues ret;

    static_assert( std::is_arithmetic< NumberType >::value,
                   "invalid template argument" );

    for ( const NumberType& v : arr ) {
        ret.Add( MakeShared< FJsonValueNumber >( v ) ) ;
    }

    return ret;
}

TJsonValues _getArrayOfJsonValuesBoolean( const TArray< bool >& arr )
{
    TJsonValues ret;

    for ( const bool& v : arr ) {
        ret.Add( MakeShared< FJsonValueBoolean >( v ) );
    }

    return ret;
}

TJsonValues _getArrayOfJsonValuesString( const TArray< FString >& arr )
{
    TJsonValues ret;

    for ( const FString& v : arr ) {
        ret.Add( MakeShared< FJsonValueString >( v ) );
    }

    return ret;
}

TSharedPtr< FJsonValue > _makeJsonObject( const TSSGS_ObjectDef& objDef )
{
    auto objProp = MakeShared< FJsonObject >();

    for ( const auto& prop : objDef )
        prop.Decorate( objProp );

    return MakeShared< FJsonValueObject >( objProp );
}

// ****** FSSGS_RateRange ******
FSSGS_RateRange::FSSGS_RateRange() {}

FSSGS_RateRange::FSSGS_RateRange( const TArray< FSSGS_Frequency >& frequency, const TArray< FSSGS_RepeatLimit >& repeatLimit ) :
    frequency( frequency ),
    repeat_limit( repeatLimit )
{}

FSSGS_RateRange::FSSGS_RateRange( const TArray< FSSGS_FrequencyRepeatLimitPair >& v )
{
    frequency.Reserve( v.Num() );
    repeat_limit.Reserve( v.Num() );

    for ( const auto pair : v ) {
        frequency.Add( FSSGS_Frequency{ pair.low, pair.high, pair.frequency } );
        repeat_limit.Add( FSSGS_RepeatLimit{ pair.low, pair.high, pair.repeat_limit } );
    }
}


// ****** USSGS_RateSpecification ******
USSGS_RateSpecification* USSGS_RateSpecification::MakeStaticRate( int32 frequency, int32 repeat_limit )
{
    USSGS_RateSpecification* p = _createUObj< USSGS_RateSpecification >();
    p->_mode = RateMode_Static;
    p->_rate.Set< FSSGS_RateStatic >( FSSGS_RateStatic{ frequency, repeat_limit } );
    return p;
}

USSGS_RateSpecification* USSGS_RateSpecification::MakeRangedRate( const TArray< FSSGS_FrequencyRepeatLimitPair >& v )
{
    USSGS_RateSpecification* p = _createUObj< USSGS_RateSpecification >();
    p->_mode = RateMode_Range;
    p->_rate.Set< FSSGS_RateRange >( FSSGS_RateRange( v ) );
    return p;
}

TSharedPtr< FJsonValue > USSGS_RateSpecification::Convert() const
{
    switch ( _mode ) {
    
    case RateMode_Static: {
        TSharedPtr< FJsonObject > obj = FJsonObjectConverter::UStructToJsonObject( _rate.Get< FSSGS_RateStatic >() );
        return MakeShared< FJsonValueObject >( obj );
    }

    case RateMode_Range: {
        TSharedPtr< FJsonObject > obj = FJsonObjectConverter::UStructToJsonObject( _rate.Get< FSSGS_RateRange >() );
        return MakeShared< FJsonValueObject >( obj );
    }
    
    }

    return MakeShared< FJsonValueNull >();
}

// ****** FSSGS_ColorRangeStatic ******
FSSGS_ColorRangeStatic::FSSGS_ColorRangeStatic( int32 l, int32 h, const FSSGS_RGB& c ) :
    low( l ),
    high( h ),
    color( c )
{}

// ****** FSSGS_ColorRangeGradient ******
FSSGS_ColorRangeGradient::FSSGS_ColorRangeGradient( int32 l, int32 h, const FSSGS_RGB& zero, const FSSGS_RGB& hundred ) :
    low( l ),
    high( h ),
    color( FSSGS_ColorGradient{ { zero, hundred } } )
{}

// ****** FSSGS_ColorRange ******
FSSGS_ColorRange::FSSGS_ColorRange( const FSSGS_ColorRangeStatic& v ) :
    _type( RangeColorEffect_Static ),
    _color( v )
{}

FSSGS_ColorRange::FSSGS_ColorRange( const FSSGS_ColorRangeGradient& v ) :
    _type( RangeColorEffect_Gradient ),
    _color( v )
{}

TSharedPtr< FJsonValue > FSSGS_ColorRange::Convert() const
{
    TSharedPtr< FJsonObject > obj;

    switch ( _type ) {
    case RangeColorEffect_Static:
        obj = FJsonObjectConverter::UStructToJsonObject( _color.Get< FSSGS_ColorRangeStatic >() );
        break;
    case RangeColorEffect_Gradient:
        obj = FJsonObjectConverter::UStructToJsonObject( _color.Get< FSSGS_ColorRangeGradient >() );
        break;
    default:
        break;
    }

    return MakeShared< FJsonValueObject >( obj );
}

// ****** USSGS_ColorEffectSpecificationStatic ******
USSGS_ColorEffectSpecificationStatic* USSGS_ColorEffectSpecificationStatic::MakeStaticColorEffect( const FSSGS_RGB& color )
{
    USSGS_ColorEffectSpecificationStatic* p = _createUObj< USSGS_ColorEffectSpecificationStatic >();
    p->color = color;
    return p;
}

TSharedPtr< FJsonValue > USSGS_ColorEffectSpecificationStatic::Convert() const
{
    auto obj = FJsonObjectConverter::UStructToJsonObject( color );
    return MakeShared< FJsonValueObject >( obj );
}

// ****** USSGS_ColorEffectSpecificationGradient ******
USSGS_ColorEffectSpecificationGradient* USSGS_ColorEffectSpecificationGradient::MakeGradientColorEffect( const FSSGS_RGB& zero, const FSSGS_RGB& hundred )
{
    USSGS_ColorEffectSpecificationGradient* p = _createUObj< USSGS_ColorEffectSpecificationGradient >();
    p->gradient = FSSGS_ColorGradient{ FSSGS_Gradient{ zero, hundred } };
    return p;
}

TSharedPtr< FJsonValue > USSGS_ColorEffectSpecificationGradient::Convert() const
{
    auto obj = FJsonObjectConverter::UStructToJsonObject( gradient );
    return MakeShared< FJsonValueObject >( obj );
}

// ****** USSGS_ColorEffectSpecificationRanges ******
USSGS_ColorEffectSpecificationRanges* USSGS_ColorEffectSpecificationRanges::MakeRangeColorEffect( const TArray< FSSGS_ColorRange >& v )
{
    USSGS_ColorEffectSpecificationRanges* p = _createUObj< USSGS_ColorEffectSpecificationRanges >();
    p->ranges = v;
    return p;
}

FSSGS_ColorRange USSGS_ColorEffectSpecificationRanges::MakeStaticColorRange( int32 low, int32 high, const FSSGS_RGB& color )
{
    return FSSGS_ColorRange( FSSGS_ColorRangeStatic( low,
                                                     high,
                                                     color ) );
}

FSSGS_ColorRange USSGS_ColorEffectSpecificationRanges::MakeGradientColorRange( int32 low, int32 high, const FSSGS_RGB& zero, const FSSGS_RGB& hundred )
{
    return FSSGS_ColorRange( FSSGS_ColorRangeGradient( low,
                                                       high,
                                                       zero,
                                                       hundred ) );
}

TSharedPtr< FJsonValue > USSGS_ColorEffectSpecificationRanges::Convert() const
{
    TJsonValues arr( _getArrayOfJsonValues( ranges ) );

    return MakeShared< FJsonValueArray >( arr );
}


// ****** FSSGS_HandlerColor ******
FSSGS_HandlerColor::FSSGS_HandlerColor() : color( nullptr ), rate( nullptr ) {}

FSSGS_HandlerColor::FSSGS_HandlerColor( const FSSGS_HandlerColor& other ) : FSSGS_HandlerColor()
{
    deviceZone = other.deviceZone;
    mode = other.mode;
    color = other.color;
    rate = other.rate;
}

FSSGS_HandlerColor::FSSGS_HandlerColor( const FSSGS_IlluminationDeviceZone& dz, ESSGS_IlluminationMode im, USSGS_ColorEffectSpecification* colorSpec, USSGS_RateSpecification* rateSpec ) :
    deviceZone( dz ),
    mode( im ),
    color( colorSpec ),
    rate( rateSpec )
{}

const FSSGS_HandlerColor& FSSGS_HandlerColor::operator=( const FSSGS_HandlerColor& rhs )
{
    if ( this != &rhs ) {
        deviceZone = rhs.deviceZone;
        mode = rhs.mode;
        color = rhs.color;
        rate = rhs.rate;
    }

    return *this;
}

FSSGS_HandlerColor::~FSSGS_HandlerColor()
{
    // let the GC work
    color = nullptr;
    rate = nullptr;
}

TSharedPtr< FJsonValue > FSSGS_HandlerColor::Convert() const
{
    auto obj = MakeShared< FJsonObject >();

    obj->SetStringField( "device-type", deviceZone.device );

    if ( deviceZone.zoneType == FSSGS_IlluminationDeviceZone::named )
        obj->SetStringField( "zone", deviceZone.namedZone() );
    else if ( deviceZone.zoneType == FSSGS_IlluminationDeviceZone::custom )
        obj->SetArrayField( "custom-zone-keys", _getArrayOfJsonValuesNumbers( deviceZone.customZone() ) );

    obj->SetStringField( "mode", GetEnumString( ESSGS_IlluminationMode, mode ).ToLower() );
    
    if ( color )
        obj->SetField( "color", color->Convert() );

    if ( rate )
        obj->SetField( "rate", rate->Convert() );

    return MakeShared< FJsonValueObject >( obj );
}


// ****** FSSGS_TactileEffectPredefined ******
TSharedPtr< FJsonValue > FSSGS_TactileEffectPredefined::Convert() const
{
    auto obj = MakeShared< FJsonObject >();

    obj->SetStringField( "type", type.name );
    obj->SetNumberField( "delay-ms", delay_ms );

    return MakeShared< FJsonValueObject >( obj );
}


// ****** FSSGS_TactileEffectCustom ******
TSharedPtr< FJsonValue > FSSGS_TactileEffectCustom::Convert() const
{
    auto obj = MakeShared< FJsonObject >();

    obj->SetStringField( "type", _type );
    obj->SetNumberField( "length-ms", length_ms );
    obj->SetNumberField( "delay-ms", delay_ms );

    return MakeShared< FJsonValueObject >( obj );
}

// ****** FSSGS_TactilePatternStatic ******
FSSGS_TactilePatternStatic::FSSGS_TactilePatternStatic( const FSSGS_TactileEffectPredefined& v ) :
    _type( TactilePatternStatic_Predefined ),
    _pattern( v )
{}

FSSGS_TactilePatternStatic::FSSGS_TactilePatternStatic( const FSSGS_TactileEffectCustom& v ) :
    _type( TactilePatternStatic_Custom ),
    _pattern( v )
{}

TSharedPtr< FJsonValue > FSSGS_TactilePatternStatic::Convert() const
{
    switch ( _type ) {

    case TactilePatternStatic_Predefined:
        return _pattern.Get< FSSGS_TactileEffectPredefined >().Convert();
        break;

    case TactilePatternStatic_Custom:
        return _pattern.Get< FSSGS_TactileEffectCustom >().Convert();
        break;

    default:
        return MakeShared< FJsonValueNull >();
        break;

    }
}

// ****** FSSGS_TactilePatternRange ******
FSSGS_TactilePatternRange::FSSGS_TactilePatternRange( int32 low, int32 high, const TArray< FSSGS_TactilePatternStatic >& v ) :
    low( low ),
    high( high ),
    pattern( v )
{}

TSharedPtr< FJsonValue > FSSGS_TactilePatternRange::Convert() const
{
    auto obj = MakeShared< FJsonObject >();

    obj->SetNumberField( "low", low );
    obj->SetNumberField( "high", high );
    obj->SetArrayField( "pattern", _getArrayOfJsonValues( pattern ) );

    return MakeShared< FJsonValueObject >( obj );
}


// ****** USSGS_TactilePatternSpecificationStatic ******
USSGS_TactilePatternSpecificationStatic* USSGS_TactilePatternSpecificationStatic::MakeStaticTactilePattern( const TArray< FSSGS_TactilePatternStatic >& pattern )
{
    USSGS_TactilePatternSpecificationStatic* p = _createUObj< USSGS_TactilePatternSpecificationStatic >();
    p->_pattern = pattern;
    return p;
}

FSSGS_TactilePatternStatic USSGS_TactilePatternSpecificationStatic::MakeStaticWithPredefinedEffect( const FSSGS_PredefinedTactilePattern& type, int32 delay_ms )
{
    return FSSGS_TactilePatternStatic( FSSGS_TactileEffectPredefined( type,
                                                                      delay_ms ) );
}

FSSGS_TactilePatternStatic USSGS_TactilePatternSpecificationStatic::MakeStaticWithCustomEffect( int32 length_ms, int32 delay_ms )
{
    return FSSGS_TactilePatternStatic( FSSGS_TactileEffectCustom( length_ms,
                                                                  delay_ms ) );
}

TArray<FSSGS_TactilePatternStatic> USSGS_TactilePatternSpecificationStatic::MakeStaticEmptyPattern( )
{
    return TArray<FSSGS_TactilePatternStatic>();
}

TSharedPtr< FJsonValue > USSGS_TactilePatternSpecificationStatic::Convert() const
{
    return MakeShared< FJsonValueArray >( _getArrayOfJsonValues( _pattern ) );
}

// ****** USSGS_TactilePatternSpecificationRanges ******
USSGS_TactilePatternSpecificationRanges* USSGS_TactilePatternSpecificationRanges::MakeRangedTactilePattern( const TArray< FSSGS_TactilePatternRange >& ranges )
{
    USSGS_TactilePatternSpecificationRanges* p = _createUObj< USSGS_TactilePatternSpecificationRanges >();
    p->_pattern = ranges;
    return p;
}

TSharedPtr< FJsonValue > USSGS_TactilePatternSpecificationRanges::Convert() const
{
    return MakeShared< FJsonValueArray >( _getArrayOfJsonValues( _pattern ) );
}

// ****** FSSGS_HandlerTactile ******
FSSGS_HandlerTactile::FSSGS_HandlerTactile() : pattern( nullptr ), rate( nullptr ) {}

FSSGS_HandlerTactile::FSSGS_HandlerTactile( const FSSGS_HandlerTactile& other ) : FSSGS_HandlerTactile()
{
    deviceZone = other.deviceZone;
    mode = other.mode;
    pattern = other.pattern;
    rate = other.rate;
}

FSSGS_HandlerTactile::FSSGS_HandlerTactile( const FSSGS_TactileDeviceZone& deviceZone, USSGS_TactilePatternSpecification* pattern, USSGS_RateSpecification* rate ) :
    deviceZone( deviceZone ),
    pattern( pattern ),
    rate( rate )
{}

const FSSGS_HandlerTactile& FSSGS_HandlerTactile::operator=( const FSSGS_HandlerTactile& rhs )
{
    if ( this != &rhs ) {
        deviceZone = rhs.deviceZone;
        mode = rhs.mode;
        pattern = rhs.pattern;
        rate = rhs.rate;
    }

    return *this;
}

FSSGS_HandlerTactile::~FSSGS_HandlerTactile()
{
    // let the GC work
    pattern = nullptr;
    rate = nullptr;
}

TSharedPtr< FJsonValue > FSSGS_HandlerTactile::Convert() const
{
    auto obj = MakeShared< FJsonObject >();

    obj->SetStringField( "device-type", deviceZone.device );
    obj->SetStringField( "zone", deviceZone.zone );
    obj->SetStringField( "mode", mode );
    
    if ( pattern )
        obj->SetField( "pattern", pattern->Convert() );

    if ( rate )
        obj->SetField( "rate", rate->Convert() );

    return MakeShared< FJsonValueObject >( obj );
}

// ****** FSSGS_LineDataAccessor ******
void FSSGS_LineDataAccessor::Decorate( TSharedPtr< FJsonObject > obj ) const
{
    switch ( _type ) {

    case FrameKey:
        obj->SetStringField( "context-frame-key", _value );
        break;

    case GoLispExpr:
        obj->SetStringField( "arg", _value );
        break;

    }
}

// ****** FSSGS_LineData ******
TSharedPtr< FJsonValue > FSSGS_LineData::Convert() const
{
    auto obj = MakeShared< FJsonObject >();

    switch ( _variant_type ) {

    case FSSGS_LineData::TxtModifiers: {
        auto& v = _variant.Get< FSSGS_LineDataText >();
        obj->SetBoolField( "has-text", v.has_text );
        obj->SetStringField( "prefix", v.prefix );
        obj->SetStringField( "suffix", v.suffix );
        obj->SetBoolField( "bold", v.bold );
        obj->SetNumberField( "wrap", v.wrap );
        break;
    }

    case FSSGS_LineData::ProgressBar: {
        auto& v = _variant.Get< FSSGS_LineDataProgressBar >();
        obj->SetBoolField( "has-progress-bar", v.has_progress_bar );
        break;
    }

    }

    _dataAccessor.Decorate( obj );

    return MakeShared< FJsonValueObject >( obj );
}

// ****** FSSGS_FrameModifiers ******
void FSSGS_FrameModifiers::Decorate( TSharedPtr< FJsonObject > obj ) const
{
    obj->SetNumberField( "length-millis", length_millis );

    switch ( _repeats_type ) {

    case FSSGS_FrameModifiers::Boolean:
        obj->SetBoolField( "repeats", _repeats.Get< bool >() );
        break;

    case FSSGS_FrameModifiers::Integer:
        obj->SetNumberField( "repeats", _repeats.Get< int32 >() );
        break;

    }
}

// ****** FSSGS_FrameDataSingleLine ******
TSharedPtr< FJsonValue > FSSGS_FrameDataSingleLine::Convert() const
{
    auto obj = lineData.Convert()->AsObject();

    frameModifiers.Decorate( obj );
    obj->SetNumberField( "icon-id", ( uint8 )icon_id );

    return MakeShared< FJsonValueObject >( obj );
}

// ****** FSSGS_FrameDataMultiLine ******
TSharedPtr< FJsonValue > FSSGS_FrameDataMultiLine::Convert() const
{
    auto obj = MakeShared< FJsonObject >();

    frameModifiers.Decorate( obj );
    obj->SetNumberField( "icon-id", ( uint8 )icon_id );

    if ( lines.Num() > 0 )
        obj->SetArrayField( "lines", _getArrayOfJsonValues( lines ) );

    return MakeShared< FJsonValueObject >( obj );
}

// ****** USSGS_ImageDataTexture2D ******
USSGS_ImageDataTexture2D* USSGS_ImageDataTexture2D::MakeImageDataFromTexture( UTexture2D* pTex )
{
    USSGS_ImageDataTexture2D* p = _createUObj< USSGS_ImageDataTexture2D >();
    p->_pTex = pTex;
    return p;
}

TArray< uint8 > USSGS_ImageDataTexture2D::GetData( const FSSGS_ScreenDeviceZone& dz )
{
    TArray< uint8 > data;

    if ( !_pTex ) {
        LOG( Warning, TEXT( "Null texture resource" ) );
        return data;
    }

    if ( dz.w() < _pTex->GetSizeX() ) {
        // do nothing if supplied texture is too wide
        LOG( Warning, TEXT( "Texture too wide for target device" ) );
        return data;
    }

    int targetSize = dz.w() * dz.h();
    if ( targetSize == 0 )
    {
        LOG( Error, TEXT( "Using generic screen device for image data" ) );
        return data;
    }

    int texSize = _pTex->GetSizeX() * std::min(_pTex->GetSizeY(), dz.h());

    // see if we can read pixels before attempting to access them
    if ( ( _pTex->CompressionSettings != TextureCompressionSettings::TC_VectorDisplacementmap ) ||
         ( _pTex->PlatformData->Mips.Num() != 1 ) ||
         ( _pTex->SRGB != false ) )
    {
        LOG( Error, TEXT( "Invalid texture format" ) );
        return data;
    }

    // get pixels
    const FColor* pData = static_cast< const FColor* >( _pTex->PlatformData->Mips[ 0 ].BulkData.LockReadOnly() );
    if ( !pData )
    {
        LOG( Error, TEXT( "Failed accessing colors from texture resource" ) );
        return data ;
    }

    TArray< uint8 > luma;
    luma.AddZeroed( texSize );

    // Crude approximation of luminance
    // Y = ( 3R + 4G + B ) / 8
    for ( int idx = 0; idx < texSize; ++idx ) {
        luma[ idx ] = ( ( pData[ idx ].R << 1 ) + pData[ idx ].R +
                        ( pData[ idx ].G << 2 ) +
                        ( pData[ idx ].B ) ) >> 3;
    }

    _pTex->PlatformData->Mips[ 0 ].BulkData.Unlock();

    // threshold and pack
    int idx = 0;
    data.AddZeroed( luma.Num() / 8 );
    for ( uint8& v : data )
    {
        // apply thresholding at 50% intensity
        v = ( ( !!( luma[ idx ] & 0x80 ) ) << 7 ) |
            ( ( !!( luma[ idx + 1 ] & 0x80 ) ) << 6 ) |
            ( ( !!( luma[ idx + 2 ] & 0x80 ) ) << 5 ) |
            ( ( !!( luma[ idx + 3 ] & 0x80 ) ) << 4 ) |
            ( ( !!( luma[ idx + 4 ] & 0x80 ) ) << 3 ) |
            ( ( !!( luma[ idx + 5 ] & 0x80 ) ) << 2 ) |
            ( ( !!( luma[ idx + 6 ] & 0x80 ) ) << 1 ) |
            ( ( !!( luma[ idx + 7 ] & 0x80 ) ) );

        idx += 8;
    }

    // pad with zeroes
    data.AddZeroed( ( targetSize - texSize ) / 8 );

    return data;
}

// ****** USSGS_ImageDataArray ******
USSGS_ImageDataArray* USSGS_ImageDataArray::MakeImageDataFromArray( TArray< uint8 >&& packedBinaryImage )
{
    USSGS_ImageDataArray* p = _createUObj< USSGS_ImageDataArray >();
    p->_arr = packedBinaryImage;
    return p;
}

USSGS_ImageDataArray* USSGS_ImageDataArray::MakeImageDataFromArray( const TArray< uint8 >& packedBinaryImage )
{
    USSGS_ImageDataArray* p = _createUObj< USSGS_ImageDataArray >();
    p->_arr = packedBinaryImage;
    return p;
}

TArray< uint8 > USSGS_ImageDataArray::GetData( const FSSGS_ScreenDeviceZone& dz )
{
    return _arr;
}

// ****** FSSGS_FrameDataImage ******
FSSGS_FrameDataImage::FSSGS_FrameDataImage( USSGS_ImageDataSource* pSrc, const FSSGS_ScreenDeviceZone& dz, const FSSGS_FrameModifiers& frameModifiers ) :
    frameModifiers( frameModifiers ),
    dz( dz )
{
    if ( pSrc )
    {
        int targetArraySize = ( dz.h() * dz.w() ) / 8;
        if ( targetArraySize == 0 ) {
            LOG( Error, TEXT( "Using generic screen device for image data" ) );
        } else {

            imageData = pSrc->GetData( dz );
            if ( imageData.Num() != targetArraySize ) {
                LOG( Warning,
                     TEXT( "Invalid array length: have %d, need %d" ),
                     imageData.Num(), targetArraySize );

                // resulting array will be empty,
                // default as per GameSense SDK
                imageData.Empty();
            }

        }
    }
}

TSharedPtr< FJsonValue > FSSGS_FrameDataImage::Convert() const
{
    auto obj = MakeShared< FJsonObject >();

    obj->SetBoolField( "has-text", false );
    obj->SetArrayField( "image-data", _getArrayOfJsonValuesNumbers( imageData ) );

    frameModifiers.Decorate( obj );

    return MakeShared< FJsonValueObject >( obj );
}

// ****** FSSGS_FrameData ******
TSharedPtr< FJsonValue > FSSGS_FrameData::Convert() const
{
    switch ( _variant_type ) {

    case FSSGS_FrameData::SingleLine:
        return _variant.Get< FSSGS_FrameDataSingleLine >().Convert();
        break;

    case FSSGS_FrameData::MultiLine:
        return _variant.Get< FSSGS_FrameDataMultiLine >().Convert();
        break;

    case FSSGS_FrameData::Image:
        return _variant.Get< FSSGS_FrameDataImage >().Convert();

    default:
        return MakeShared< FJsonValueNull >();
        break;

    }
}

// ****** FSSGS_FrameDataRange ******
TSharedPtr< FJsonValue > FSSGS_FrameDataRange::Convert() const
{
    auto obj = MakeShared< FJsonObject >();

    obj->SetNumberField( "low", low );
    obj->SetNumberField( "high", high );
    obj->SetArrayField( "datas", _getArrayOfJsonValues( datas ) );

    return MakeShared< FJsonValueObject >( obj );
}

// ****** USSGS_ScreenDataSpecification ******
FSSGS_FrameData USSGS_ScreenDataSpecification::MakeSingleLineFrameData( const FSSGS_LineData& lineData, FSSGS_FrameModifiers frameModifiers, ESSGS_EventIconId icon_id )
{
    return FSSGS_FrameData( FSSGS_FrameDataSingleLine{ lineData,
                                                       frameModifiers,
                                                       icon_id } );
}

FSSGS_FrameData USSGS_ScreenDataSpecification::MakeMultiLineFrameData( const TArray< FSSGS_LineData >& lines, FSSGS_FrameModifiers frameModifiers, ESSGS_EventIconId icon_id )
{
    return FSSGS_FrameData( FSSGS_FrameDataMultiLine{ lines,
                                                      frameModifiers,
                                                      icon_id } );
}

FSSGS_FrameData USSGS_ScreenDataSpecification::MakeImageFrameData( USSGS_ImageDataSource*& pSrc, const FSSGS_ScreenDeviceZone& dz, FSSGS_FrameModifiers frameModifiers )
{
    return FSSGS_FrameData( FSSGS_FrameDataImage{ pSrc,
                                                  dz,
                                                  frameModifiers } );
}

FSSGS_LineData USSGS_ScreenDataSpecification::MakeTextLineData( const FSSGS_LineDataText& textModifiers, const FSSGS_LineDataAccessor& accessor )
{
    return FSSGS_LineData{ textModifiers,
                           accessor };
}

FSSGS_LineData USSGS_ScreenDataSpecification::MakeTextLineData( const FSSGS_LineDataText& textModifiers )
{
    return FSSGS_LineData{ textModifiers };
}

FSSGS_LineData USSGS_ScreenDataSpecification::MakeProgressBarLineData( const FSSGS_LineDataAccessor& accessor )
{
    return FSSGS_LineData{ FSSGS_LineDataProgressBar(),
                           accessor };
}

FSSGS_LineData USSGS_ScreenDataSpecification::MakeProgressBarLineData()
{
    return FSSGS_LineData{ FSSGS_LineDataProgressBar() };
}

FSSGS_FrameModifiers USSGS_ScreenDataSpecification::MakeFrameModifiers( int32 length_millis, bool repeats )
{
    return FSSGS_FrameModifiers{ length_millis, repeats };
}

FSSGS_FrameModifiers USSGS_ScreenDataSpecification::MakeFrameModifiersWithRepeatCount( int32 length_millis, int32 repeat_count )
{
    return FSSGS_FrameModifiers{ length_millis, repeat_count };
}

FSSGS_FrameModifiers USSGS_ScreenDataSpecification::MakeFrameModifiersWithNoRepeat( int32 length_millis )
{
    return FSSGS_FrameModifiers{ length_millis };
}

FSSGS_LineDataAccessor USSGS_ScreenDataSpecification::MakeContextFrameKeyAccessor( const FString& key )
{
    return FSSGS_LineDataAccessor::ContextFrameKey( key );
}

FSSGS_LineDataAccessor USSGS_ScreenDataSpecification::MakeGoLispExpressionAccessor( const FString& expr )
{
    return FSSGS_LineDataAccessor::GoLispExpression( expr );
}

// ****** USSGS_ScreenDataSpecificationStatic ******
USSGS_ScreenDataSpecificationStatic* USSGS_ScreenDataSpecificationStatic::MakeStaticScreenData( const TArray< FSSGS_FrameData >& datas )
{
    auto p = _createUObj< USSGS_ScreenDataSpecificationStatic >();
    p->datas = datas;
    return p;
}

TSharedPtr< FJsonValue > USSGS_ScreenDataSpecificationStatic::Convert() const
{
    return MakeShared< FJsonValueArray >( _getArrayOfJsonValues( datas ) );
}

// ****** USSGS_ScreenDataSpecificationRanges ******
USSGS_ScreenDataSpecificationRanges* USSGS_ScreenDataSpecificationRanges::MakeScreenDataRanges( const TArray< FSSGS_FrameDataRange >& datas )
{
    auto p = _createUObj< USSGS_ScreenDataSpecificationRanges >();
    p->datas = datas;
    return p;
}

TSharedPtr< FJsonValue > USSGS_ScreenDataSpecificationRanges::Convert() const
{
    return MakeShared< FJsonValueArray >( _getArrayOfJsonValues( datas ) );
}

// ****** FSSGS_HandlerScreen ******
FSSGS_HandlerScreen::FSSGS_HandlerScreen() : data( nullptr ) {}

FSSGS_HandlerScreen::FSSGS_HandlerScreen( const FSSGS_HandlerScreen& other ) :
    deviceZone( other.deviceZone ),
    mode( other.mode ),
    data( other.data )

{}

FSSGS_HandlerScreen::FSSGS_HandlerScreen( const FSSGS_ScreenDeviceZone& deviceZone, USSGS_ScreenDataSpecification* dataSpec ) :
    deviceZone( deviceZone ),
    data( dataSpec )
{}

const FSSGS_HandlerScreen& FSSGS_HandlerScreen::operator=( const FSSGS_HandlerScreen& rhs )
{
    if ( this != &rhs ) {
        deviceZone = rhs.deviceZone;
        mode = rhs.mode;
        data = rhs.data;
    }

    return *this;
}

FSSGS_HandlerScreen::~FSSGS_HandlerScreen()
{
    // let the GC work
    data = nullptr;
}

TSharedPtr< FJsonValue > FSSGS_HandlerScreen::Convert() const
{
    auto obj = MakeShared< FJsonObject >();

    obj->SetStringField( "device-type", deviceZone.device );
    obj->SetStringField( "zone", deviceZone.zone );
    obj->SetStringField( "mode", mode );

    if ( data )
        obj->SetField( "datas", data->Convert() );


    return MakeShared< FJsonValueObject >( obj );
}

// ****** USSGS_HandlerCollection ******
USSGS_HandlerCollection::~USSGS_HandlerCollection()
{
    _colorHandlers.Empty();
    _tactileHandlers.Empty();
}

USSGS_HandlerCollection* USSGS_HandlerCollection::MakeHandlerCollection()
{
    return _createUObj< USSGS_HandlerCollection >();
}

void USSGS_HandlerCollection::AddColorHandler( const FSSGS_HandlerColor& handler )
{
    _colorHandlers.Add( handler );
}

void USSGS_HandlerCollection::AddColorHandler( const FSSGS_IlluminationDeviceZone& deviceZone, ESSGS_IlluminationMode mode, USSGS_ColorEffectSpecification*& colorSpec, USSGS_RateSpecification* rateSpec )
{
    _colorHandlers.Add( FSSGS_HandlerColor( deviceZone,
                                            mode,
                                            colorSpec,
                                            rateSpec ) );
}

void USSGS_HandlerCollection::AddTactileHandler( const FSSGS_HandlerTactile& handler )
{
    _tactileHandlers.Add( handler );
}

void USSGS_HandlerCollection::AddTactileHandler( const FSSGS_TactileDeviceZone& deviceZone, USSGS_TactilePatternSpecification*& pattern, USSGS_RateSpecification* rate )
{
    _tactileHandlers.Add( FSSGS_HandlerTactile( deviceZone,
                                                pattern,
                                                rate ) );
}

void USSGS_HandlerCollection::AddScreenHandler( const FSSGS_ScreenDeviceZone& deviceZone, USSGS_ScreenDataSpecification*& data )
{
    _screenHandlers.Add( FSSGS_HandlerScreen( deviceZone,
                                              data ) );
}

TSharedPtr< FJsonValue > USSGS_HandlerCollection::Convert() const
{
    TJsonValues arr( _getArrayOfJsonValues( _colorHandlers ) );
    arr.Append( _getArrayOfJsonValues( _tactileHandlers ) );
    arr.Append( _getArrayOfJsonValues( _screenHandlers ) );

    return MakeShared< FJsonValueArray >( arr );
}


// ****** FSSGS_GameInfo ******
FSSGS_GameInfo::FSSGS_GameInfo() {};

FSSGS_GameInfo::FSSGS_GameInfo( const FString& game, const FString& displayName ) :
    game( game ),
    gameDisplayName( displayName )
{}

FSSGS_GameInfo::FSSGS_GameInfo( const FString& game, const FString& displayName, const FString& developer ) :
    game( game ),
    gameDisplayName( displayName ),
    developer( developer )
{}

TSharedPtr< FJsonValue > FSSGS_GameInfo::Convert() const
{
    auto obj = MakeShared< FJsonObject >();

    obj->SetStringField( "game", game );
    obj->SetStringField( "game_display_name", gameDisplayName );
    if ( !developer.IsEmpty() )
        obj->SetStringField( "developer", developer );

    return MakeShared< FJsonValueObject >( obj );
}


// ****** FSSGS_EventInfo ******
FSSGS_EventInfo::FSSGS_EventInfo() :
    game(),
    eventName(),
    minValue( 0 ),
    maxValue( 0 ),
    iconId( ESSGS_EventIconId::Default ),
    valueOptional( false )
{}

FSSGS_EventInfo::FSSGS_EventInfo( const FString& gameName, const FString& eventName, int32 minValue, int32 maxValue, ESSGS_EventIconId iconId, bool valueOptional ) :
    game( gameName ),
    eventName( eventName ),
    minValue( minValue ),
    maxValue( maxValue ),
    iconId( iconId ),
    valueOptional( valueOptional )
{}

TSharedPtr< FJsonValue > FSSGS_EventInfo::Convert() const
{
    auto obj = MakeShared< FJsonObject >();

    obj->SetStringField( "game", game );
    obj->SetStringField( "event", eventName );
    obj->SetNumberField( "min_value", minValue );
    obj->SetNumberField( "max_value", maxValue );
    obj->SetNumberField( "icon_id", ( uint32 )iconId );
    obj->SetBoolField( "value_optional", valueOptional );

    return MakeShared< FJsonValueObject >( obj );
}

// ****** FSSGS_EventBinding ******
FSSGS_EventBinding::FSSGS_EventBinding() :
    game(),
    eventName(),
    minValue( 0 ),
    maxValue( 0 ),
    iconId( ESSGS_EventIconId::Default ),
    handlers( nullptr ),
    valueOptional( false )
{
    handlers = _createUObj< USSGS_HandlerCollection >();
}

FSSGS_EventBinding::FSSGS_EventBinding( const FString& gameName, const FString& eventName, int32 minValue, int32 maxValue, ESSGS_EventIconId iconId, USSGS_HandlerCollection* handlers, bool valueOptional ) :
    game( gameName ),
    eventName( eventName ),
    minValue( minValue ),
    maxValue( maxValue ),
    iconId( iconId ),
    handlers( handlers ),
    valueOptional( valueOptional )
{}

FSSGS_EventBinding::~FSSGS_EventBinding()
{
    // let the GC work
    handlers = nullptr;
}

TSharedPtr< FJsonValue > FSSGS_EventBinding::Convert() const
{
    auto obj = MakeShared< FJsonObject >();

    obj->SetStringField( "game", game );
    obj->SetStringField( "event", eventName );
    obj->SetNumberField( "min_value", minValue );
    obj->SetNumberField( "max_value", maxValue );
    obj->SetNumberField( "icon_id", ( uint32 )iconId );
    obj->SetBoolField( "value_optional", valueOptional );

    if ( handlers ) {
        auto handlersJsonArray = handlers->Convert();
        const TJsonValues* pHandlers;

        if ( handlersJsonArray->TryGetArray( pHandlers ) ) {
            obj->SetArrayField( "handlers", *pHandlers );
        }
    }

    return MakeShared< FJsonValueObject >( obj );
}

// ****** FSSGS_EventUpdate ******
FSSGS_EventUpdate::FSSGS_EventUpdate() {}

FSSGS_EventUpdate::FSSGS_EventUpdate( const FString& game, const FString& eventName, const FSSGS_EventData& data ) :
    game( game ),
    eventName( eventName ),
    data( data )
{}

TSharedPtr< FJsonValue > FSSGS_EventUpdate::Convert() const
{
    auto obj = MakeShared< FJsonObject >();

    obj->SetStringField( "game", game );
    obj->SetStringField( "event", eventName );
    obj->SetField( "data", data.Convert() );

    return MakeShared< FJsonValueObject >( obj );
}

// ****** FSSGS_Event ******
FSSGS_Event::FSSGS_Event() {}

FSSGS_Event::FSSGS_Event( const FString& game, const FString& eventName ) :
    game( game ),
    eventName( eventName )
{}

TSharedPtr< FJsonValue > FSSGS_Event::Convert() const
{
    auto obj = MakeShared< FJsonObject >();

    obj->SetStringField( "game", game );
    obj->SetStringField( "event", eventName );

    return MakeShared< FJsonValueObject >( obj );
}

// ****** FSSGS_Game ******
FSSGS_Game::FSSGS_Game() {}

FSSGS_Game::FSSGS_Game( const FString& game ) :
    game( game )
{}

TSharedPtr< FJsonValue > FSSGS_Game::Convert() const
{
    auto obj = MakeShared< FJsonObject >();

    obj->SetStringField( "game", game );

    return MakeShared< FJsonValueObject >( obj );
}

// ****** FSSGS_EventData ******
TSharedPtr< FJsonValue > FSSGS_EventData::Convert() const
{
    auto obj = MakeShared< FJsonObject >();

    obj->SetNumberField( "value", value );
    if ( frame )
        obj->SetField( "frame", frame->Convert() );

    return MakeShared< FJsonValueObject >( obj );
}

// ****** FSSGS_KeyValuePair ******
void FSSGS_KeyValuePair::Decorate( TSharedPtr< FJsonObject > obj ) const
{
    switch ( _type ) {

    case Bool:
        obj->SetBoolField( _name, _variant.Get< Type >().Get< bool >() );
        break;

    case Uint8:
        obj->SetNumberField( _name, _variant.Get< Type >().Get< uint8 >() );
        break;

    case Int32:
        obj->SetNumberField( _name, _variant.Get< Type >().Get< int32 >() );
        break;

    case Float:
        obj->SetNumberField( _name, _variant.Get< Type >().Get< float >() );
        break;

    case String:
        obj->SetStringField( _name, _variant.Get< Type >().Get< FString >() );
        break;

    case Object: {
        auto& objectDef = _variant.Get< Type >().Get< TSSGS_ObjectDef >();
        obj->SetField( _name, _makeJsonObject( objectDef ) );
        break;
    }

    case BoolArray: {
        auto v = _variant.Get< ArrayType >().Get< TArray< bool > >();
        obj->SetArrayField( _name, _getArrayOfJsonValuesBoolean( v ) );
        break;
    }

    case Uint8Array: {
        auto v = _variant.Get< ArrayType >().Get< TArray< uint8 > >();
        obj->SetArrayField( _name, _getArrayOfJsonValuesNumbers( v ) );
        break;
    }

    case Int32Array: {
        auto v = _variant.Get< ArrayType >().Get< TArray< int32 > >();
        obj->SetArrayField( _name, _getArrayOfJsonValuesNumbers( v ) );
        break;
    }

    case FloatArray: {
        auto v = _variant.Get< ArrayType >().Get< TArray< float > >();
        obj->SetArrayField( _name, _getArrayOfJsonValuesNumbers( v ) );
        break;
    }

    case StringArray: {
        auto v = _variant.Get< ArrayType >().Get< TArray< FString > >();
        obj->SetArrayField( _name, _getArrayOfJsonValuesString( v ) );
        break;
    }

    case ObjectArray: {
        TJsonValues arr;
        auto& objects = _variant.Get< ArrayType >().Get< TArray< FSSGS_PropertyContainer > >();

        for ( const auto& shim : objects )
            arr.Add( _makeJsonObject( shim.properties ) );

        obj->SetArrayField( _name, arr );
        break;

    }

    }
}

// ****** USSGS_FrameObject ******
USSGS_FrameObject* USSGS_FrameObject::MakeFrameObject( const TSSGS_ObjectDef& properties )
{
    USSGS_FrameObject* p = _createUObj< USSGS_FrameObject >();
    p->properties = properties;
    return p;
}

FSSGS_KeyValuePair USSGS_FrameObject::MakePropertyBool( const FString& n, bool v )
{
    return FSSGS_KeyValuePair{ n, v };
}

FSSGS_KeyValuePair USSGS_FrameObject::MakePropertyByte( const FString& n, uint8 v )
{
    return FSSGS_KeyValuePair{ n, v };
}

FSSGS_KeyValuePair USSGS_FrameObject::MakePropertyInt( const FString& n, int32 v )
{
    return FSSGS_KeyValuePair{ n, v };
}

FSSGS_KeyValuePair USSGS_FrameObject::MakePropertyFloat( const FString& n, float v )
{
    return FSSGS_KeyValuePair{ n, v };
}

FSSGS_KeyValuePair USSGS_FrameObject::MakePropertyString( const FString& n, const FString& v )
{
    return FSSGS_KeyValuePair{ n, v };
}

FSSGS_KeyValuePair USSGS_FrameObject::MakePropertyObject( const FString& n, const TSSGS_ObjectDef& v )
{
    return FSSGS_KeyValuePair{ n, v };
}

FSSGS_KeyValuePair USSGS_FrameObject::MakePropertyBoolArray( const FString& n, const TArray< bool >& v )
{
    return FSSGS_KeyValuePair{ n, v };
}

FSSGS_KeyValuePair USSGS_FrameObject::MakePropertyByteArray( const FString& n, const TArray< uint8 >& v )
{
    return FSSGS_KeyValuePair{ n, v };
}

FSSGS_KeyValuePair USSGS_FrameObject::MakePropertyIntArray( const FString& n, const TArray< int32 >& v )
{
    return FSSGS_KeyValuePair{ n, v };
}

FSSGS_KeyValuePair USSGS_FrameObject::MakePropertyFloatArray( const FString& n, const TArray< float >& v )
{
    return FSSGS_KeyValuePair{ n, v };
}

FSSGS_KeyValuePair USSGS_FrameObject::MakePropertyStringArray( const FString& n, const TArray< FString >& v )
{
    return FSSGS_KeyValuePair{ n, v };
}

FSSGS_KeyValuePair USSGS_FrameObject::MakePropertyObjectArray( const FString& n, const TArray< FSSGS_PropertyContainer >& v )
{
    return FSSGS_KeyValuePair{ n, v };
}

TSharedPtr< FJsonValue > USSGS_FrameObject::Convert() const
{
    auto obj = MakeShared< FJsonObject >();

    for ( const auto& prop : properties )
        prop.Decorate( obj );

    return MakeShared< FJsonValueObject >( obj );
}
