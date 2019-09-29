#include "Matrix.h"
#include "Vector.h"
#include "Matrix_Util.h"
#include <assert.h>
#include "RNG.h"

Matrix Matrix_Create_Vandermonde (Vector x) {
	double tmp;
	Matrix A;
	
	A = Matrix_Create(x.n, x.n);
	for (unsigned int i = 0; i < x.n; i++) {
		tmp = 1;
		for (unsigned int j = 0; j < x.n; j++) {
			Matrix_Set (A, tmp, i, j);
			tmp *= x.v[i];
		}
	}
	return A;
}

void Matrix_Gauss (Matrix A) {
	double lambda, x, y, tmp1, tmp2;
	
	for (unsigned int startIndex = 0; startIndex < A.m - 1; startIndex++) {
		for (unsigned int i = startIndex + 1; i < A.m; i++) {
			x = Matrix_Get(A, startIndex, startIndex);
			y = Matrix_Get(A, i, startIndex);

			assert (x!= 0);
			
			lambda = - y / x;
			
			for (unsigned int j = startIndex; j < (unsigned int) A.m; j++) {
				tmp1 = Matrix_Get(A, i, j);
				tmp2 = Matrix_Get(A, startIndex, j);
				Matrix_Set(A, lambda * tmp2 + tmp1, i, j);
			}
			Matrix_Set(A, lambda, i, startIndex);
		}
	}	
}

void Matrix_Gauss_Back (Matrix A) {
	double lambda, tmp1, tmp2;

	for (int col = A.m - 2; col >= 0; col--) {
		for (int row = A.m-1; row > col; row-- ) {
			lambda = Matrix_Get(A, (unsigned int) row, (unsigned int) col);

			tmp1 = Matrix_Get(A, (unsigned int) col, (unsigned int) col);
			Matrix_Set(A, -lambda * tmp1, (unsigned int) row, (unsigned int) col);
			for (unsigned int j = col + 1; j < A.m; j++ ) {
				tmp1 = Matrix_Get(A, (unsigned int) row, j);
				tmp2 = Matrix_Get(A, (unsigned int) col, j);
				Matrix_Set(A, tmp1 - lambda * tmp2, (unsigned int) row, j);
			}
		}
	}
}