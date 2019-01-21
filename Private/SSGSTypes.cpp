#include "SSGSPrivatePCH.h"


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

    return std::move( ret );
}

template < typename T >
TJsonValues _getArrayOfJsonValues( const TArray< T >& arr )
{
    TJsonValues ret;

    for ( const T& obj : arr ) {
        ret.Add( obj.Convert() );
    }

    return std::move( ret );
}

TJsonValues _getArrayOfJsonValues( const TArray< uint8 >& arr)
{
    TJsonValues ret;

    for ( const uint8 v : arr ) {
        ret.Add( TSharedPtr< FJsonValue >( new ( std::nothrow ) FJsonValueNumber( v ) ) );
    }

    return std::move( ret );
}

template < typename T >
TJsonValues _getArrayOfJsonValues( const TArray< T* >& arr )
{
    TJsonValues ret;

    for ( const T* obj : arr ) {
        ret.Add( obj->Convert() );
    }

    return std::move( ret );
}

TSharedPtr< FJsonValue > FSSGS_JsonConvertable::Convert() const 
{
    // TODO Log message  "reimplement this"
    return std::move( TSharedPtr< FJsonValue >( nullptr ) );
};

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
    p->SetStaticRate( frequency, repeat_limit );
    return p;
}

USSGS_RateSpecification* USSGS_RateSpecification::MakeRangedRate( const TArray< FSSGS_FrequencyRepeatLimitPair >& v )
{
    USSGS_RateSpecification* p = _createUObj< USSGS_RateSpecification >();
    p->SetRangedRate( v );
    return p;
}

void USSGS_RateSpecification::SetStaticRate( const FSSGS_RateStatic& v )
{
    _mode = RateMode_Static;
    _rate.SetSubtype< FSSGS_RateStatic >( v );
}

void USSGS_RateSpecification::SetStaticRate( int32 frequency, int32 repeat_limit )
{
    _mode = RateMode_Static;
    _rate.SetSubtype< FSSGS_RateStatic >( FSSGS_RateStatic{ frequency, repeat_limit } );
}

void USSGS_RateSpecification::SetRangedRate( const FSSGS_RateRange& v )
{
    _mode = RateMode_Range;
    _rate.SetSubtype< FSSGS_RateRange >( v );
}

void USSGS_RateSpecification::SetRangedRate( const TArray< FSSGS_FrequencyRepeatLimitPair >& v )
{
    _mode = RateMode_Range;
    _rate.SetSubtype< FSSGS_RateRange >( FSSGS_RateRange( v ) );
}

TSharedPtr< FJsonValue > USSGS_RateSpecification::Convert() const
{
    switch ( _mode ) {
    
    case RateMode_Static: {
        TSharedPtr< FJsonObject > obj = FJsonObjectConverter::UStructToJsonObject( _rate.GetSubtype< FSSGS_RateStatic >() );
        return std::move( TSharedPtr< FJsonValue >( new ( std::nothrow ) FJsonValueObject( obj ) ) );
    }

    case RateMode_Range: {
        TSharedPtr< FJsonObject > obj = FJsonObjectConverter::UStructToJsonObject( _rate.GetSubtype< FSSGS_RateRange >() );
        return std::move( TSharedPtr< FJsonValue >( new ( std::nothrow ) FJsonValueObject( obj ) ) );
    }
    
    }

    return TSharedPtr< FJsonValue >( nullptr );
}

// ****** FSSGS_ColorRangeStatic ******
FSSGS_ColorRangeStatic::FSSGS_ColorRangeStatic( uint8 l, uint8 h, const FSSGS_RGB& c ) :
    low( l ),
    high( h ),
    color( c )
{}

// ****** FSSGS_ColorRangeGradient ******
FSSGS_ColorRangeGradient::FSSGS_ColorRangeGradient( uint8 l, uint8 h, const FSSGS_ColorGradient& c ) :
    low( l ),
    high( h ),
    color( c )
{}

// ****** USSGS_ColorEffectSpecificationStatic ******
USSGS_ColorEffectSpecificationStatic* USSGS_ColorEffectSpecificationStatic::MakeStaticColorEffect( const FSSGS_RGB& color )
{
    USSGS_ColorEffectSpecificationStatic* p = _createUObj< USSGS_ColorEffectSpecificationStatic >();
    p->SetColor( color );
    return p;
}

