#pragma once

#include <SDL3/SDL.h>
#include "viewevent.h"
#include "game.h"

class GameRenderer{
public:
    GameRenderer( int windowWidth = 640, int windowHeight = 480, int cellSize = 30 );
    bool init();
    void close();
    void centreCamera( const Game& game );
    void renderGame( const Game& game ) const;
    void handleEvent( ViewEvent event );
    int getCellSize() const { return m_cellSize; }
    SDL_Rect getCamera() const { return { m_cameraX, m_cameraY, m_windowWidth, m_windowHeight }; }

private:
    static const int MIN_CELL_SIZE;
    static const int MAX_CELL_SIZE;
    static const int MIN_WINDOW_SIZE;
    
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    int m_windowWidth, m_windowHeight;
    int m_cameraX, m_cameraY;
    int m_cellSize = 30;
};