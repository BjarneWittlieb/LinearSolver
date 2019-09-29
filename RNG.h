#ifndef Rng_Header
#define Rng_Header

#include <stdio.h>

struct RNG {
	unsigned int a;
	unsigned int b;
	unsigned int m;
	unsigned int seed;
};
typedef struct RNG RNG;

RNG RNG_Set (unsigned int, unsigned int, unsigned int);
RNG RNG_Set_Knuth (void);

unsigned int RNG_Evaluate (RNG *);
double RNG_Evaluate_Percent(RNG *);

void RNG_Report(FILE *, RNG *);

#endif