#include "highscore.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

#include "asset_manager.h"
#include "point.h"

Highscore::Highscore(SDL_Renderer* renderer)
    : button_back{ renderer, {550, 850}, "BACK", MENU },
      title{renderer,
              "HIGHSCORE",
              {450, 150},
              AssetManager::getInstance().getFont("title"),
              {255, 255, 255, 255} }
{
    auto score_entries = parseHighscoreFromFile("highscore.txt");
    createRenderedTextFromEntries(renderer, score_entries);
}

GameStates Highscore::getNextState() const
{
    return next_state;
}

void Highscore::handleEvents()
{
    while (SDL_PollEvent(&events) != 0) {
        if (events.type == SDL_QUIT) {
            next_state = QUIT;
        }
        else if (events.type == SDL_MOUSEBUTTONDOWN) {
            checkButtonPressed();
        }
    }
}

void Highscore::update() {}

void Highscore::render(SDL_Renderer* renderer)
{
    auto background = AssetManager::getInstance().getTexture("background");
    SDL_RenderCopy(renderer, background->getTexture(), NULL, NULL);
    title.draw(renderer);
    button_back.draw(renderer);
    for (const auto& entry : highscore_entries) {
        entry->draw(renderer);
    }

    SDL_RenderPresent(renderer);
}

void Highscore::checkButtonPressed()
{
    next_state = button_back.update(next_state);
}

std::vector<std::string> Highscore::parseHighscoreFromFile(
    const std::string& filename)
{
    std::ifstream file{filename};
    if (!file) {
        std::ofstream new_file{filename};
        new_file << "";
        new_file.close();
        file.clear();
        file.open(filename);
    }

    std::vector<std::string> entries; 
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream iss{line};
        iss << std::setw(15) << line << line;
        std::string entry;
        std::getline(iss, entry);
        entries.push_back(entry);
    }
    return entries;
}

void Highscore::createRenderedTextFromEntries(SDL_Renderer* renderer,
                                              const std::vector<
                                              std::string>& entries)
{
    SDL_Color color{255, 255, 255, 255};
    auto font = AssetManager::getInstance().getFont("score");
    Point pos{450, 500};
    
    for (const auto& entry : entries) {
        auto text = std::make_unique<RenderedText>(renderer, entry, pos, font, color);
        highscore_entries.push_back(std::move(text));
        pos.y += 50;
    }
}
