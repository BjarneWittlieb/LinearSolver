#include "Tuple.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

double *Tuple_Create(size_t length)
{
	double *tmp = NULL;
	tmp = calloc(length, sizeof(double));
	return tmp;
}

void Tuple_Destroy(double *tuple)
{
	free(tuple);
}

void Tuple_Report(FILE *F, size_t length, double *tuple, char *fmt, char *info)
{
	fprintf(F, "# Reporting Tuple (length %u):\n", (int)length);
	fprintf(F, "#Info: %s\n", info);
	for (size_t i = 0; i < length; i++)
	{
		fprintf(F, fmt, tuple[i]);
		fprintf(F, "\n");
	}
	fprintf(F, "\n");
}

unsigned int *TupleOfUnsignedInt_Create(size_t length)
{
	unsigned int *tmp = NULL;
	tmp = calloc(length, sizeof(unsigned int));
	return tmp;
}

void TupleOfUnsignedInt_Destroy(unsigned int *tuple)
{
	free(tuple);
}

void TupleOfUnsignedInt_Report(FILE *F, size_t length, unsigned int *tuple, char *fmt, char *info)
{
	fprintf(F, "# Rporting Tuple of unsigned int (length %u):\n", (int)length);
	fprintf(F, "#Info: %s\n", info);
	for (size_t i = 0; i < length; i++)
	{
		fprintf(F, fmt, tuple[i]);
		fprintf(F, "\n");
	}
	fprintf(F, "\n");
}

double *TupleOfTuple_Create(size_t m, size_t n)
{
	double *tmp = NULL;
	tmp = calloc(m * n, sizeof(double));
	return tmp;
}

void TupleOfTuple_Destroy(double *t)
{
	free(t);
}

double TupleOfTuple_Get(double *t, unsigned int i, unsigned int j, size_t n)
{
	return t[i * n + j];
}

void TupleOfTuple_Set(double *t, double x, unsigned int i, unsigned int j, size_t n)
{
	t[i * n + j] = x;
}

double *TupleOfTuple_LoadFromFile(char *Filename, size_t *pm, size_t *pn)
{
	double *A = NULL;

	char s[2048];
	FILE *F = NULL;
	size_t m = 0, n = 0;

	char *t;

	F = fopen(Filename, "r");

	do
	{
		t = fgets(s, 2048, F);
	} while ((s[0] == '#') || (s[0] == 10));

	if (t == NULL)
		return NULL;

	sscanf(s, "%zu %zu", &m, &n);

	A = TupleOfTuple_Create(m, n);

	{
		char *p;
		char *q;
		for (size_t i = 0; i < m; i++)
		{
			do
			{
				t = fgets(s, 2048, F);
			} while ((s[0] == '#') || (s[0] == 10));
			p = s;
			q = NULL;
			for (size_t j = 0; j < n; j++)
			{
				TupleOfTuple_Set(A, strtod(p, &q), i, j, n);
				p = q;
			}
		}
	}

	fclose(F);

	*pm = m;
	*pn = n;
	return A;
}
