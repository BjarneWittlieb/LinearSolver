#include "Matrix.h"
#include "Matrix_Util.h"
#include "Matrix_Rotate.h"
#include "Vector.h"
#include <assert.h>
#include <math.h>

// Solves the Matrix Ax = b using givens rotations and saves x in vector b. Also returns b.
Vector Solve_Givens(Matrix A, Vector b) {
    double s, c, t, x, y, sum;
    assert(A.n == b.n);
    
    Matrix_Rotate(A);

    // rotate b with givens matrix
    for (unsigned int col = 0; col < A.n - 1; col++) {
        for (unsigned int row = col + 1; row < A.n; row++) {
            // setting s and c using stored value t = s/c in the matrix A
            t = Matrix_Get(A, row, col);
            c = sqrt(1 / (1 + t*t));
            if (c == 0) {
				s = copysign(1.0, t);
			} else {
				s = c * t;
			}
            // multipling givens matrix to b
            x = b.v[col];
            y = b.v[row];
            b.v[col] = x*c - y*s;
            b.v[row] = x*s + y*c;
        }
    }
    // Vector_Report(stdout, b, "%lf", "Modifiziertes b");

    // calculating solution and storing it in vector b
    for (int i = A.n-1; i >=0; i--) {
        sum = 0;
        for (unsigned int j = i + 1; j < A.n; j++) {
            sum += b.v[j] * Matrix_Get(A, (unsigned int) i, j);
        }
        b.v[i] = (-sum + b.v[i]) / Matrix_Get(A, (unsigned int) i, (unsigned int) i);
    }

    return b;
}

// solves the Matrix Ax = b using gaussian algorithm and saves x in vector b and also returns b.
Vector Solve_Gauss(Matrix A, Vector b) {
    double lambda, x, y, sum;
    assert(A.n == b.n);

    Matrix_Gauss(A);

    // gauss on b, oh yeah
    for (unsigned int col = 0; col < A.n - 1; col++) {
        for (unsigned int row = col + 1; row < A.n; row++) {
            lambda = Matrix_Get(A, row, col);
            x = b.v[col];
            y = b.v[row];
            b.v[row] = y + lambda * x;
        }
    }    
    // Vector_Report(stdout, b, "%lf", "Modifiziertes b");

    // calculating solution and storing it in vector b
    for (int i = A.n-1; i >=0; i--) {
        sum = 0;
        for (unsigned int j = i + 1; j < A.n; j++) {
            sum += b.v[j] * Matrix_Get(A, (unsigned int) i, j);
        }
        b.v[i] = (-sum + b.v[i]) / Matrix_Get(A, (unsigned int) i, (unsigned int) i);
    }

    return b;
}

// creates a Vandermonte Matrix with vector x and solves for y using recursiveness. Stores result in y.
Vector Solve_Vandermonte(Vector x, Vector rhs) {
    // the outer loop, where the dimension goes down. but the actual value i need is low, so dimension goes up i guess
    for (int dim = 1; dim <= x.n; dim++) {
        for (int i = dim; i < x.n; i++) {
            rhs.v[i] = (rhs.v[i] - rhs.v[dim-1]) / (x.v[i] - x.v[dim-1]);
        }
    }
    for (int i = 1; i < x.n; i++ ) {
        for (int j = i; j > 1; j--) {
            if (i + 1 != x.n) {}
                rhs.v[i] -= x.v[j] * rhs.v[i+1];
            }
        }
    }
    return rhs;
}

int main(void) {
    Vector rhs;
    Vector x;
    
    x = Vector_Create(4);
    rhs = Vector_Create(4);

    x.v[0] = -1;
    x.v[1] = -0.5;
    x.v[2] = 0.5;
    x.v[3] = 1;

    rhs.v[0] = -1;
    rhs.v[1] = -0.5;
    rhs.v[2] = 0.5;
    rhs.v[3] = 1;

    Vector_Report(stdout, x, "%lf", "x");
    Vector_Report(stdout, rhs, "%lf", "rhs");
    Solve_Vandermonte(x, rhs);
    Vector_Report(stdout, x, "%lf", "x");
    Vector_Report(stdout, rhs, "%lf", "rhs");

}