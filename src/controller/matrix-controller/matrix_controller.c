#include<stdio.h>
#include<stdlib.h>
#include"matrix_controller.h"

int** allocate_matrix(int n,int m){
	int **arr  = (int **) malloc(n * sizeof(int *)) ;
	for (int i=0;i<n;i++)
		arr[i] = (int *) malloc(m * sizeof(int)) ; 
	
	return arr ; 
}

void set_dimentions(matrix* mat , char* first_line){
	char *line = first_line + 4 ; // to skip row=
	mat->rows = strtol(line,&line,0) ; 
	line += 5 ; //to skip ' col'
	mat->columns = strtol(line,&line,0) ;
	return ; 
}

void set_matrix_attributes(matrix *mat , char * first_line){
	set_dimentions(mat,first_line) ;
	mat->arr = allocate_matrix(mat->rows,mat->columns);
	return ; 
}

void read_row(int** mat , char* line , int row, int columns){
 
	for (int j=0;j<columns;j++){
		mat[row][j] = strtol(line,&line,0) ; 
	}
	return ;
}

matrix* read_matrix(FILE* file){
	matrix* mat = malloc(sizeof(matrix)) ; 
	size_t sz = 1000 ; // random big number
	char* line = (char*) malloc(sz);
	getline(&line,&sz,file);
	set_matrix_attributes(mat,line);
	int i = 0 ;  
	while(getline(&line,&sz,file) != -1){
		read_row(mat->arr,line,i++,mat->columns) ; 
	}
	free(line);
	return mat ; 
}

void write_matrix_into_file(FILE* file,int **mat,int n, int m){
	int i,j;
	for (i=0;i<n;i++){
		for (j=0;j<m-1;j++){
			fprintf(file, "%d\t",mat[i][j]);
		}
		fprintf(file, "%d\n", mat[i][j] );
	}
}
