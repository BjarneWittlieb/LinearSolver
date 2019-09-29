#include "Matrix.h"
#include "Vector.h"

Vector Solve_Givens(Matrix, Vector);
Vector Solve_Gauss(Matrix, Vector);
Vector Solve_Vandermonte(Vector, Vector);

double myPow(double, unsigned int);
void Compare(Vector);