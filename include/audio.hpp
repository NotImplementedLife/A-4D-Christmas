#pragma once

#include <maxmod.h>

extern const mm_sound_effect laser_sfx;
extern const mm_sound_effect explosion_sfx;

void init_sound();

void play_sound(const mm_sound_effect* sfx);