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


#include "Types/SSGS_Payload.h"
#include "Runtime/JsonUtilities/Public/JsonObjectConverter.h"


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
        TSharedPtr< FJsonValue > v( new ( std::nothrow ) FJsonValueObject( jsonObj ) );
        ret.Add( v );
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
        return TSharedPtr< FJsonValue >( new ( std::nothrow ) FJsonValueObject( obj ) );
    }

    case RateMode_Range: {
        TSharedPtr< FJsonObject > obj = FJsonObjectConverter::UStructToJsonObject( _rate.Get< FSSGS_RateRange >() );
        return TSharedPtr< FJsonValue >( new ( std::nothrow ) FJsonValueObject( obj ) );
    }
    
    }

    return TSharedPtr< FJsonValue >( new ( std::nothrow ) FJsonValueNull );
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

    return TSharedPtr< FJsonValue >( new ( std::nothrow ) FJsonValueObject( obj ) );
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
    return TSharedPtr< FJsonValue >( new ( std::nothrow ) FJsonValueObject( obj ) );
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
    return TSharedPtr< FJsonValue >( new ( std::nothrow ) FJsonValueObject( obj ) );
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

    return TSharedPtr< FJsonValue >( new ( std::nothrow ) FJsonValueArray( arr ) );
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
    TSharedPtr< FJsonObject > obj( new ( std::nothrow ) FJsonObject );

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

    return TSharedPtr< FJsonValue >( new ( std::nothrow ) FJsonValueObject( obj ) );
}


// ****** FSSGS_TactileEffectPredefined ******
TSharedPtr< FJsonValue > FSSGS_TactileEffectPredefined::Convert() const
{
    TSharedPtr< FJsonObject > obj( new ( std::nothrow ) FJsonObject );

    obj->SetStringField( "type", type.name );
    obj->SetNumberField( "delay-ms", delay_ms );

    return TSharedPtr< FJsonValue >( new ( std::nothrow ) FJsonValueObject( obj ) );
}


// ****** FSSGS_TactileEffectCustom ******
TSharedPtr< FJsonValue > FSSGS_TactileEffectCustom::Convert() const
{
    TSharedPtr< FJsonObject > obj( new ( std::nothrow ) FJsonObject );

    obj->SetStringField( "type", _type );
    obj->SetNumberField( "length-ms", length_ms );
    obj->SetNumberField( "delay-ms", delay_ms );

    return TSharedPtr< FJsonValue >( new ( std::nothrow ) FJsonValueObject( obj ) );
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
        return TSharedPtr< FJsonValue >( new ( std::nothrow ) FJsonValueNull );
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
    TSharedPtr< FJsonObject > obj( new ( std::nothrow ) FJsonObject );

    obj->SetNumberField( "low", low );
    obj->SetNumberField( "high", high );
    obj->SetArrayField( "pattern", _getArrayOfJsonValues( pattern ) );

    return TSharedPtr< FJsonValue >( new ( std::nothrow ) FJsonValueObject( obj ) );
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
    return TSharedPtr< FJsonValue >(
        new ( std::nothrow ) FJsonValueArray( _getArrayOfJsonValues( _pattern ) ) );
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
    return TSharedPtr< FJsonValue >( 
        new ( std::nothrow ) FJsonValueArray( _getArrayOfJsonValues( _pattern ) ) );
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
    TSharedPtr< FJsonObject > obj( new ( std::nothrow ) FJsonObject );

    obj->SetStringField( "device-type", deviceZone.device );
    obj->SetStringField( "zone", deviceZone.zone );
    obj->SetStringField( "mode", mode );
    
    if ( pattern )
        obj->SetField( "pattern", pattern->Convert() );

    if ( rate )
        obj->SetField( "rate", rate->Convert() );

    return TSharedPtr< FJsonValue >( new ( std::nothrow ) FJsonValueObject( obj ) );
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
    obj->SetNumberField( "icon-id", (uint8)icon_id );

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

    return MakeShared< FJsonValueObject >( obj );
}

