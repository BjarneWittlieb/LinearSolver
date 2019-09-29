#include "Matrix.h"
#include "Matrix_Util.h"
#include "Matrix_Rotate.h"
#include "Vector.h"
#include "Solver.h"
#include <assert.h>
#include <math.h>

// Solves the Matrix Ax = b using givens rotations and saves x in vector b. Also returns b.
Vector Solve_Givens(Matrix A, Vector b)
{
    double s, c, t, x, y, sum;
    assert(A.n == b.n);

    Matrix_Rotate(A);

    // rotate b with givens matrix
    for (unsigned int col = 0; col < A.n - 1; col++)
    {
        for (unsigned int row = col + 1; row < A.n; row++)
        {
            // setting s and c using stored value t = s/c in the matrix A
            t = Matrix_Get(A, row, col);
            c = sqrt(1 / (1 + t * t));
            if (c == 0)
            {
                s = copysign(1.0, t);
            }
            else
            {
                s = c * t;
            }
            // multipling givens matrix to b
            x = b.v[col];
            y = b.v[row];
            b.v[col] = x * c - y * s;
            b.v[row] = x * s + y * c;
        }
    }
    // Vector_Report(stdout, b, "%lf", "Modifiziertes b");

    // calculating solution and storing it in vector b
    for (int i = A.n - 1; i >= 0; i--)
    {
        sum = 0;
        for (unsigned int j = i + 1; j < A.n; j++)
        {
            sum += b.v[j] * Matrix_Get(A, (unsigned int)i, j);
        }
        b.v[i] = (-sum + b.v[i]) / Matrix_Get(A, (unsigned int)i, (unsigned int)i);
    }

    return b;
}

// solves the Matrix Ax = b using gaussian algorithm and saves x in vector b and also returns b.
Vector Solve_Gauss(Matrix A, Vector b)
{
    double lambda, x, y, sum;
    assert(A.n == b.n);

    Matrix_Gauss(A);

    // gauss on b, oh yeah
    for (unsigned int col = 0; col < A.n - 1; col++)
    {
        for (unsigned int row = col + 1; row < A.n; row++)
        {
            lambda = Matrix_Get(A, row, col);
            x = b.v[col];
            y = b.v[row];
            b.v[row] = y + lambda * x;
        }
    }
    // Vector_Report(stdout, b, "%lf", "Modifiziertes b");

    // calculating solution and storing it in vector b
    for (int i = A.n - 1; i >= 0; i--)
    {
        sum = 0;
        for (unsigned int j = i + 1; j < A.n; j++)
        {
            sum += b.v[j] * Matrix_Get(A, (unsigned int)i, j);
        }
        b.v[i] = (-sum + b.v[i]) / Matrix_Get(A, (unsigned int)i, (unsigned int)i);
    }

    return b;
}

// creates a Vandermonte Matrix with vector x and solves for y using recursiveness. Stores result in y.
Vector Solve_Vandermonte(Vector x, Vector rhs)
{
    // the outer loop, where the dimension goes down. but the actual value i need is low, so dimension goes up i guess
    for (int dim = 1; dim <= x.n; dim++)
    {
        for (int i = dim; i < x.n; i++)
        {
            rhs.v[i] = (rhs.v[i] - rhs.v[dim - 1]) / (x.v[i] - x.v[dim - 1]);
        }
    }
    // Vector_Report(stdout, rhs, "%lf", "the vector rhs in mid");
    for (int xi = x.n - 2; xi >= 0; xi--)
    {
        for (int i = xi; i < x.n - 1; i++)
        {
            rhs.v[i] = rhs.v[i] - x.v[xi] * rhs.v[i + 1];
            // printf("i: %u, xi: %u\n", i, xi);
            // Vector_Report(stdout, rhs, "%lf", "the vector rhs in mid mid");
        }
    }

    return rhs;
}

void Compare(Vector alpha)
{
    Vector x;
    Vector rhs;
    double step;

    x = Vector_Create(alpha.n);
    rhs = Vector_Create(alpha.n);
    step = 2.0 / (alpha.n - 1);

    // creating the vector x
    for (int i = 0; i < alpha.n; i++)
    {
        x.v[i] = -1.0 + step * i;
    }

    // evaluting the right hand side
    for (int i = 0; i < x.n; i++)
    {
        for (int j = 0; j < x.n; j++)
        {
            rhs.v[i] += myPow(x.v[i], j) * alpha.v[j];
        }
    }

    Vector_Report(stdout, x, "%lf", "This is vector x");
    Vector_Report(stdout, rhs, "%lf", "This is vector rhs");

    Solve_Vandermonte(x, rhs);
    Vector_Report(stdout, rhs, "%lf", "This is the solved alpha.");
}

double myPow(double x, unsigned int n)
{
    double y;

    y = 1;
    for (unsigned int i = 0; i < n; i++)
    {
        y *= x;
    }

    return y;
}

int main(void)
{
    Vector a;
    a = Vector_Create(4);

    a.v[0] = 0;
    a.v[1] = 0;
    a.v[2] = 0;
    a.v[3] = 1;

    Vector_Report(stdout, a, "%lf", "This is the alpha started with");
    Compare(a);
}