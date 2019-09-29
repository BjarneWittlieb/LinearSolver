#include "Matrix.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

double * TupleOfTuple_Create (size_t m, size_t n) {
	double * tmp = NULL;
	tmp = calloc(m * n, sizeof(double));
	return tmp;
}

void TupleOfTuple_Destroy(double * t) {
	free(t);
}

double TupleOfTuple_Get(double * t, unsigned int i, unsigned int j, size_t n) {
	return t[i*n + j];
}

void TupleOfTuple_Set(double * t,double x, unsigned int i, unsigned int j, size_t n) {
	t[i*n+j] = x;
}

double * TupleOfTuple_LoadFromFile(char * Filename, size_t * pm, size_t * pn) {
	double * A = NULL;
	
	char s[2048];
	FILE * F = NULL;
	size_t m = 0, n = 0;
	
	char * t;
	
	F = fopen(Filename, "r");
	
	do {
		t = fgets (s, 2048, F);
	} while ((s[0] == '#') || (s[0] == 10));
	
	if (t == NULL) return NULL;
	
	sscanf(s, "%zu %zu", &m, &n);
	
	A = TupleOfTuple_Create (m, n);
	
	{
		char * p;
		char * q;
		for (size_t i = 0; i < m; i++) {
			do {
				t = fgets (s, 2048, F);
			}
			while ((s[0] == '#') || (s[0] == 10));
			p = s; q = NULL;
			for (size_t j = 0; j < n; j++) {
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

Matrix Matrix_Create (size_t m, size_t n) {
	double * tmp = TupleOfTuple_Create(m, n);
	Matrix A = {m, n, tmp};
	return A;
}

void Matrix_Report(FILE * F, Matrix A, char * fmt, char * info) {
	fprintf(F, "# Reporting Matrix with %u lines and %u Columns:\n%u %u\n", A.m, A.n, A.m, A.n);
	fprintf(F, "# Info: %s\n", info);
	for (unsigned int i = 0; i < (unsigned int) A.m; i++) {
		for (unsigned int j = 0; j < (unsigned int) A.n; j++) {
			fprintf(F, fmt, Matrix_Get(A, i, j));
			fprintf(F, " ");
		}
		fprintf(F, "\n");
	}
	fprintf(F, "# End of Matrix.\n\n");
}

void Matrix_Destroy(Matrix A) {
	TupleOfTuple_Destroy(A.V);
	A.V = NULL;
	A.n = 0;
	A.m = 0;
}

double Matrix_Get(Matrix A, unsigned int i, unsigned int j) {
	return TupleOfTuple_Get(A.V, i, j, A.n);
}

void Matrix_Set(Matrix A, double x, unsigned int i, unsigned int j) {
	TupleOfTuple_Set(A.V, x, i, j, A.n);
}

Matrix Matrix_LoadFromFile (char * fn) {
	Matrix A;
	A.V = TupleOfTuple_LoadFromFile(fn, &A.n, &A.m);
	return A;
}
