OPTIONS = -std=c99 -pedantic -Wall -Wextra -Wtraditional-conversion -Wdeclaration-after-statement -D__USE_MINGW_ANSI_STDIO=1

Solver.exe : Solver.o Matrix.o Vector.o Tuple.o Random.o RNG.o Rotate.o Matrix_Rotate.o
	gcc -o Solver.exe Solver.o Matrix.o Vector.o Tuple.o Random.o RNG.o Rotate.o Matrix_Rotate.o -lm
Solver.o : Solver.c Solver.h
	gcc $(OPTIONS) -c Solver.c
	
Matrix.o : Matrix.c Matrix.h
	gcc $(OPTIONS) -c Matrix.c
	
Vector.o : Vector.c Vector.h
	gcc $(OPTIONS) -c Vector.c
	
Tuple.o : Tuple.c Tuple.h
	gcc $(OPTIONS) -c Tuple.c

Random.o : Random.c Random.h
	gcc $(OPTIONS) -c Random.c

RNG.o : RNG.c RNG.h
	gcc $(OPTIONS) -c RNG.c

Rotate.o : Rotate.c Rotate.h
	gcc $(OPTIONS) -c Rotate.c

Matrix_Rotate.o : Matrix_Rotate.c Matrix_Rotate.h
	gcc $(OPTIONS) -c Matrix_Rotate.c

clear:
	del *.exe
	del *.o