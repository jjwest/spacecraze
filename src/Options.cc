#include "Options.h"

#include "AssetManager.h"
#include "Constants.h"
#include "Globals.h"

Options::Options()
{
    title.setText("SETTINGS");
    title.setPosition(450, 150);
    title.setFont(AssetManager::instance().getFont("title"));

    back_button.setPosition(SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT - 150);
    back_button.setText("BACK");

    music_text.setText("Music");
    music_text.setPosition(450, 300);
    music_text.setFont(AssetManager::instance().getFont("text"));
    music_button.setPosition(650, 300);

    sound_text.setText("Sound effects");
    sound_text.setPosition(300, 350);
    sound_text.setFont(AssetManager::instance().getFont("text"));
    sound_button.setPosition(650, 350);

    if (GLOBAL_SETTINGS.music)
    {
		music_button.setText("ON");
    }
    else
    {
		music_button.setText("OFF");
    }
    if (GLOBAL_SETTINGS.sound_effects)
    {
		sound_button.setText("ON");
    }
    else
    {
		sound_button.setText("OFF");
    }
}

State Options::getNextState() const
{
    return next_state;
}

void Options::handleEvents()
{
    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT)
    	{
            next_state = State::QUIT;
        }
        else if (leftMouseButtonPressed())
    	{
    	    if (back_button.mouseOver())
    	    {
				next_state = State::MENU;
    	    }
    	    else if (music_button.mouseOver())
    	    {
				toggleMusic();
    	    }
    	    else if (sound_button.mouseOver())
    	    {
				toggleSoundEffects();
    	    }
		}
    	else if (event.type == SDL_KEYDOWN)
    	{
    	    if (active_button == NONE)
    	    {
				active_button = MUSIC;
    	    }
    	    else if (event.key.keysym.sym == SDLK_UP && active_button != MUSIC)
    	    {
				--active_button;
    	    }
    	    else if (event.key.keysym.sym == SDLK_DOWN && active_button != BACK)
    	    {
				++active_button;
    	    }
    	    else if (event.key.keysym.sym == SDLK_RETURN)
    	    {
				switch (active_button)
				{
				case SOUND_EFFECTS: toggleSoundEffects();     break;
				case MUSIC:         toggleMusic();            break;
				case BACK:          next_state = State::MENU; break;
				}
    	    }
    	}
    	else if (event.type == SDL_MOUSEMOTION)
    	{
    	    if (back_button.mouseOver())
    	    {
				active_button = BACK;
    	    }
    	    else if (music_button.mouseOver())
    	    {
				active_button = MUSIC;
    	    }
    	    else if (sound_button.mouseOver())
    	    {
				active_button = SOUND_EFFECTS;
    	    }
			else
			{
				active_button = NONE;
			}
    	}
    }

}

void Options::update()
{
    switch (active_button)
    {
    case NONE:
    {
		back_button.removeHighlight();
		music_button.removeHighlight();
		sound_button.removeHighlight();
		break;
    }
    case MUSIC:
    {
		music_button.addHighlight();
		back_button.removeHighlight();
		sound_button.removeHighlight();
		break;
    }
    case SOUND_EFFECTS:
    {
		sound_button.addHighlight();
		back_button.removeHighlight();
		music_button.removeHighlight();
		break;
    }
    case BACK:
    {
		back_button.addHighlight();
		music_button.removeHighlight();
		sound_button.removeHighlight();
		break;
    }
    }
}

void Options::draw(SDL_Renderer *renderer)
{
    SDL_RenderClear(renderer);

    auto background = AssetManager::instance().getTexture("background");
    SDL_RenderCopy(renderer, background->getTexture(), NULL, NULL);
    title.draw(renderer);
    music_button.draw(renderer);
    music_text.draw(renderer);
    sound_button.draw(renderer);
    sound_text.draw(renderer);
    back_button.draw(renderer);

    SDL_RenderPresent(renderer);
}

bool Options::leftMouseButtonPressed() const
{
    return (event.type == SDL_MOUSEBUTTONDOWN &&
			SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT));
}

void Options::toggleMusic()
{
    GLOBAL_SETTINGS.music = !GLOBAL_SETTINGS.music;
    if (GLOBAL_SETTINGS.music)
    {
		music_button.setText("ON");
    }
    else
    {
		music_button.setText("OFF");
    }
}

void Options::toggleSoundEffects()
{
    GLOBAL_SETTINGS.sound_effects = !GLOBAL_SETTINGS.sound_effects;
    if (GLOBAL_SETTINGS.sound_effects)
    {
		sound_button.setText("ON");
    }
    else
    {
		sound_button.setText("OFF");
    }
}
