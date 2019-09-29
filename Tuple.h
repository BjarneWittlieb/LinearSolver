#ifndef Tuple_Header
#define Tuple_Header

#include <stddef.h>
#include <stdio.h>

double *Tuple_Create(size_t);
void Tuple_Destroy(double *);
void Tuple_Report(FILE *, size_t, double *, char *, char *);

unsigned int *TupleOfUnsignedInt_Create(size_t);
void TupleOfUnsignedInt_Destroy(unsigned int *);
void TupleOfUnsignedInt_Report(FILE *, size_t, unsigned int *, char *, char *);

double *TupleOfTuple_Create(size_t, size_t);
void TupleOfTuple_Destroy(double *);
double TupleOfTuple_Get(double *, unsigned int, unsigned int, size_t);
void TupleOfTuple_Set(double *, double, unsigned int, unsigned int, size_t);
double *TupleOfTuple_LoadFromFile(char *, size_t *, size_t *);

#endif