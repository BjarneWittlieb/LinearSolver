#include <stddef.h>
#include "RNG.h"
#include "Tuple.h"

unsigned int * TupleOfUnsignedInt_Create_Random (size_t length, RNG * rng) {
	unsigned int * tmp = TupleOfUnsignedInt_Create (length);
	for (size_t i = 0; i < length; i++) {
		tmp[i] = RNG_Evaluate(rng);
	}
	return tmp;
}

void TupleOfUnsignedInt_Set_Random (size_t length, unsigned int * tuple, RNG * rng) {
	for (size_t i = 0; i < length; i++) {
		tuple[i] = RNG_Evaluate(rng);
	}
}

double * Tuple_Create_Random (size_t length, RNG * rng, double a, double b) {
	double value;
	double * tmp = Tuple_Create(length);
	for (size_t i = 0; i < length; i++) {
		value = (b-a) * RNG_Evaluate_Percent(rng) + a;
		tmp[i] = value;
	}
	return tmp;
}

void Tuple_Set_Random (size_t length, double * tuple, RNG * rng, double a, double b) {
	double value;
	for (size_t i = 0; i < length; i++) {
		value = (b-a) * RNG_Evaluate_Percent(rng) + a;
		tuple[i] = value;
	}
}