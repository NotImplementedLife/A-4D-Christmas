#pragma once

#include <gba.h>

namespace nTopbar
{
	void init();
	u8 take_a_heart();
	void add_to_score(u16 ds);	
	u16 get_score();
	
	u16 get_high_score();
	void set_high_score(u16 hs);
	void save_score_if_high();
	
	void set_shot_enemies(u32 _shot);		
	u32 get_shot_enemies();	
	void inc_shot_enemies();
	
	void update_progress_bar(bool inc=false);
	
	bool is_combo();
	
	void reset_progress_bar();
}