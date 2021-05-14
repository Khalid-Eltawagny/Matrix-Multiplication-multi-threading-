#include<stdio.h>
#include <memory.h>
#include <errno.h>
#include <stdlib.h>
#include"file_controller.h"

matrix* read_input(char *path){
	FILE *file = fopen(path,"r");
	if(file == NULL){
		fprintf(stderr, "%s\n","Couldn't find this specified file " );
		exit(1);
	} 
	matrix* mat = read_matrix(file); 
	fclose(file);
	return mat ; 
}

void write_output(char *path , int** arr , int n ,int m){
	FILE *file = fopen(path,"w");
	if (file == NULL){
		fprintf(stderr, "%s\n","Couldn't create this file" );
		exit(1);
	}
	write_matrix_into_file(file ,arr,n,m);
	fclose(file);
	return ; 
}