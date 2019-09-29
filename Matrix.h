#ifndef Matrix_Header
#define Matrix_Header

#include <stddef.h>
#include <stdio.h>

struct Matrix{
	size_t m, n;
	double * V;
};
typedef struct Matrix Matrix;

double * TupleOfTuple_Create (size_t, size_t);
void TupleOfTuple_Destroy(double *);
double TupleOfTuple_Get(double *, unsigned int, unsigned int, size_t);
void TupleOfTuple_Set(double *, double, unsigned int, unsigned int, size_t);
double * TupleOfTuple_LoadFromFile(char *, size_t *, size_t *);

Matrix Matrix_Create (size_t, size_t);
void Matrix_Report(FILE *, Matrix, char *, char *);
void Matrix_Destroy(Matrix);
double Matrix_Get(Matrix, unsigned int, unsigned int);
void Matrix_Set(Matrix, double, unsigned int, unsigned int);
Matrix Matrix_LoadFromFile (char *);

#endif