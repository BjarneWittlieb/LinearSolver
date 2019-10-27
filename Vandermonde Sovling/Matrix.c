#include "Matrix.h"
#include "Vector.h"
#include "Tuple.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

Matrix Matrix_Create(size_t m, size_t n)
{
	double *tmp = TupleOfTuple_Create(m, n);
	Matrix A = {m, n, tmp};
	return A;
}

void Matrix_Report(FILE *F, Matrix A, char *fmt, char *info)
{
	fprintf(F, "# Reporting Matrix with %u lines and %u Columns:\n%u %u\n", A.m, A.n, A.m, A.n);
	fprintf(F, "# Info: %s\n", info);
	for (unsigned int i = 0; i < (unsigned int)A.m; i++)
	{
		for (unsigned int j = 0; j < (unsigned int)A.n; j++)
		{
			fprintf(F, fmt, Matrix_Get(A, i, j));
			fprintf(F, " ");
		}
		fprintf(F, "\n");
	}
	fprintf(F, "# End of Matrix.\n\n");
}

void Matrix_Destroy(Matrix A)
{
	TupleOfTuple_Destroy(A.V);
	A.V = NULL;
	A.n = 0;
	A.m = 0;
}

double Matrix_Get(Matrix A, unsigned int i, unsigned int j)
{
	return TupleOfTuple_Get(A.V, i, j, A.n);
}

void Matrix_Set(Matrix A, double x, unsigned int i, unsigned int j)
{
	TupleOfTuple_Set(A.V, x, i, j, A.n);
}

Matrix Matrix_LoadFromFile(char *fn)
{
	Matrix A;
	A.V = TupleOfTuple_LoadFromFile(fn, &A.n, &A.m);
	return A;
}

Matrix Matrix_Create_Vandermonde(Vector x)
{
	double tmp;
	Matrix A;

	A = Matrix_Create(x.n, x.n);
	for (unsigned int i = 0; i < x.n; i++)
	{
		tmp = 1;
		for (unsigned int j = 0; j < x.n; j++)
		{
			Matrix_Set(A, tmp, i, j);
			tmp *= x.v[i];
		}
	}
	return A;
}
