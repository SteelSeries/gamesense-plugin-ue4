/**
* Authors: sharkgoesmad
*
* Copyright (c) 2019 SteelSeries ApS. All Rights Reserved.
*/
#pragma once


#include "Types/SSGS_Payload.h"
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
    * Initializes client's resources. Must call it before invoking any other function.
    *
    * @return true if successful, false otherwise.
    */
    UFUNCTION( BlueprintCallable, Category = "Gamesense|Client" )
    static bool Start();

    /**
    * Stops the client and releases its resources. Call on exit.
    */
    UFUNCTION( BlueprintCallable, Category = "Gamesense|Client" )
    static void Stop();

    /**
    * Registers a game with the GameSense server.
    *
    * @param	gameName The string that the server uses to identify the game.
    * @param	gameDisplayName The string used by SteelSeries Engine to display game title.
    * @param    developer The optional string used by SteelSeriers Engine to display game developer name.
    */
    UFUNCTION( BlueprintCallable, Category = "Gamesense|Client", meta = ( AutoCreateRefTerm = "developer" ) )
    static void RegisterGame( const FString& gameName, const FString& gameDisplayName, const FString& developer );
    
    /**
    * Registers a game event with the GameSense server.
    *
    * @param	gameName The string that the server uses to identify the game.
    * @param	eventName The string the server uses to identify an event for the game.
    * @param	minValue Minimum integer value for the event.
    * @param	maxValue Maximum integer value for the event.
    * @param	iconId The ID value of an icon associated with the game. Used by SteelSeries Engine.
    * @param	valueOptional If true, handlers will be processed on every event update with no regard to update value.
    */
    UFUNCTION( BlueprintCallable, Category = "Gamesense|Client" )
    static void RegisterEvent( const FString& gameName, const FString& eventName, int32 minValue, int32 maxValue, ESSGS_EventIconId iconId, bool valueOptional = false );
    
    /**
    * Registers a game event with the GameSense server and binds specified handlers to the event.
    *
    * @param	gameName The string that the server uses to identify the game.
    * @param	eventName The string the server uses to identify an event for the game.
    * @param	minValue Minimum integer value for the event.
    * @param	maxValue Maximum integer value for the event.
    * @param	iconId The ID value of an icon associated with the game. Used by SteelSeries Engine.
    * @param	handlers The collection of handlers to bind to the event.
    * @param	valueOptional If true, handlers will be processed on every event update with no regard to update value.
    */
    UFUNCTION( BlueprintCallable, Category = "Gamesense|Client" )
    static void BindEvent( const FString& gameName, const FString& eventName, int32 minValue, int32 maxValue, ESSGS_EventIconId iconId, UPARAM( ref, DisplayName = "Handler Collection" ) USSGS_HandlerCollection*& handlers, bool valueOptional = false );
    
    /**
    * Sends event update to the GameSense server.
    *
    * @param	gameName The string that the server uses to identify the game.
    * @param	eventName The string the server uses to identify an event for the game.
    * @param	data Event data object with current value for the event.
    */
    UFUNCTION( BlueprintCallable, Category = "Gamesense|Client" )
    static void SendEvent( const FString& gameName, const FString& eventName, const FSSGS_EventData& data );
   
    /**
    * Unregisters an event with the server for the specified game.
    *
    * @param	gameName The string that the server uses to identify the game.
    * @param	eventName The string the server uses to identify an event for the game.
    */
    UFUNCTION( BlueprintCallable, Category = "Gamesense|Client" )
    static void RemoveEvent( const FString& gameName, const FString& eventName );
    
    /**
    * Unregisters the specified game with the server.
    *
    * @param	gameName The string that the server uses to identify the game.
    * @param	eventName The string the server uses to identify an event for the game.
    */
    UFUNCTION( BlueprintCallable, Category = "Gamesense|Client" )
    static void RemoveGame( const FString& gameName );

};
