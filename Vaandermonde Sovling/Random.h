#ifndef Random_Header
#define Random_Header

#include <stddef.h>
#include "RNG.h"

unsigned int * TupleOfUnsignedInt_Create_Random (size_t, RNG *);
void TupleOfUnsignedInt_Set_Random (size_t, unsigned int *, RNG *);

double * Tuple_Create_Random (size_t, RNG *, double, double);
void Tuple_Set_Random (size_t, double *, RNG *, double, double);

#endif