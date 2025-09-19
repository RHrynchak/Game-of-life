#include "game.h"
#include "gamerenderer.h"
#include "inputhandler.h"

int main(){
    Game game;
    GameRenderer renderer;
    if ( !renderer.init() ){
        SDL_Log( "Failed to initialize!\n" );
    }
    else{
        bool quit = false;
        SDL_Event e;
        InputHandler inputHandler;
        renderer.centreCamera( game );
        renderer.renderGame( game );
        while ( !quit ){
            bool changed = false;
            if ( SDL_WaitEventTimeout( &e, 10 ) ){
                do{
                    if ( e.type == SDL_EVENT_QUIT ){
                        quit = true;
                    }
                    inputHandler.handleSDLEvent( e, renderer.getCellSize(), renderer.getCamera() );
                    std::optional<GameEvent> gameEvent = inputHandler.getGameEvent();
                    if ( gameEvent ){
                        game.handleEvent( *gameEvent );
                        inputHandler.clearGameEvent();
                    }
                    std::optional<ViewEvent> viewEvent = inputHandler.getViewEvent();
                    if ( viewEvent ){
                        renderer.handleEvent( *viewEvent );
                        inputHandler.clearViewEvent();
                    }
                    if ( gameEvent || viewEvent )
                    {
                        changed = true;
                    }
                } while ( SDL_PollEvent( &e ) );
            }
            changed = changed || game.update();
            if (changed){
                renderer.renderGame( game );
                SDL_Log( "Current generation: %d, cells alive: %d", game.getField().getGeneration(), game.getField().getAlive().size() );
            }
        }
    }
    renderer.close();
    return 0;
}