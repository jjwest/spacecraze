#include "../inc/menustate.h"

#include "../inc/resourcemanager"

MenuState::MenuState(Texture* t, SDL_Renderer* r, SDL_Event* e)
    :  {
    font = ResourceManager::getInstance().getFont("button")

    button["PLAY"] = new Button(renderer, "PLAY", 400, 300, font, white, green);
    button["RESUME"] = new Button(renderer, "RESUME", 400, 300, font, white, green);
    button["HIGHSCORE"] = new Button(renderer, "HIGHSCORE", 400, 350, font, white, green);
    button["QUIT"] = new Button(renderer, "QUIT", 400, 400, font, white, green);
}

MenuState::~MenuState() {
    TTF_CloseFont(font);
    
    for ( auto pair : button ) {
        delete pair.second;
    }
}

GAMESTATES MenuState::update(bool paused) {
    if ( paused ) {
        gamestate = PAUSEMENU;
    }
    else {
        gamestate = MENU;
    }

    is_paused = paused;
    handle_events();
    draw();
    
    return gamestate;
}

bool MenuState::cursor_over_button(const SDL_Rect& rect) const {
    int x, y;
    SDL_GetMouseState(&x, &y);

    return ( x >= rect.x && 
             y >= rect.y &&
             x <= rect.x + rect.w && 
             y <= rect.y + rect.h );
}


void MenuState::draw() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background, NULL, NULL);

    if ( is_paused ) {
        button.at("RESUME")->draw(renderer);
    }
    else {
        button.at("PLAY")->draw(renderer);
    }
    
    button.at("HIGHSCORE")->draw(renderer);
    button.at("QUIT")->draw(renderer);
    
    SDL_RenderPresent(renderer);
}

void MenuState::handle_events() {
    while ( SDL_PollEvent(event) != 0 ) {
        if ( event->type == SDL_QUIT ) {
            gamestate = QUIT;
        }
        else if ( event->type == SDL_MOUSEBUTTONDOWN && 
                 event->button.button == SDL_BUTTON_LEFT ) {
            check_button_pushed();
        }
    }
}

void MenuState::check_button_pushed() {   
    if ( cursor_over_button( button.at("PLAY")->get_rect() )) {
        gamestate = PLAY;
        return;
    }
    if ( cursor_over_button( button.at("HIGHSCORE")->get_rect() )) {
        gamestate = HIGHSCORE;
        return;
    }
    if ( cursor_over_button( button.at("QUIT")->get_rect() )) {
        gamestate = QUIT;
        return;
    }
}

TTF_Font* MenuState::load_font(std::string path, int size) {
    TTF_Font* loaded_font = TTF_OpenFont(path.c_str(), size);
    if ( font == NULL ) {
        std::cerr << "Failed to load font. Reason: " 
                  << TTF_GetError() << std::endl;
        exit(1);
    }

    return loaded_font;
}


