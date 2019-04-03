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
#include "SSGS_ClientBPLibrary.h"
#include "SSGS_ClientPrivate.h"


using namespace ssgs;


bool USSGS_ClientBPLibrary::Start()
{
#if STEELSERIESGAMESENSE_SUPPORTED_PLATFORMS
    return Client::Initialize();
#else
    return false;
#endif
}

void USSGS_ClientBPLibrary::Stop()
{
#if STEELSERIESGAMESENSE_SUPPORTED_PLATFORMS
    Client::Release();
#endif
}

void USSGS_ClientBPLibrary::RegisterGame( const FString& gameName, const FString& gameDisplayName, const FString& developer )
{
#if STEELSERIESGAMESENSE_SUPPORTED_PLATFORMS
    Client::Instance()->RegisterGame( FSSGS_GameInfo( gameName,
                                                      gameDisplayName,
                                                      developer ) );
#endif
}

void USSGS_ClientBPLibrary::RegisterEvent( const FString& gameName, const FString& eventName, int32 minValue, int32 maxValue, ESSGS_EventIconId iconId, bool valueOptional )
{
#if STEELSERIESGAMESENSE_SUPPORTED_PLATFORMS
    Client::Instance()->RegisterEvent( FSSGS_EventInfo( gameName,
                                                        eventName,
                                                        minValue,
                                                        maxValue,
                                                        iconId,
                                                        valueOptional ) );
#endif
}

void USSGS_ClientBPLibrary::BindEvent( const FString& gameName, const FString& eventName, int32 minValue, int32 maxValue, ESSGS_EventIconId iconId, USSGS_HandlerCollection*& handlers, bool valueOptional )
{
#if STEELSERIESGAMESENSE_SUPPORTED_PLATFORMS
    Client::Instance()->BindEvent(
        FSSGS_EventBinding( gameName,
                            eventName,
                            minValue,
                            maxValue,
                            iconId,
                            handlers,
                            valueOptional ) );
#endif
}

void USSGS_ClientBPLibrary::SendEvent( const FString& gameName, const FString& eventName, const FSSGS_EventData& data )
{
#if STEELSERIESGAMESENSE_SUPPORTED_PLATFORMS
    Client::Instance()->SendEvent( FSSGS_EventUpdate( gameName,
                                                      eventName,
                                                      data ) );
#endif
}

void USSGS_ClientBPLibrary::RemoveEvent( const FString& gameName, const FString& eventName )
{
#if STEELSERIESGAMESENSE_SUPPORTED_PLATFORMS
    Client::Instance()->RemoveEvent( FSSGS_Event{ gameName, eventName } );
#endif
}

void USSGS_ClientBPLibrary::RemoveGame( const FString& gameName )
{
#if STEELSERIESGAMESENSE_SUPPORTED_PLATFORMS
    Client::Instance()->RemoveGame( FSSGS_Game{ gameName } );
#endif
}