void USSGS_ColorEffectSpecificationStatic::SetColor( const FSSGS_RGB& v )
{
    color = v;
}

TSharedPtr< FJsonValue > USSGS_ColorEffectSpecificationStatic::Convert() const
{
    auto obj = FJsonObjectConverter::UStructToJsonObject( color );
    return std::move( TSharedPtr< FJsonValue >( new ( std::nothrow ) FJsonValueObject( obj ) ) );
}

// ****** USSGS_ColorEffectSpecificationGradient ******
USSGS_ColorEffectSpecificationGradient* USSGS_ColorEffectSpecificationGradient::MakeGradientColorEffect( const FSSGS_RGB& zero, const FSSGS_RGB& hundred )
{
    USSGS_ColorEffectSpecificationGradient* p = _createUObj< USSGS_ColorEffectSpecificationGradient >();
    p->SetGradientWithColors( zero, hundred );
    return p;
}

void USSGS_ColorEffectSpecificationGradient::SetGradientWithColors( const FSSGS_RGB& zero, const FSSGS_RGB& hundred )
{
    gradient = FSSGS_ColorGradient{ FSSGS_Gradient{ zero, hundred } };
}

void USSGS_ColorEffectSpecificationGradient::SetGradient( const FSSGS_Gradient& v )
{
    gradient = FSSGS_ColorGradient{ v };
}

TSharedPtr< FJsonValue > USSGS_ColorEffectSpecificationGradient::Convert() const
{
    auto obj = FJsonObjectConverter::UStructToJsonObject( gradient );
    return std::move( TSharedPtr< FJsonValue >( new ( std::nothrow ) FJsonValueObject( obj ) ) );
}

// ****** USSGS_ColorEffectSpecificationRanges ******
USSGS_ColorEffectSpecificationRanges* USSGS_ColorEffectSpecificationRanges::MakeRangeColorEffect()
{
    USSGS_ColorEffectSpecificationRanges* p = _createUObj< USSGS_ColorEffectSpecificationRanges >();
    return p;
}

void USSGS_ColorEffectSpecificationRanges::AddStatic( const FSSGS_ColorRangeStatic& v )
{
    staticRanges.Add( v );
}

void USSGS_ColorEffectSpecificationRanges::AddStatic( uint8 low, uint8 high, const FSSGS_RGB& color )
{
    staticRanges.Add( FSSGS_ColorRangeStatic( low,
                                              high,
                                              color ) );
}

void USSGS_ColorEffectSpecificationRanges::AddGradient( const FSSGS_ColorRangeGradient& v )
{
    gradientRanges.Add( v );
}

void USSGS_ColorEffectSpecificationRanges::AddGradient( uint8 low, uint8 high, const FSSGS_RGB& zero, const FSSGS_RGB& hundred )
{
    gradientRanges.Add( FSSGS_ColorRangeGradient( low,
                                                  high,
                                                  FSSGS_ColorGradient{ { zero, hundred } } ) );
}

TSharedPtr< FJsonValue > USSGS_ColorEffectSpecificationRanges::Convert() const
{
    TJsonValues arr( _getArrayOfJsonValuesFromUStructs( staticRanges ) );
    arr.Append( _getArrayOfJsonValuesFromUStructs( gradientRanges ) );

    return std::move( TSharedPtr< FJsonValue >( new ( std::nothrow ) FJsonValueArray( arr ) ) );
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

    obj->SetStringField( "mode", GetEnumString( ESSGS_IlluminationMode, mode ) );
    
    if ( color )
        obj->SetField( "color", color->Convert() );

    if ( rate )
        obj->SetField( "rate", rate->Convert() );

    return std::move( TSharedPtr< FJsonValue >( new ( std::nothrow ) FJsonValueObject( obj ) ) );
}


// ****** FSSGS_TactileEffectPredefined ******
TSharedPtr< FJsonValue > FSSGS_TactileEffectPredefined::Convert() const
{
    TSharedPtr< FJsonObject > obj( new ( std::nothrow ) FJsonObject );

    obj->SetStringField( "type", type.name );
    obj->SetNumberField( "delay-ms", delay_ms );

    return std::move( TSharedPtr< FJsonValue >( new ( std::nothrow ) FJsonValueObject( obj ) ) );
}


