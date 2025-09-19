#pragma once

#include "field.h"
#include "gameevent.h"
#include "ltimer.h"

class Game{
public:
    Game() { m_timer.start(); m_timer.pause(); };
    bool update();
    void handleEvent( GameEvent event );
    const Field& getField() const { return m_field; }
    bool active() const { return m_active; }
    
private:
    static const int MIN_SPEED;
    static const int MAX_SPEED;
    bool m_active = false;
    int m_speed = 2; //frames per second
    Field m_field;
    LTimer m_timer;
};