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


namespace ssgs {


/**
* Initializes client's resources. Must call it before invoking any other function.
*
* @return true if successful, false otherwise.
*/
bool STEELSERIESGAMESENSE_API Start();

/**
* Stops the client and releases its resources. Call on exit.
*/
void STEELSERIESGAMESENSE_API Stop();

/**
* Registers a game with the GameSense server.
*
* @param    v   FSSGS_GameInfo object.
*/
void STEELSERIESGAMESENSE_API RegisterGame( const FSSGS_GameInfo& v );

/**
* Registers a game event with the GameSense server.
*
* @param	v   FSSGS_EventInfo object describing an event.
*/
void STEELSERIESGAMESENSE_API RegisterEvent( const FSSGS_EventInfo& v );

/**
* Registers a game event with the GameSense server and binds specified handlers to the event.
*
* @param	v   FSSGS_EventBinding object with event description and handlers.
*/
void STEELSERIESGAMESENSE_API BindEvent( const FSSGS_EventBinding& v );

/**
* Sends event update to the GameSense server.
*
* @param	v   FSSGS_EventUpdate object with update data.
*/
void STEELSERIESGAMESENSE_API SendEvent( const FSSGS_EventUpdate& v );

/**
* Unregisters an event with the server for the specified game.
*
* @param	v   FSSGS_Event object.
*/
void STEELSERIESGAMESENSE_API RemoveEvent( const FSSGS_Event& v );

/**
* Unregisters the specified game with the server.
*
* @param	v   FSSGS_Game object.
*/
void STEELSERIESGAMESENSE_API RemoveGame( const FSSGS_Game& v );


};
