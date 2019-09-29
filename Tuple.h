#ifndef Tuple_Header
#define Tuple_Header

#include <stddef.h>
#include <stdio.h>

double * Tuple_Create(size_t);
void Tuple_Destroy(double *);
void Tuple_Report(FILE *, size_t, double *, char *, char *);
	
unsigned int * TupleOfUnsignedInt_Create(size_t);
void TupleOfUnsignedInt_Destroy(unsigned int *);
void TupleOfUnsignedInt_Report(FILE *, size_t, unsigned int *, char *, char *);

#endif