// ****** FSSGS_TactileEffectCustom ******
TSharedPtr< FJsonValue > FSSGS_TactileEffectCustom::Convert() const
{
    TSharedPtr< FJsonObject > obj( new ( std::nothrow ) FJsonObject );

    obj->SetStringField( "type", _type );
    obj->SetNumberField( "length-ms", length_ms );
    obj->SetNumberField( "delay-ms", delay_ms );

    return std::move( TSharedPtr< FJsonValue >( new ( std::nothrow ) FJsonValueObject( obj ) ) );
}

// ****** FSSGS_TactilePatternStatic ******
FSSGS_TactilePatternStatic::FSSGS_TactilePatternStatic( const FSSGS_TactileEffectPredefined& v ) :
    _type( TactilePatternStatic_Predefined )
{
    new ( &_pattern.predefined ) FSSGS_TactileEffectPredefined( v );
}

FSSGS_TactilePatternStatic::FSSGS_TactilePatternStatic( const FSSGS_TactileEffectCustom& v ) :
    _type( TactilePatternStatic_Custom )
{
    new ( &_pattern.custom ) FSSGS_TactileEffectCustom( v );
}

FSSGS_TactilePatternStatic::FSSGS_TactilePatternStatic( const FSSGS_TactilePatternStatic& other ) :
    _type( other._type )
{
    switch ( other._type ) {

    case TactilePatternStatic_Predefined:
        new ( &_pattern.predefined ) FSSGS_TactileEffectPredefined( other._pattern.predefined );
        break;

    case TactilePatternStatic_Custom:
        new ( &_pattern.custom ) FSSGS_TactileEffectCustom( other._pattern.custom );
        break;

    default:
        break;

    }
}

FSSGS_TactilePatternStatic& FSSGS_TactilePatternStatic::operator=( const FSSGS_TactilePatternStatic& rhs )
{
    if ( this != &rhs ) {

        switch ( _type ) {

        case TactilePatternStatic_Predefined:
            _pattern.predefined.~FSSGS_TactileEffectPredefined();
            break;

        case TactilePatternStatic_Custom:
            _pattern.custom.~FSSGS_TactileEffectCustom();
            break;

        }

        _type = rhs._type;

        switch ( rhs._type ) {

        case TactilePatternStatic_Predefined:
            new ( &_pattern.predefined ) FSSGS_TactileEffectPredefined( rhs._pattern.predefined );
            break;

        case TactilePatternStatic_Custom:
            new ( &_pattern.custom ) FSSGS_TactileEffectCustom( rhs._pattern.custom );
            break;

        default:
            break;

        }
    }

    return *this;
}

TSharedPtr< FJsonValue > FSSGS_TactilePatternStatic::Convert() const
{
    switch ( _type ) {
    // TODO remove
    //case TactilePatternStatic_Predefined:
    //    return _pattern.GetSubtype< FSSGS_TactileEffectPredefined >().Convert();
    //    break;

    //case TactilePatternStatic_Custom:
    //    return _pattern.GetSubtype< FSSGS_TactileEffectCustom >().Convert();
    //    break;

    case TactilePatternStatic_Predefined:
        return _pattern.predefined.Convert();
        break;

    case TactilePatternStatic_Custom:
        return _pattern.custom.Convert();
        break;

    default:
        return TSharedPtr< FJsonValue >( nullptr );
        break;

    }
}

// ****** FSSGS_TactilePatternRange ******
FSSGS_TactilePatternRange::FSSGS_TactilePatternRange( uint8 low, uint8 high, const TArray< FSSGS_TactilePatternStatic >& v ) :
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

    return std::move( TSharedPtr< FJsonValue >( new ( std::nothrow ) FJsonValueObject( obj ) ) );
}


// ****** USSGS_TactilePatternSpecificationStatic ******
USSGS_TactilePatternSpecificationStatic* USSGS_TactilePatternSpecificationStatic::MakeStaticTactilePattern( const TArray< FSSGS_TactilePatternStatic >& pattern )
{
    USSGS_TactilePatternSpecificationStatic* p = _createUObj< USSGS_TactilePatternSpecificationStatic >();
    p->SetPattern( pattern );
    return p;
}

