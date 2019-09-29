#include <stddef.h>
#include "Vector.h"
#include "Random.h"
#include "Tuple.h"
#include "RNG.h"
#include "Rotate.h"

Vector Vector_Create(size_t length)
{
	Vector tmp;
	tmp.n = length;
	tmp.v = Tuple_Create(length);
	return tmp;
}

Vector Vector_Create_Random(size_t length, RNG *rng, double a, double b)
{
	Vector tmp;
	tmp.n = length;
	tmp.v = Tuple_Create_Random(length, rng, a, b);
	return tmp;
}

void Vector_Rotate(Vector v)
{
	Tuple_Rotate(v.n, v.v);
}

void Vector_Rotate_Back(Vector v)
{
	Tuple_Rotate_Back(v.n, v.v);
}

void Vector_Report(FILE *F, Vector v, char *fmt, char *info)
{
	fprintf(F, "# Reporting Vector as Tuple.\n");
	fprintf(F, "# Vector info: %s\n", info);
	Tuple_Report(F, v.n, v.v, fmt, "This is a v of a Vector.");
}

void Vector_Destroy(Vector v)
{
	Tuple_Destroy(v.v);
	v.n = 0;
	v.v = NULL;
}