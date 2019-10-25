#ifndef Solver_Header
#define Solver_Header

#include <stdio.h>
#include "Matrix.h"
#include "Vector.h"

Vector Solve_Triangular_Backwards(Matrix, Vector);
Vector Solve_Givens(Matrix, Vector);
Vector Solve_Gauss(Matrix, Vector);
Vector Solve_Vandermonte(Vector, Vector);

double evaluate_Polynom(double, Vector);
void Compare(FILE *, Vector);

#endif