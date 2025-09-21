#include "gamerenderer.h"

const int GameRenderer::MIN_CELL_SIZE{ 5 };
const int GameRenderer::MIN_WINDOW_SIZE{ 100 };

GameRenderer::GameRenderer( int windowWidth, int windowHeight, int m_cellSize ) : m_windowWidth( windowWidth ), m_windowHeight( windowHeight ), m_cellSize( m_cellSize )
{
    if ( m_windowWidth < MIN_WINDOW_SIZE ){
        m_windowWidth = MIN_WINDOW_SIZE;
    }
    if ( m_windowHeight < MIN_WINDOW_SIZE ){
        m_windowHeight = MIN_WINDOW_SIZE;
    }
    MAX_CELL_SIZE = std::min( m_windowWidth, m_windowHeight ) / 2;
    if ( m_cellSize < MIN_CELL_SIZE )
    {
        m_cellSize = MIN_CELL_SIZE;
    }
    if ( m_cellSize > MAX_CELL_SIZE ){
        m_cellSize = MAX_CELL_SIZE;
    }
}

bool GameRenderer::init(){
    bool success = true;
    if ( !SDL_Init(SDL_INIT_VIDEO) ) {
        SDL_Log( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    }
    else{
        if ( !SDL_CreateWindowAndRenderer( "Game of Life", m_windowWidth, m_windowHeight, 0, &m_window, &m_renderer ) ) {
            SDL_Log( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else {
            SDL_SetWindowResizable( m_window, true );
            SDL_SetRenderVSync( m_renderer, 1 );
            SDL_SetRenderDrawColor( m_renderer, 0xFF, 0xFF, 0xFF, 0xFF );
        }
    }
    return success;
}

void GameRenderer::close(){
    SDL_DestroyRenderer( m_renderer );
    SDL_DestroyWindow( m_window );
    m_renderer = nullptr;
    m_window = nullptr;
    SDL_Quit();
}

void GameRenderer::centreCamera( const Game& game ){
    m_cameraX = ( game.getField().getWidth() * m_cellSize - m_windowWidth ) / 2;
    m_cameraY = ( game.getField().getHeight() * m_cellSize - m_windowHeight ) / 2;
}

void GameRenderer::renderGame( const Game& game ) const
{
    const Field& field = game.getField();
    SDL_SetRenderDrawColor( m_renderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear( m_renderer );
    SDL_FRect background { 0, 0, (float)field.getWidth() * m_cellSize, (float)field.getHeight() * m_cellSize };
    SDL_SetRenderDrawColor( m_renderer, 0, 0, 0, 0xFF );
    SDL_RenderFillRect( m_renderer, &background );

    SDL_SetRenderDrawColor( m_renderer, 0, 100, 150, 255 );
    for ( int i = m_cellSize; i <= m_cellSize * ( field.getWidth() - 1 ); i += m_cellSize ){
        SDL_RenderLine( m_renderer, (float)i - m_cameraX, 0, (float)i - m_cameraX, (float)field.getHeight() * m_cellSize );
    }
    for ( int i = m_cellSize; i <= m_cellSize * ( field.getHeight() - 1 ); i += m_cellSize ){
        SDL_RenderLine( m_renderer, 0, (float)i - m_cameraY, (float)field.getWidth() * m_cellSize, (float)i - m_cameraY );
    }

    for ( Cell cell : field.getAlive() )
    {
        SDL_FRect cellRect { (float)cell.x * m_cellSize - m_cameraX, (float)cell.y * m_cellSize - m_cameraY, (float)m_cellSize, (float)m_cellSize };
        SDL_RenderFillRect( m_renderer, &cellRect );
    }
    SDL_RenderPresent( m_renderer );
}

void GameRenderer::handleEvent( ViewEvent event )
{
    float mHelpCameraX, mHelpCameraY;
    int oldWindowWindth = m_windowWidth, oldWindowHeight = m_windowHeight;
    
    switch ( event.action )
    {
    case ViewAction::CELL_SIZE_DECREASE:
        mHelpCameraX = float(m_cameraX) / m_cellSize;
        mHelpCameraY = float(m_cameraY) / m_cellSize;
        --m_cellSize;
        if ( m_cellSize < MIN_CELL_SIZE )
            m_cellSize = MIN_CELL_SIZE;
        m_cameraX = int(mHelpCameraX * m_cellSize);
        m_cameraY = int(mHelpCameraY * m_cellSize);
        break;
    
    case ViewAction::CELL_SIZE_INCREASE:
        mHelpCameraX = float(m_cameraX) / m_cellSize;
        mHelpCameraY = float(m_cameraY) / m_cellSize;
        ++m_cellSize;
        if ( m_cellSize > MAX_CELL_SIZE )
            m_cellSize = MAX_CELL_SIZE;
        m_cameraX = int(mHelpCameraX * m_cellSize);
        m_cameraY = int(mHelpCameraY * m_cellSize);
        break;
    
    case ViewAction::WINDOW_SIZE_CHANGE:
        SDL_GetWindowSize( m_window, &m_windowWidth, &m_windowHeight );
        m_cameraX -= (m_windowWidth - oldWindowWindth) / 2;
        m_cameraY -= (m_windowHeight - oldWindowHeight) / 2;
        break;

    case ViewAction::CAMERA_MOVE:
        m_cameraX += event.velX * m_windowWidth / 50;
        m_cameraY += event.velY * m_windowHeight / 50;
    }

    MAX_CELL_SIZE = std::min( m_windowWidth, m_windowHeight ) / 2;
}