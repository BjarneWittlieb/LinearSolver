#ifndef Util_Header
#define Util_Header

#include "Matrix.h"
#include "Vector.h"

Matrix Matrix_Create_Vandermonde (Vector);
void Matrix_Gauss (Matrix);
void Matrix_Gauss_Back (Matrix);

#endif