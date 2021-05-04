#ifndef RANDOM_INPUT_RANDOM
#define RANDOM_INPUT_RANDOM

// handles inputs for the random list

#include "input.h"
#include "screen.h"

// returns +1 if up, 0 if nothing, -1 if down
s32 InputRandom_run(Screen *random, u32 frame);

#endif