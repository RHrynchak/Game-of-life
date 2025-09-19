#include "game.h"

const int Game::MIN_SPEED {1};
const int Game::MAX_SPEED {10};

bool Game::update(){
    bool changed = false;
    if ( m_active && 1000.f / m_speed <= m_timer.getTicks() ){
        m_field.updateField();
        m_timer.start();
        changed = true;
    }
    return changed;
}

void Game::handleEvent( GameEvent event )
{
    switch ( event.action ){
    case GameAction::SPEED_UP:
        ++m_speed;
        if ( m_speed > MAX_SPEED )
            m_speed = MAX_SPEED;
        break;

    case GameAction::SPEED_DOWN:
        --m_speed;
        if ( m_speed < MIN_SPEED )
            m_speed = MIN_SPEED;
        break;    
    
    case GameAction::PAUSE:
        if (m_active){
            m_timer.pause();
        }
        else{
            m_timer.unpause();
        }
        m_active = !m_active;
        break;
    
    case GameAction::CLEAR:
        if ( !m_active ){
            m_field.clear();
            m_timer.start();
            m_timer.pause();
        }
        break;

    case GameAction::TOGGLE_CELL:
        if ( !m_active )
        {
            m_field.updateCell( event.cell );
        }
        break;
    }
}