// ****** FSSGS_FrameDataMultiLine ******
TSharedPtr< FJsonValue > FSSGS_FrameDataMultiLine::Convert() const
{
    auto obj = MakeShared< FJsonObject >();

    frameModifiers.Decorate( obj );

    if ( lines.Num() > 0 )
        obj->SetArrayField( "lines", _getArrayOfJsonValues( lines ) );

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
FSSGS_FrameData USSGS_ScreenDataSpecification::MakeSingleLineFrameData( const FSSGS_LineData& lineData, FSSGS_FrameModifiers frameModifiers )
{
    return FSSGS_FrameData( FSSGS_FrameDataSingleLine{ lineData,
                                                       frameModifiers } );
}

FSSGS_FrameData USSGS_ScreenDataSpecification::MakeMultiLineFrameData( const TArray< FSSGS_LineData >& lines, FSSGS_FrameModifiers frameModifiers )
{
    return FSSGS_FrameData( FSSGS_FrameDataMultiLine{ lines,
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

FSSGS_FrameModifiers USSGS_ScreenDataSpecification::MakeFrameModifiers( int32 length_millis, ESSGS_EventIconId icon_id, bool repeats )
{
    return FSSGS_FrameModifiers{ length_millis, icon_id, repeats };
}

FSSGS_FrameModifiers USSGS_ScreenDataSpecification::MakeFrameModifiersWithRepeatCount( int32 length_millis, ESSGS_EventIconId icon_id, int32 repeat_count )
{
    return FSSGS_FrameModifiers{ length_millis, icon_id, repeat_count };
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

TSharedPtr< FJsonValue > FSSGS_GameInfo::Convert() const
{
    TSharedPtr< FJsonObject > obj( new ( std::nothrow ) FJsonObject() );

    obj->SetStringField( "game", game );
    obj->SetStringField( "game_display_name", gameDisplayName );

    return TSharedPtr< FJsonValue >( new ( std::nothrow ) FJsonValueObject( obj ) );
}


// ****** FSSGS_EventInfo ******
FSSGS_EventInfo::FSSGS_EventInfo() {}

FSSGS_EventInfo::FSSGS_EventInfo( const FString& gameName, const FString& eventName, int32 minValue, int32 maxValue, ESSGS_EventIconId iconId ) :
    game( gameName ),
    eventName( eventName ),
    minValue( minValue ),
    maxValue( maxValue ),
    iconId( iconId )
{}

TSharedPtr< FJsonValue > FSSGS_EventInfo::Convert() const
{
    TSharedPtr< FJsonObject > obj( new ( std::nothrow ) FJsonObject() );

    obj->SetStringField( "game", game );
    obj->SetStringField( "event", eventName );
    obj->SetNumberField( "min_value", minValue );
    obj->SetNumberField( "max_value", maxValue );
    obj->SetNumberField( "icon_id", ( uint32 )iconId );

    return TSharedPtr< FJsonValue >( new ( std::nothrow ) FJsonValueObject( obj ) );
}

// ****** FSSGS_EventBinding ******
FSSGS_EventBinding::FSSGS_EventBinding()
{
    handlers = _createUObj< USSGS_HandlerCollection >();
}

FSSGS_EventBinding::FSSGS_EventBinding( const FString& gameName, const FString& eventName, int32 minValue, int32 maxValue, ESSGS_EventIconId iconId, USSGS_HandlerCollection* handlers ) :
    game( gameName ),
    eventName( eventName ),
    minValue( minValue ),
    maxValue( maxValue ),
    iconId( iconId ),
    handlers( handlers )
{}

FSSGS_EventBinding::~FSSGS_EventBinding()
{
    // let the GC work
    handlers = nullptr;
}

TSharedPtr< FJsonValue > FSSGS_EventBinding::Convert() const
{
    TSharedPtr< FJsonObject > obj( new ( std::nothrow ) FJsonObject() );

    obj->SetStringField( "game", game );
    obj->SetStringField( "event", eventName );
    obj->SetNumberField( "min_value", minValue );
    obj->SetNumberField( "max_value", maxValue );
    obj->SetNumberField( "icon_id", ( uint32 )iconId );

    if ( handlers ) {
        auto handlersJsonArray = handlers->Convert();
        const TJsonValues* pHandlers;

        if ( handlersJsonArray->TryGetArray( pHandlers ) ) {
            obj->SetArrayField( "handlers", *pHandlers );
        }
    }

    return TSharedPtr< FJsonValue >( new ( std::nothrow ) FJsonValueObject( obj ) );
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
    TSharedPtr< FJsonObject > obj( new ( std::nothrow ) FJsonObject() );

    obj->SetStringField( "game", game );
    obj->SetStringField( "event", eventName );
    obj->SetField( "data", data.Convert() );

    return TSharedPtr< FJsonValue >( new ( std::nothrow ) FJsonValueObject( obj ) );
}

// ****** FSSGS_Event ******
FSSGS_Event::FSSGS_Event() {}

FSSGS_Event::FSSGS_Event( const FString& game, const FString& eventName ) :
    game( game ),
    eventName( eventName )
{}

TSharedPtr< FJsonValue > FSSGS_Event::Convert() const
{
    TSharedPtr< FJsonObject > obj( new ( std::nothrow ) FJsonObject() );

    obj->SetStringField( "game", game );
    obj->SetStringField( "event", eventName );

    return TSharedPtr< FJsonValue >( new ( std::nothrow ) FJsonValueObject( obj ) );
}

// ****** FSSGS_Game ******
FSSGS_Game::FSSGS_Game() {}

FSSGS_Game::FSSGS_Game( const FString& game ) :
    game( game )
{}

TSharedPtr< FJsonValue > FSSGS_Game::Convert() const
{
    TSharedPtr< FJsonObject > obj( new ( std::nothrow ) FJsonObject() );

    obj->SetStringField( "game", game );

    return TSharedPtr< FJsonValue >( new ( std::nothrow ) FJsonValueObject( obj ) );
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

// ****** FSSGS_PropertyValuePair ******
void FSSGS_PropertyValuePair::Decorate( TSharedPtr< FJsonObject > obj ) const
{
    switch ( _type ) {

    case PropertyVariant_Bool:
        obj->SetBoolField( _name, _variant.Get< Type >().Get< bool >() );
        break;

    case PropertyVariant_Uint8:
        obj->SetNumberField( _name, _variant.Get< Type >().Get< uint8 >() );
        break;

    case PropertyVariant_Int32:
        obj->SetNumberField( _name, _variant.Get< Type >().Get< int32 >() );
        break;

    case PropertyVariant_Float:
        obj->SetNumberField( _name, _variant.Get< Type >().Get< float >() );
        break;

    case PropertyVariant_String:
        obj->SetStringField( _name, _variant.Get< Type >().Get< FString >() );
        break;

    case PropertyVariant_BoolArray: {
        auto v = _variant.Get< ArrayType >().Get< TArray< bool > >();
        obj->SetArrayField( _name, _getArrayOfJsonValuesBoolean( v ) );
        break;
    }

    case PropertyVariant_Uint8Array: {
        auto v = _variant.Get< ArrayType >().Get< TArray< uint8 > >();
        obj->SetArrayField( _name, _getArrayOfJsonValuesNumbers( v ) );
        break;
    }

    case PropertyVariant_Int32Array: {
        auto v = _variant.Get< ArrayType >().Get< TArray< int32 > >();
        obj->SetArrayField( _name, _getArrayOfJsonValuesNumbers( v ) );
        break;
    }

    case PropertyVariant_FloatArray: {
        auto v = _variant.Get< ArrayType >().Get< TArray< float > >();
        obj->SetArrayField( _name, _getArrayOfJsonValuesNumbers( v ) );
        break;
    }

    case PropertyVariant_StringArray: {
        auto v = _variant.Get< ArrayType >().Get< TArray< FString > >();
        obj->SetArrayField( _name, _getArrayOfJsonValuesString( v ) );
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

FSSGS_PropertyValuePair USSGS_FrameObject::MakePropertyBool( const FString& n, bool v )
{
    return FSSGS_PropertyValuePair{ n, v };
}

FSSGS_PropertyValuePair USSGS_FrameObject::MakePropertyByte( const FString& n, uint8 v )
{
    return FSSGS_PropertyValuePair{ n, v };
}

FSSGS_PropertyValuePair USSGS_FrameObject::MakePropertyInt( const FString& n, int32 v )
{
    return FSSGS_PropertyValuePair{ n, v };
}

FSSGS_PropertyValuePair USSGS_FrameObject::MakePropertyFloat( const FString& n, float v )
{
    return FSSGS_PropertyValuePair{ n, v };
}

FSSGS_PropertyValuePair USSGS_FrameObject::MakePropertyString( const FString& n, const FString& v )
{
    return FSSGS_PropertyValuePair{ n, v };
}

FSSGS_PropertyValuePair USSGS_FrameObject::MakePropertyBoolArray( const FString& n, const TArray< bool >& v )
{
    return FSSGS_PropertyValuePair{ n, v };
}

FSSGS_PropertyValuePair USSGS_FrameObject::MakePropertyByteArray( const FString& n, const TArray< uint8 >& v )
{
    return FSSGS_PropertyValuePair{ n, v };
}

FSSGS_PropertyValuePair USSGS_FrameObject::MakePropertyIntArray( const FString& n, const TArray< int32 >& v )
{
    return FSSGS_PropertyValuePair{ n, v };
}

FSSGS_PropertyValuePair USSGS_FrameObject::MakePropertyFloatArray( const FString& n, const TArray< float >& v )
{
    return FSSGS_PropertyValuePair{ n, v };
}

FSSGS_PropertyValuePair USSGS_FrameObject::MakePropertyStringArray( const FString& n, const TArray< FString >& v )
{
    return FSSGS_PropertyValuePair{ n, v };
}

TSharedPtr< FJsonValue > USSGS_FrameObject::Convert() const
{
    auto obj = MakeShared< FJsonObject >();

    for ( const auto& prop : properties )
        prop.Decorate( obj );

    return MakeShared< FJsonValueObject >( obj );
}
