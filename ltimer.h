#pragma once

#include <cstdint>

class LTimer{
public:
    LTimer();
    void start();
    void stop();
    void pause();
    void unpause();
    uint64_t getTicks();
    bool isStarted() { return mStarted; }
    bool isPaused() { return mPaused; }
private:
    uint64_t mStartTicks = 0;
    uint64_t mPausedTicks = 0;
    bool mStarted = false;
    bool mPaused = false;
    
    uint64_t getCurrentTicks() const;
};