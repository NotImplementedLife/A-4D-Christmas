#pragma once

namespace nSRAM
{
	bool check_integrity();
	void write(const void* source, int size, int offset);
	void read(void* destination, int size, int offset);	
}