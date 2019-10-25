#ifndef Matrix_Header
#define Matrix_Header

#include <stddef.h>
#include <stdio.h>
#include "Vector.h"

struct Matrix
{
	size_t m, n;
	double *V;
};
typedef struct Matrix Matrix;

Matrix Matrix_Create(size_t, size_t);
void Matrix_Report(FILE *, Matrix, char *, char *);
void Matrix_Destroy(Matrix);
double Matrix_Get(Matrix, unsigned int, unsigned int);
void Matrix_Set(Matrix, double, unsigned int, unsigned int);
Matrix Matrix_LoadFromFile(char *);

Matrix Matrix_Create_Vandermonde(Vector);

#endif