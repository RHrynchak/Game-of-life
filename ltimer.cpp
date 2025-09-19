#include "ltimer.h"
#include <chrono>

LTimer::LTimer(){}

void LTimer::start(){
    mStarted = true;
    mPaused = false;
    mStartTicks = getCurrentTicks();
    mPausedTicks = 0;
}

void LTimer::stop(){
    mStarted = false;
    mPaused = false;
    mStartTicks = 0;
    mPausedTicks = 0;
}

void LTimer::pause(){
    if ( mStarted && !mPaused ){
        mPaused = true;
        mPausedTicks = getCurrentTicks() - mStartTicks;
        mStartTicks = 0;
    }
}

void LTimer::unpause(){
    if ( mStarted && mPaused ){
        mPaused = false;
        mStartTicks = getCurrentTicks() - mPausedTicks;
        mPausedTicks = 0;
    }
}

uint64_t LTimer::getTicks(){
    uint64_t time = 0;
    if ( mStarted ){
        if ( mPaused ){
            time = mPausedTicks;
        }
        else{
            time = getCurrentTicks() - mStartTicks;
        }
    }
    return time;
}

uint64_t LTimer::getCurrentTicks() const
{
    static auto programStart = std::chrono::steady_clock::now();
    auto now = std::chrono::steady_clock::now();
    auto passed = std::chrono::duration_cast<std::chrono::milliseconds>( now - programStart );
    return static_cast< uint64_t >( passed.count() );
}