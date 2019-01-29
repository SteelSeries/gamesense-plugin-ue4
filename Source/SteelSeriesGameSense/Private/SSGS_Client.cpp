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


#include "ISteelSeriesGameSense.h"
#include "SSGS_Client.h"
#include "SSGS_ClientPrivate.h"
#include "Types/SSGS_Payload.h"


namespace ssgs {


bool Start()
{
#if STEELSERIESGAMESENSE_SUPPORTED_PLATFORMS
    return Client::Initialize();
#else
    return false;
#endif
}

void Stop()
{
#if STEELSERIESGAMESENSE_SUPPORTED_PLATFORMS
    Client::Release();
#endif
}

void RegisterGame( const FSSGS_GameInfo& v )
{
#if STEELSERIESGAMESENSE_SUPPORTED_PLATFORMS
    Client::Instance()->RegisterGame( v );
#endif
}

void RegisterEvent( const FSSGS_EventInfo& v )
{
#if STEELSERIESGAMESENSE_SUPPORTED_PLATFORMS
    Client::Instance()->RegisterEvent( v );
#endif
}

void BindEvent( const FSSGS_EventBinding& v )
{
#if STEELSERIESGAMESENSE_SUPPORTED_PLATFORMS
    Client::Instance()->BindEvent( v );
#endif
}

void SendEvent( const FSSGS_EventUpdate& v )
{
#if STEELSERIESGAMESENSE_SUPPORTED_PLATFORMS
    Client::Instance()->SendEvent( v );
#endif
}

void RemoveEvent( const FSSGS_Event& v )
{
#if STEELSERIESGAMESENSE_SUPPORTED_PLATFORMS
    Client::Instance()->RemoveEvent( v );
#endif
}

void RemoveGame( const FSSGS_Game& v )
{
#if STEELSERIESGAMESENSE_SUPPORTED_PLATFORMS
    Client::Instance()->RemoveGame( v );
#endif
}


}
