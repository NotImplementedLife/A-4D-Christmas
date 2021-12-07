#pragma once

#include <gba.h>

namespace nTopbar
{
	void init();
	u8 take_a_heart();
	void add_to_score(u16 ds);
	u16 get_score();
}