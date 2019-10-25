OPTIONS = -std=c99 -pedantic -Wall -Wextra -Wtraditional-conversion -Wdeclaration-after-statement -D__USE_MINGW_ANSI_STDIO=1

Solver_General.exe : Solver_General.o
	gcc -o Solver_General.exe Solver_General.o -lm
Solver_General.o : Solver_General.c
	gcc $(OPTIONS) -c Solver_General.c