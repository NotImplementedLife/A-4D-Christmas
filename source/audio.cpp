#include "audio.hpp"

#include <gba.h>
#include "soundbank.h"
#include "soundbank_bin.h"

// https://www.soundfishing.eu/sound/laser-gun
const mm_sound_effect laser_sfx = {
		{ SFX_LASER } ,			// id
		1<<13,	// rate
		0,		// handle
		255,	// volume
		128,		// panning
};

// https://elements.envato.com/explosion-powerful-GHDGDPQ?utm_source=mixkit&utm_medium=referral&utm_campaign=elements_mixkit_cs_sfx_tag&_ga=2.127449229.1699470174.1640886970-1747293953.1640886970
const mm_sound_effect explosion_sfx = {
		{ SFX_EXPLOSION } ,			// id
		1<<10,	// rate
		0,		// handle
		255,	// volume
		128,		// panning
};


void init_sound()
{
	// from: examples
	
	// Maxmod requires the vblank interrupt to reset sound DMA.
	// Link the VBlank interrupt to mmVBlank, and enable it. 
	irqSet( IRQ_VBLANK, mmVBlank );
	irqEnable(IRQ_VBLANK);
	
	// initialise maxmod with soundbank and 8 channels
    mmInitDefault( (mm_addr)soundbank_bin, 8 );
}

void play_sound(const mm_sound_effect* sfx)
{
	mmEffectEx((mm_sound_effect*)sfx);
}
