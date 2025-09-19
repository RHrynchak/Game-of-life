#pragma once

#include <SDL3/SDL.h>
#include "gameevent.h"
#include "viewevent.h"
#include <optional>

class InputHandler{
public:
    void handleSDLEvent( SDL_Event& e, int cellSize, SDL_Rect camera );

    std::optional<GameEvent> getGameEvent() const { return m_gameEvent; } 
    std::optional<ViewEvent> getViewEvent() const { return m_viewEvent; }

    void clearGameEvent() { m_gameEvent.reset(); }
    void clearViewEvent() { m_viewEvent.reset(); }

private:
    std::optional<GameEvent> m_gameEvent {}; 
    std::optional<ViewEvent> m_viewEvent {};

    void handleKeyboardEvent( SDL_KeyboardEvent& e );
    void handleMousePressEvent( SDL_MouseButtonEvent& e, int cellSize, SDL_Rect camera );
    void handleMouseWheelEvent( SDL_MouseWheelEvent& e );
    void handleWindowEvent( SDL_WindowEvent& e );
};