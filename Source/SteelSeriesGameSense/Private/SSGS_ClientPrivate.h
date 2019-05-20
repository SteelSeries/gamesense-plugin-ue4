/**
* Authors: sharkgoesmad
*
* Copyright (c) 2019 SteelSeries ApS. All Rights Reserved.
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
    static void Release();

    bool Initialize();

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
    bool _mInitialized;
    _state_ _mClientState;
    FString _mGameName;
    TSharedFuture< _gsWorkerReturnType_ > _gsWorkerReturnStatus;

};


}