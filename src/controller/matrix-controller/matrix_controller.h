#ifndef MATRIX_CONTROLLER
#define MATRIX_CONTROLLER

#include <stdio.h>

typedef struct {
	int rows;
	int columns;
	int ** arr ;
} matrix ; 

matrix* read_matrix(FILE* file);

void write_matrix_into_file(FILE* file,int **arr,int n, int m);

#endif