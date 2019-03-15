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
    */
    UFUNCTION( BlueprintCallable, Category = "Gamesense|Client" )
    static void RegisterGame( const FString& gameName, const FString& gameDisplayName );
    
    /**
    * Registers a game event with the GameSense server.
    *
    * @param	gameName The string that the server uses to identify the game.
    * @param	eventName The string the server uses to identify an event for the game.
    * @param	minValue Minimum integer value for the event.
    * @param	maxValue Maximum integer value for the event.
    * @param	iconId The ID value of an icon associated with the game. Used by SteelSeries Engine.
    */
    UFUNCTION( BlueprintCallable, Category = "Gamesense|Client" )
    static void RegisterEvent( const FString& gameName, const FString& eventName, int32 minValue, int32 maxValue, ESSGS_EventIconId iconId );
    
    /**
    * Registers a game event with the GameSense server and binds specified handlers to the event.
    *
    * @param	gameName The string that the server uses to identify the game.
    * @param	eventName The string the server uses to identify an event for the game.
    * @param	minValue Minimum integer value for the event.
    * @param	maxValue Maximum integer value for the event.
    * @param	iconId The ID value of an icon associated with the game. Used by SteelSeries Engine.
    * @param	handlers The collection of handlers to bind to the event.
    */
    UFUNCTION( BlueprintCallable, Category = "Gamesense|Client" )
    static void BindEvent( const FString& gameName, const FString& eventName, int32 minValue, int32 maxValue, ESSGS_EventIconId iconId, UPARAM( ref, DisplayName = "Handler Collection" ) USSGS_HandlerCollection*& handlers );
    
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
