#include "Rng.h"
#include <stdio.h>
#include <time.h>
#include <sys/time.h>

RNG RNG_Set(unsigned int a, unsigned int b, unsigned int m) {
	struct timeval tv;
	RNG tmp;
	
	tmp.a = a;
	tmp.b = b;
	tmp.m = m;
	
	// setting seed to time since 1970!
	gettimeofday(&tv, NULL);
	tmp.seed = tv.tv_usec;
	
	return tmp;
}

RNG RNG_Set_Knuth() {
	return RNG_Set(25173, 13849, 65536);
}

unsigned int RNG_Evaluate(RNG * rng) {
	rng->seed = (rng->a * rng->seed + rng->b) % rng->m;
	return rng->seed;
}

double RNG_Evaluate_Percent(RNG * rng) {
	return (double) RNG_Evaluate(rng) / rng->m;
}

void RNG_Report(FILE * F, RNG * rng) {
	
	fprintf(F, "# REPORT Random Number Generator: a: %u, b: %u, m: %u, seed: %u\n", rng->a, rng->b, rng->m, rng->seed);
}