#ifndef _OPTIONS_H_
#define _OPTIONS_H_

#include <SDL2/SDL.h>

#include "Button.h"
#include "GameState.h"
#include "Text.h"

class Options: public GameState
{
public:
    Options();
    State getNextState() const override;
    void handleEvents() override;
    void update() override;
    void draw(SDL_Renderer* renderer) override;

private:
    enum Buttons
    {
	NONE,
	MUSIC,
	SOUND_EFFECTS,
	BACK
    };
    Button back_button;
    Button music_button;
    Button sound_button;
    Text music_text;
    Text sound_text;
    Text title;
    State next_state = State::OPTIONS;
    int active_button = NONE;
    SDL_Event event;

    bool leftMouseButtonPressed() const;
    void toggleMusic();
    void toggleSoundEffects();
};


#endif // _OPTIONS_H_
