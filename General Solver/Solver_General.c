#include <complex.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

struct VectorGen
{
    char **v;
    unsigned int n;
};
typedef struct VectorGen VectorGen;

typedef char *mult(char *, char *);
typedef char *divide(char *, char *);
typedef char *subtract(char *, char *);

mult multComplex;
divide divideComplex;
subtract subtractComplex;

double complex String_To_Complex(char *);
char *Complex_To_String(double complex);

VectorGen Vandermonde_Gen(VectorGen, VectorGen, mult, divide, subtract);

VectorGen Vandermonde_Gen(VectorGen x, VectorGen rhs, mult mult, divide divide, subtract subtract)
{
    for (int k = 0; k < (int)x.n - 1; k++)
    {
        for (int i = k + 1; i < (int)x.n; i++)
        {
            rhs.v[i] = divide(subtract(rhs.v[i], rhs.v[k]), subtract(x.v[i], x.v[k]));
        }
    }
    for (int xi = x.n - 2; xi >= 0; xi--)
    {
        for (int i = xi; i < (int)x.n - 1; i++)
        {
            rhs.v[i] = subtract(rhs.v[i], mult(x.v[xi], rhs.v[i + 1]));
        }
    }
    return rhs;
}

double complex String_To_Complex(char *s)
{
    char *ptr;
    double complex z;
    ptr = strtok(s, ",");
    z = atof(ptr);
    ptr = strtok(NULL, ",");
    z = z + atof(ptr) * I;
    return z;
}

char *Complex_To_String(double complex z)
{
    char *s = calloc(sizeof(char), 27);
    snprintf(s, 27, "%e,%e", creal(z), cimag(z));
    return s;
}

char *multComplex(char *num1, char *num2)
{
    double complex a, b, c;
    a = String_To_Complex(num1);
    b = String_To_Complex(num2);
    c = a * b;
    return Complex_To_String(c);
}

char *subtractComplex(char *num1, char *num2)
{
    double complex a, b, c;
    a = String_To_Complex(num1);
    b = String_To_Complex(num2);
    c = a - b;
    return Complex_To_String(c);
}

char *divideComplex(char *num1, char *num2)
{
    double complex a, b, c;
    a = String_To_Complex(num1);
    b = String_To_Complex(num2);
    c = a / b;
    return Complex_To_String(c);
}

int main()
{
    char s[] = "3.14,2.2";
    char c[] = "1, 0";
    printf(divideComplex(multComplex(s, c), calloc));

    return 0;
}