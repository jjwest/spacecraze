#ifndef _HIGHSCORE_H_
#define _HIGHSCORE_H_

#include <SDL2/SDL.h>
#include <memory>
#include <vector>
#include <string>

#include "gamestate.h"
#include "rendered_text.h"
#include "button.h"
#include "enums.h"

class Highscore: public GameState
{
public:
    Highscore(SDL_Renderer* renderer);
    GameStates getNextState() const;
    void handleEvents();
    void update();
    void render(SDL_Renderer* renderer);

private:
    SDL_Event events;
    GameStates next_state = HIGHSCORE;
    Button button_back;
    RenderedText title;
    std::vector<std::unique_ptr<RenderedText>> highscore_entries;

    std::vector<std::string> parseHighscoreFromFile(const std::string& filename);
    void checkButtonPressed();
    void createRenderedTextFromEntries(SDL_Renderer* renderer,
                                       const std::vector<std::string>& entries);
};

#endif // _HIGHSCORE_H_
