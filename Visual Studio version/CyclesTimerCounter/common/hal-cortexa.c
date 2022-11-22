#include <stdio.h>
#include "hal.h"

void hal_setup(const enum clock_mode clock)
{
	(void)clock;
	//TODO figure out if we need to do someting here
}

uint64_t hal_get_time() {

#ifdef __aarch64__

	uint64_t t;
	asm volatile("mrs %0, PMCCNTR_EL0":"=r"(t));
	return t;

	#elseif __armv7l__

		// TODO: this is actually a 32-bit counter, so it won't work for very long running schemes
		//       need to figure out a way to get a 64-bit cycle counter
		unsigned int cc;
	asm volatile("mrc p15, 0, %0, c9, c13, 0" : "=r"(cc));
	return cc;
	#elseif __x8664__
		uint64_t t = 0;
	return t;
#else
	uint64_t t = 0;
	return t;
#endif
}

/// THIS VERSION HAS TWO FUNCTIONS
/*#ifdef __aarch64__

uint64_t hal_get_time()
{
	uint64_t t;
	asm volatile("mrs %0, PMCCNTR_EL0":"=r"(t));
	return t;
}

#else

uint64_t hal_get_time()
{
	// TODO: this is actually a 32-bit counter, so it won't work for very long running schemes
	//       need to figure out a way to get a 64-bit cycle counter
	unsigned int cc;
	asm volatile("mrc p15, 0, %0, c9, c13, 0" : "=r"(cc));
	return cc;
}
#endif*/


