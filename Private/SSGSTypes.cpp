#include "SSGSPrivatePCH.h"


#define DELETE(X) if ( X ) { delete X; X = nullptr; }


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
void USSGS_RateSpecification::SetStaticRate( const FSSGS_RateStatic& v )
{
    _mode = RateMode_Static;
    _rate.SetSubtype< FSSGS_RateStatic >( v );
}

void USSGS_RateSpecification::SetRangedRate( const FSSGS_RateRange& v )
{
    _mode = RateMode_Range;
    _rate.SetSubtype< FSSGS_RateRange >( v );
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
USSGS_ColorEffectSpecificationGradient::~USSGS_ColorEffectSpecificationGradient()
{
    UE_LOG( LogTemp, Warning, TEXT( "***** ~USSGS_ColorEffectSpecificationGradient() *****" ) );
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
void USSGS_ColorEffectSpecificationRanges::AddStatic( const FSSGS_ColorRangeStatic& v )
{
    staticRanges.Add( v );
}

void USSGS_ColorEffectSpecificationRanges::AddGradient( const FSSGS_ColorRangeGradient& v )
{
    gradientRanges.Add( v );
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

FSSGS_HandlerColor::FSSGS_HandlerColor( const FSSGS_IlluminationDeviceZone& dz, const SSGS_IlluminationMode& im, USSGS_ColorEffectSpecification* colorSpec, USSGS_RateSpecification* rateSpec ) :
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
    check( color != nullptr );

    TSharedPtr< FJsonObject > obj( new ( std::nothrow ) FJsonObject );

    obj->SetStringField( "device-type", deviceZone.device );

    if ( deviceZone.zoneType == FSSGS_IlluminationDeviceZone::named )
        obj->SetStringField( "zone", deviceZone.namedZone() );
    else if ( deviceZone.zoneType == FSSGS_IlluminationDeviceZone::custom )
        obj->SetArrayField( "custom-zone-keys", _getArrayOfJsonValues( deviceZone.customZone() ) );

    obj->SetStringField( "mode", GetEnumString( SSGS_IlluminationMode, mode ) );
    
    if ( color )
        obj->SetField( "color", color->Convert() );

    if ( rate )
        obj->SetField( "rate", rate->Convert() );

    return std::move( TSharedPtr< FJsonValue >( new ( std::nothrow ) FJsonValueObject( obj ) ) );
}


// ****** FSSGS_TactileEffectSimple ******
TSharedPtr< FJsonValue > FSSGS_TactileEffectSimple::Convert() const
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

    obj->SetStringField( "type", type );
    obj->SetNumberField( "length-ms", length_ms );
    obj->SetNumberField( "delay-ms", delay_ms );

    return std::move( TSharedPtr< FJsonValue >( new ( std::nothrow ) FJsonValueObject( obj ) ) );
}


// ****** UTactilePatternRange ******
USSGS_TactilePatternSpecification::USSGS_TactilePatternSpecification()
{
    SetSimplePattern( TArray< FSSGS_TactileEffectSimple >() );
}

void USSGS_TactilePatternSpecification::SetSimplePattern( const TArray< FSSGS_TactileEffectSimple >& v )
{
    _type = TactilePatternType_Simple;
    _pattern.SetSubtype< TArray< FSSGS_TactileEffectSimple > >( v );
}

void USSGS_TactilePatternSpecification::SetCustomPattern( const TArray< FSSGS_TactileEffectCustom >& v )
{
    _type = TactilePatternType_Custom;
    _pattern.SetSubtype< TArray< FSSGS_TactileEffectCustom > >( v );
}

TSharedPtr< FJsonValue > USSGS_TactilePatternSpecification::Convert() const
{
    switch ( _type ) {
    
    case TactilePatternType_Simple: {
        TJsonValues arr( _getArrayOfJsonValues( _pattern.GetSubtype< TArray< FSSGS_TactileEffectSimple > >() ) );
        return std::move( TSharedPtr< FJsonValue >( new ( std::nothrow ) FJsonValueArray( arr ) ) );
    }

    case TactilePatternType_Custom: {
        TJsonValues arr( _getArrayOfJsonValues( _pattern.GetSubtype< TArray< FSSGS_TactileEffectCustom > >() ) );
        return std::move( TSharedPtr< FJsonValue >( new ( std::nothrow ) FJsonValueArray( arr ) ) );
    }

    }
    

    return std::move( TSharedPtr< FJsonValue >( nullptr ) );
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
    check( pattern != nullptr );

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
    UE_LOG( LogTemp, Warning, TEXT( "***** ~USSGS_HandlerCollection() *****" ) );
    _colorHandlers.Empty();
    _tactileHandlers.Empty();
}

void USSGS_HandlerCollection::AddColorHandler( const FSSGS_HandlerColor& handler )
{
    _colorHandlers.Add( handler );
}

void USSGS_HandlerCollection::AddTactileHandler( const FSSGS_HandlerTactile& handler )
{
    _tactileHandlers.Add( handler );
}

TSharedPtr< FJsonValue > USSGS_HandlerCollection::Convert() const
{
    TJsonValues arr( _getArrayOfJsonValues( _colorHandlers ) );
    arr.Append( _getArrayOfJsonValues( _tactileHandlers ) );

    return std::move( TSharedPtr< FJsonValue >( new ( std::nothrow ) FJsonValueArray( arr ) ) );
}


// ****** FSSGS_GameInfo ******
FSSGS_GameInfo::FSSGS_GameInfo() {};

FSSGS_GameInfo::FSSGS_GameInfo( const FString& game, const FString& displayName, SSGS_IconColor iconColorId ) :
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

FSSGS_EventInfo::FSSGS_EventInfo( const FString& gameName, const FString& eventName, int32 minValue, int32 maxValue, SSGS_EventIconId iconId ) :
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

FSSGS_EventBinding::FSSGS_EventBinding( const FString& gameName, const FString& eventName, int32 minValue, int32 maxValue, SSGS_EventIconId iconId, USSGS_HandlerCollection* handlers ) :
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

    auto handlersJsonArray = handlers->Convert();
    const TArray < TSharedPtr < FJsonValue > >* pHandlers;
    // TODO what if null or empty?
    if ( handlersJsonArray->TryGetArray( pHandlers ) ) {
        obj->SetArrayField( "handlers", *pHandlers );
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
