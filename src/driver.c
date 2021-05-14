
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "logic/row_threaded.h"
#include "logic/element_threaded.h"
#include "logic/matrix_threaded.h"
#include "controller/file-controller/file_controller.h"
int ** M1 , ** M2 , ** M3 ; 
int N,M,L; 
// C is N * L 

char* outputpath ; 
void init_M1(char *path){
    matrix* mat = read_input(path);
    M1 = mat->arr ; 
    N = mat->rows ; 
    M = mat->columns ; 
}
void init_M2(char *path){
    matrix* mat = read_input(path) ;
    M2 = mat->arr ;
    L = mat->columns ; 
    if (mat->rows != M){
        printf("Invalid input\n");
        exit(-1);
    }
}

void allocate_M3(int n ,int m){
    int** arr = (int**) malloc(n*sizeof(int*)) ; 
    for (int i=0;i<n;i++)
        arr[i] = (int *) malloc(m*sizeof(int)) ; 
    M3 = arr ; 
    return ; 
}

void clear_M3(int n,int m){
    for (int i=0;i<n;i++)
        for (int j=0;j<m;j++)
            M3[i][j] = 0 ; 
}
int main(int argc, char *argv[]) {
    if (argc == 4) { // all files provided -including program name-
        init_M1(argv[1]);
        init_M2(argv[2]);
        outputpath = argv[3] ;  

    } else { // use default files
        init_M1("./tests/test3/a.txt");
        init_M2("./tests/test3/b.txt");
        outputpath = "c.out" ; 
    }
    
    allocate_M3(N,L) ;
    clear_M3(N,L);
    run_matrix_threaded(M1,M2,M3,N,M,L) ;  
    write_output(outputpath,M3,N,L) ;
    return 0 ; 
}
