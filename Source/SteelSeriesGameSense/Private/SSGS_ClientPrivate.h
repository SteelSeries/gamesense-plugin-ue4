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


#include "Async/Future.h"
#include "Types/SSGS_Payload.h"


DECLARE_LOG_CATEGORY_EXTERN( SSGS_Client, Log, All );


namespace ssgs {


/**
* SteelSeries GameSense Client Implementation
*/
class STEELSERIESGAMESENSE_API Client {

    typedef uint32 _gsWorkerReturnType_;

    enum _state_ {
        Probing = 0,
        Active,
        Disabled
    };

public:

    ~Client();

    /**
    * API methods
    */
    void RegisterGame( const FSSGS_GameInfo& v );
    void RegisterEvent( const FSSGS_EventInfo& v );
    void BindEvent( const FSSGS_EventBinding& v );
    void SendEvent( const FSSGS_EventUpdate& v );
    void RemoveEvent( const FSSGS_Event& v );
    void RemoveGame( const FSSGS_Game& v );

    /**
    * Singleton access
    */
    static Client* Instance();
    static bool Initialize();
    static void Release();

private:

    Client();
    Client( const Client& other ) = delete;
    Client( const Client&& other ) = delete;
    Client& operator=( const Client& rhs ) = delete;
    Client& operator=( const Client&& rhs ) = delete;

    bool _isActive() { return _mClientState == Active; }
    bool _isDisabled() { return _mClientState == Disabled; }

    _gsWorkerReturnType_ _gsWorkerFn();

private:

    static Client* _mpInstance;

private:

    bool _mShouldRun;
    _state_ _mClientState;
    FString _mGameName;
    TSharedFuture< _gsWorkerReturnType_ > _gsWorkerReturnStatus;

};


}