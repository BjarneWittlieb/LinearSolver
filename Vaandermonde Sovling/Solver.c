#include "Matrix.h"
#include "Matrix_Rotate.h"
#include "Vector.h"
#include "Solver.h"
#include <assert.h>
#include <math.h>

Vector Solve_Triangular_Backwards(Matrix A, Vector b)
{
    double sum;
    assert(A.n == b.n && A.n != 0);
    for (unsigned int i = A.n; i >= 1; i--)
    {
        sum = 0;
        for (unsigned int j = i; j < A.n; j++)
        {
            sum += b.v[j] * Matrix_Get(A, i - 1, j);
        }
        b.v[i - 1] = (-sum + b.v[i]) / Matrix_Get(A, i - 1, i);
    }
    return b;
}

// Solves the Matrix Ax = b using givens rotations and saves x in vector b. Also returns b.
Vector Solve_Givens(Matrix A, Vector b)
{
    double s, c, t, x, y;
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

    return Solve_Triangular_Backwards(A, b);
}

// solves the Matrix Ax = b using gaussian algorithm and saves x in vector b and also returns b.
Vector Solve_Gauss(Matrix A, Vector b)
{
    double lambda, x, y;
    assert(A.n == b.n);
    Matrix_Gauss(A);

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
    return Solve_Triangular_Backwards(A, b);
}

// creates a Vandermonte Matrix with vector x and solves for y using recursiveness. Stores result in y.
Vector Solve_Vandermonte(Vector x, Vector rhs)
{
    for (int k = 0; k < (int)x.n - 1; k++)
    {
        for (int i = k + 1; i < (int)x.n; i++)
        {
            rhs.v[i] = (rhs.v[i] - rhs.v[k]) / (x.v[i] - x.v[k]);
        }
    }
    for (int xi = x.n - 2; xi >= 0; xi--)
    {
        for (int i = xi; i < (int)x.n - 1; i++)
        {
            rhs.v[i] = rhs.v[i] - x.v[xi] * rhs.v[i + 1];
        }
    }
    return rhs;
}

void Compare(FILE *F, Vector alpha)
{
    Vector x;
    Vector rhs;
    double step;

    x = Vector_Create(alpha.n);
    rhs = Vector_Create(alpha.n);
    step = 2.0 / (alpha.n - 1);

    // creating the vector x
    for (int i = 0; (unsigned int)i < alpha.n; i++)
    {
        x.v[i] = -1 + step * i;
        // x.v[i] = pow(2.0, -(double)i);
    }

    // evaluting the right hand side
    for (int i = 0; (unsigned int)i < x.n; i++)
    {
        rhs.v[i] = evaluate_Polynom(x.v[i], alpha);
    }

    Vector_Report(F, x, "%e", "This is vector x");
    Vector_Report(F, rhs, "%e", "This is vector rhs");

    Solve_Vandermonte(x, rhs);
    Vector_Report(F, rhs, "%e", "This is the solved alpha.");
    fprintf(F, "The relative error:\n");
    for (unsigned int i = 0; i < x.n; i++)
    {
        fprintf(F, "%u %e\n", i, fabs(alpha.v[i] - rhs.v[i]) / fabs(alpha.v[i]));
    }
}

// calculates a value of a polynom where the coefficients are stored in alpha evaluated in x.
double evaluate_Polynom(double x, Vector alpha)
{
    double y;

    y = 0;
    for (int i = (int)alpha.n; i >= 0; i--)
    {
        y = y * x + alpha.v[i];
    }
    return y;
}

int main(int k, char **args)
{
    int n;
    Vector a;
    RNG rng;
    FILE *F;

    rng = RNG_Set_Knuth();
    n = (int)atof(args[1]);
    F = fopen("moin.txt", "w+");
    a = Vector_Create_Random((unsigned int)n, &rng, -10.0, 10.0);

    Vector_Report(F, a, "%.2e", "This is the alpha started with");
    Compare(F, a);

    fclose(F);
}