#include "inputhandler.h"

void InputHandler::handleSDLEvent( SDL_Event& e, int cellSize, SDL_Rect camera )
{
    switch ( e.type ){
    case SDL_EVENT_KEY_DOWN:
        handleKeyboardEvent( e.key );
        break;
    case SDL_EVENT_MOUSE_BUTTON_DOWN:
        handleMousePressEvent( e.button, cellSize, camera );
        break;
    case SDL_EVENT_MOUSE_WHEEL:
        handleMouseWheelEvent( e.wheel );
        break;
    default:
        if (e.type >= SDL_EVENT_WINDOW_FIRST && e.type <= SDL_EVENT_WINDOW_LAST) {
            handleWindowEvent(e.window);
        }
        break;
    }
}

void InputHandler::handleKeyboardEvent( SDL_KeyboardEvent& e )
{
    GameEvent event;
    ViewEvent viewEvent;
    
    switch ( e.key ){
    case SDLK_P:
        event.action = GameAction::PAUSE;
        m_gameEvent = event; 
        break; 

    case SDLK_C:
        event.action = GameAction::CLEAR;
        m_gameEvent = event; 
        break; 

    case SDLK_A:
        viewEvent.action = ViewAction::CAMERA_MOVE;
        viewEvent.velX = -1;
        m_viewEvent = viewEvent;
        break;

    case SDLK_D:
        viewEvent.action = ViewAction::CAMERA_MOVE;
        viewEvent.velX = 1;
        m_viewEvent = viewEvent;
        break;

    case SDLK_W:
        viewEvent.action = ViewAction::CAMERA_MOVE;
        viewEvent.velY = -1;
        m_viewEvent = viewEvent;
        break;

    case SDLK_S:
        viewEvent.action = ViewAction::CAMERA_MOVE;
        viewEvent.velY = 1;
        m_viewEvent = viewEvent;
        break;

    case SDLK_MINUS:
    case SDLK_KP_MINUS:
        event.action = GameAction::SPEED_DOWN;
        m_gameEvent = event; 
        break; 

    case SDLK_EQUALS:
    case SDLK_KP_PLUS:
        if ( e.key == SDLK_EQUALS && !(e.mod & SDL_KMOD_SHIFT) )
            break;
        event.action = GameAction::SPEED_UP;
        m_gameEvent = event; 
        break; 
    }
}

void InputHandler::handleMousePressEvent( SDL_MouseButtonEvent& e, int cellSize, SDL_Rect camera )
{
    GameEvent event;
    event.action = GameAction::TOGGLE_CELL;
    event.cell.x = int( (e.x + camera.x) / cellSize);
    event.cell.y = int( (e.y + camera.y) / cellSize);
    m_gameEvent = event; 
}

void InputHandler::handleMouseWheelEvent( SDL_MouseWheelEvent& e )
{
    ViewEvent event;
    if ( e.y > 0 ){
        event.action = ViewAction::CELL_SIZE_INCREASE;
    }
    else{
        event.action = ViewAction::CELL_SIZE_DECREASE;
    }
    event.mouseX = int(e.mouse_x);
    event.mouseX = int(e.mouse_y); 
    m_viewEvent = event;
}

void InputHandler::handleWindowEvent( SDL_WindowEvent& e )
{
    if ( e.type == SDL_EVENT_WINDOW_RESIZED || e.type == SDL_EVENT_WINDOW_ENTER_FULLSCREEN || e.type == SDL_EVENT_WINDOW_LEAVE_FULLSCREEN )
    {
        ViewEvent event;
        event.action = ViewAction::WINDOW_SIZE_CHANGE;
        m_viewEvent = event;
    }
}