FSSGS_TactilePatternStatic USSGS_TactilePatternSpecificationStatic::MakeStaticWithPredefinedEffect( const FSSGS_PredefinedTactilePattern type, int32 delay_ms )
{
    return FSSGS_TactilePatternStatic( FSSGS_TactileEffectPredefined( type,
                                                                      delay_ms ) );
}

FSSGS_TactilePatternStatic USSGS_TactilePatternSpecificationStatic::MakeStaticWithCustomEffect( int32 length_ms, int32 delay_ms )
{
    return FSSGS_TactilePatternStatic( FSSGS_TactileEffectCustom( length_ms,
                                                                  delay_ms ) );
}

void USSGS_TactilePatternSpecificationStatic::SetPattern( const TArray< FSSGS_TactilePatternStatic >& pattern )
{
    _pattern = pattern;
}

TSharedPtr< FJsonValue > USSGS_TactilePatternSpecificationStatic::Convert() const
{
    return std::move( TSharedPtr< FJsonValue >(
        new ( std::nothrow ) FJsonValueArray( _getArrayOfJsonValues( _pattern ) ) ) );
}

// ****** USSGS_TactilePatternSpecificationRanges ******
USSGS_TactilePatternSpecificationRanges* USSGS_TactilePatternSpecificationRanges::MakeRangedTactilePattern( const TArray< FSSGS_TactilePatternRange >& ranges )
{
    USSGS_TactilePatternSpecificationRanges* p = _createUObj< USSGS_TactilePatternSpecificationRanges >();
    p->SetRanges( ranges );
    return p;
}

void USSGS_TactilePatternSpecificationRanges::SetRanges( const TArray< FSSGS_TactilePatternRange >& ranges )
{
    _pattern = ranges;
}

TSharedPtr< FJsonValue > USSGS_TactilePatternSpecificationRanges::Convert() const
{
    return std::move( TSharedPtr< FJsonValue >( 
        new ( std::nothrow ) FJsonValueArray( _getArrayOfJsonValues( _pattern ) ) ) );
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

    return std::move( TSharedPtr< FJsonValue >( new ( std::nothrow ) FJsonValueObject( obj ) ) );
}


// ****** USSGS_HandlerCollection ******
USSGS_HandlerCollection::USSGS_HandlerCollection()
{}

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

    return std::move( TSharedPtr< FJsonValue >( new ( std::nothrow ) FJsonValueArray( arr ) ) );
}


// ****** FSSGS_GameInfo ******
FSSGS_GameInfo::FSSGS_GameInfo() {};

FSSGS_GameInfo::FSSGS_GameInfo( const FString& game, const FString& displayName, ESSGS_IconColor iconColorId ) :
    game( game ),
    gameDisplayName( displayName ),
    iconColorId( iconColorId )
{}

TSharedPtr< FJsonValue > FSSGS_GameInfo::Convert() const
{
    TSharedPtr< FJsonObject > obj( new ( std::nothrow ) FJsonObject() );

    obj->SetStringField( "game", game );
    obj->SetStringField( "game_display_name", gameDisplayName );
    obj->SetNumberField( "icon_color_id", ( uint32 )iconColorId );

    return std::move( TSharedPtr< FJsonValue >( new ( std::nothrow ) FJsonValueObject( obj ) ) );
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

    return std::move( TSharedPtr< FJsonValue >( new ( std::nothrow ) FJsonValueObject( obj ) ) );
}

// ****** FSSGS_EventBinding ******
FSSGS_EventBinding::FSSGS_EventBinding()
{
    handlers = NewObject< USSGS_HandlerCollection >();
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

    return std::move( TSharedPtr< FJsonValue >( new ( std::nothrow ) FJsonValueObject( obj ) ) );
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

    return std::move( TSharedPtr< FJsonValue >( new ( std::nothrow ) FJsonValueObject( obj ) ) );
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

    return std::move( TSharedPtr< FJsonValue >( new ( std::nothrow ) FJsonValueObject( obj ) ) );
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

    return std::move( TSharedPtr< FJsonValue >( new ( std::nothrow ) FJsonValueObject( obj ) ) );
}
