#include"../matrix-controller/matrix_controller.h"
#ifndef FILE_CONTROLLER
#define FILE_CONTROLLER
#include <stdio.h>

matrix* read_input(char *path) ; 
void write_output(char *path , int** arr , int n ,int m);

#endif
