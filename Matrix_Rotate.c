#include "Matrix.h"
#include <stdio.h>
#include <math.h>

void Matrix_Rotate(Matrix);
void Matrix_Rotate_Back (Matrix);

void Matrix_Rotate_Back (Matrix A) {
	double x, y, s, c, t, alpha;
	
	for (int col = (int) A.n - 2; col >= 0; col--) {
		for (int row = A.n - 1; row > col; row--) {
			alpha = Matrix_Get(A, (unsigned int) col, (unsigned int) col);
			// getting the quotient s/c
			t = Matrix_Get(A, (unsigned int) row, (unsigned int) col);
			c = sqrt(1 / (1 + t*t));
			if (c == 0) {
				s = copysign(1.0, t);
			} else {
				s = c * t;
			}
			Matrix_Set(A, c * alpha, (unsigned int) col, (unsigned int) col);
			Matrix_Set(A, - s * alpha, (unsigned int) row, (unsigned int) col);
			for (unsigned int i = col + 1 ; i < A.n; i++) {
				x = Matrix_Get(A, (unsigned int) col, i);
				y = Matrix_Get(A, (unsigned int) row, i);
				Matrix_Set(A, c * x + s * y, (unsigned int) col, i);
				Matrix_Set(A, - s * x + c * y, (unsigned int) row, i);
			}
		}
	}
}

void Matrix_Rotate(Matrix A) {
	
	double x, y, s, c, alpha, tmpx, tmpy;
	
	for (unsigned int startIndex = 0; startIndex < (unsigned int) A.m - 1; startIndex++) {
		for (unsigned int i = startIndex + 1; i < (unsigned int) A.m; i++) {
			x = Matrix_Get(A, startIndex, startIndex);
			y = Matrix_Get(A, i, startIndex);
			alpha = copysign(sqrt(x * x + y * y), x);
			if (y == 0) {
				c = 1; s = 0;
			} else {
				c = x / alpha;
				s = - y / alpha;
			}
			// setting all values after the rotation. The 0s to s/c
			for (unsigned int j = startIndex; j < (unsigned int) A.m; j++) {
				tmpx = Matrix_Get(A, startIndex, j);
				tmpy = Matrix_Get(A, i, j);
				Matrix_Set(A, c * tmpx - s * tmpy , startIndex, j);
				Matrix_Set(A, s * tmpx + c * tmpy, i, j);
			}
			Matrix_Set(A, s / c, i, startIndex);
		}
	}	
}