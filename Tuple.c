#include "Tuple.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>


double * Tuple_Create(size_t length) {
	double * tmp = NULL;
	tmp = calloc(length, sizeof(double));
	return tmp;
}

void Tuple_Destroy(double * tuple) {
	free(tuple);
}

void Tuple_Report(FILE * F, size_t length, double * tuple, char * fmt, char * info) {
	fprintf(F, "# Reporting Tuple (length %u):\n", (int)length);
	fprintf(F, "#Info: %s\n", info);
	for (size_t i = 0; i < length; i++) {
		fprintf(F, fmt, tuple[i]);
		fprintf(F, "\n");
	}
	fprintf(F, "\n");
}


unsigned int * TupleOfUnsignedInt_Create(size_t length) {
	unsigned int * tmp = NULL;
	tmp = calloc(length, sizeof(unsigned int));
	return tmp;
}

void TupleOfUnsignedInt_Destroy(unsigned int * tuple) {
	free(tuple);
}

void TupleOfUnsignedInt_Report(FILE * F, size_t length, unsigned int * tuple, char * fmt, char * info) {
	fprintf(F, "# Rporting Tuple of unsigned int (length %u):\n", (int)length);
	fprintf(F, "#Info: %s\n", info);
	for (size_t i = 0; i < length; i++) {
		fprintf(F, fmt, tuple[i]);
		fprintf(F, "\n");
	}
	fprintf(F, "\n");
}