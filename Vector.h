#ifndef Vector_Header
#define Vector_Header

#include <stddef.h>
#include "RNG.h"

struct Vector{
	size_t n;
	double * v;
};
typedef struct Vector Vector;

Vector Vector_Create_Random (size_t, RNG *, double, double);
Vector Vector_Create (size_t);
void Vector_Rotate(Vector);
void Vector_Rotate_Back(Vector);
void Vector_Report(FILE *, Vector, char *, char *);
void Vector_Destroy(Vector);

#endif