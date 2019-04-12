/**
* Authors: sharkgoesmad
*
* Copyright (c) 2019 SteelSeries ApS. All Rights Reserved.
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

    for ( const T& obj : arr ) {
        ret.Add( obj.Convert() );
    }

    return ret;
}

TJsonValues _getArrayOfJsonValues( const TArray< uint8 >& arr )
{
    TJsonValues ret;

    for ( const uint8 v : arr ) {
        ret.Add( TSharedPtr< FJsonValue >( new ( std::nothrow ) FJsonValueNumber( v ) ) );
    }

    return ret;
}

template < typename T >
TJsonValues _getArrayOfJsonValues( const TArray< T* >& arr )
{
    TJsonValues ret;

    for ( const T* obj : arr ) {
        ret.Add( obj->Convert() );
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
        obj->SetArrayField( "custom-zone-keys", _getArrayOfJsonValues( deviceZone.customZone() ) );

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

TSharedPtr< FJsonValue > USSGS_HandlerCollection::Convert() const
{
    TJsonValues arr( _getArrayOfJsonValues( _colorHandlers ) );
    arr.Append( _getArrayOfJsonValues( _tactileHandlers ) );

    return TSharedPtr< FJsonValue >( new ( std::nothrow ) FJsonValueArray( arr ) );
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
    obj->SetObjectField( "data", FJsonObjectConverter::UStructToJsonObject< FSSGS_EventData >( data ) );

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
