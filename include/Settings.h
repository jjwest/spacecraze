#ifndef _SETTINGS_H_
#define _SETTINGS_H_

struct SettingsConfig
{
    bool music = true;
    bool sound_effects = true;
};

extern SettingsConfig GLOBAL_SETTINGS;

#endif // _SETTINGS_H_
