#pragma once


#include "SteelSeriesGameSensePCH.h"
#include "SSGS_Payload.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SSGS_ClientBPLibrary.generated.h"



/**
* Main GameSense Client interface for UE4 Blueprint.
*/
UCLASS()
class STEELSERIESGAMESENSE_API USSGS_ClientBPLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:

    /**
    * Initializes client's resources. Must call it before invoking eny other function.
    *
    * @return true if successful, false otherwise.
    */
    UFUNCTION( BlueprintCallable, Category = "GameSense|Client" )
    static bool Start();

    /**
    * Stops the client and releases its resources. Call on exit.
    */
    UFUNCTION( BlueprintCallable, Category = "GameSense|Client" )
    static void Stop();

    /**
    * Registers a game with the GameSense server.
    *
    * @param	gameName The string that the server uses to identify the game.
    * @param	gameDisplayName The string used by SSE3 to display game title.
    * @param	iconColor The ID value of a color associated with the game. Used by SSE3.
    */
    UFUNCTION( BlueprintCallable, Category = "GameSense|Client" )
    static void RegisterGame( const FString& gameName, const FString& gameDisplayName, ESSGS_IconColor iconColor );
    
    /**
    * Registers a game event with the GameSense server.
    *
    * @param	gameName The string that the server uses to identify the game.
    * @param	eventName The string the server uses to identify an event for the game.
    * @param	minValue Minimum integer value for the event.
    * @param	maxValue Maximum integer value for the event.
    * @param	iconId The ID value of an icon associated with the game. Used by SSE3.
    */
    UFUNCTION( BlueprintCallable, Category = "GameSense|Client" )
    static void RegisterEvent( const FString& gameName, const FString& eventName, int32 minValue, int32 maxValue, ESSGS_EventIconId iconId );
    
    /**
    * Registers a game event with the GameSense server and binds specified handlers to the event.
    *
    * @param	gameName The string that the server uses to identify the game.
    * @param	eventName The string the server uses to identify an event for the game.
    * @param	minValue Minimum integer value for the event.
    * @param	maxValue Maximum integer value for the event.
    * @param	iconId The ID value of an icon associated with the game. Used by SSE3.
    * @param	handlers The collection of handlers to bind to the event.
    */
    UFUNCTION( BlueprintCallable, Category = "GameSense|Client" )
    static void BindEvent( const FString& gameName, const FString& eventName, int32 minValue, int32 maxValue, ESSGS_EventIconId iconId, UPARAM( ref, DisplayName = "Handler Collection" ) USSGS_HandlerCollection*& handlers );
    
    /**
    * Sends event update to the GameSense server.
    *
    * @param	gameName The string that the server uses to identify the game.
    * @param	eventName The string the server uses to identify an event for the game.
    * @param	value The value for the event update. Must be between the declared min and max values.
    */
    UFUNCTION( BlueprintCallable, Category = "GameSense|Client" )
    static void SendEvent( const FString& gameName, const FString& eventName, int32 value );
   
    /**
    * Unregisters an event with the server for the specified game.
    *
    * @param	gameName The string that the server uses to identify the game.
    * @param	eventName The string the server uses to identify an event for the game.
    */
    UFUNCTION( BlueprintCallable, Category = "GameSense|Client" )
    static void RemoveEvent( const FString& gameName, const FString& eventName );
    
    /**
    * Unregisters the specified game with the server.
    *
    * @param	gameName The string that the server uses to identify the game.
    * @param	eventName The string the server uses to identify an event for the game.
    */
    UFUNCTION( BlueprintCallable, Category = "GameSense|Client" )
    static void RemoveGame( const FString& gameName );

};
