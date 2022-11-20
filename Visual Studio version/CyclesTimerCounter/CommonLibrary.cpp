#ifndef COMMONLIBRARY_CPP
#define COMMONLIBRARY_CPP

#include <stdio.h>
#include <string>
#include <time.h>

#include "common/hal.h"


static inline void hal_init_perfcounters(int do_reset, int enable_divider);

static unsigned long long get_nanos(void);
static unsigned long long get_timestamp(void);


/// =========================== LIBRARY =========================== 

static unsigned long long get_timestamp(void) {

	unsigned long long timestamp = 0;
#ifdef cycles
	timestamp = (unsigned long long) hal_get_time();
#else
	timestamp = get_nanos();
#endif
	return timestamp;
}


static unsigned long long get_nanos(void)
{
	struct timespec ts;
	timespec_get(&ts, TIME_UTC);
	return (unsigned long long)ts.tv_sec * 1000000000ull + ts.tv_nsec;
}



#endif