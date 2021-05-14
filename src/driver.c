
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "logic/row_threaded.h"
#include "logic/element_threaded.h"
#include "logic/matrix_threaded.h"
#include "controller/file-controller/file_controller.h"

int **M1,**M2,**M3 ; 
int N,M,L;

// M1 --> N*M
// M2 --> M*L
// M3 --> N*L

char* outputpath ; 

// read matrix 1  form file and initialize its dimensions N and M
void init_M1(char *path){
    matrix* mat = read_input(path);
    M1 = mat->arr ; 
    N = mat->rows ; 
    M = mat->columns ; 
}

// read matrix 2  form file and initialize its dimensions M and L
void init_M2(char *path){
    matrix* mat = read_input(path) ;
    M2 = mat->arr ;
    L = mat->columns ; 
    // check for Invalid input
    if (mat->rows != M){
        printf("Invalid input\n");
        exit(-1);
    }
}

// allocate space for result array with size N * L 
void allocate_M3(int n ,int m){
    int** arr = (int**) malloc(n*sizeof(int*)) ; 
    for (int i=0;i<n;i++)
        arr[i] = (int *) malloc(m*sizeof(int)) ; 
    M3 = arr ; 
    return ; 
}

// clear result array to be ready before running any function 
void clear_M3(int n,int m){
    for (int i=0;i<n;i++)
        for (int j=0;j<m;j++)
            M3[i][j] = 0 ; 
}

int main(int argc, char *argv[]) {
    if (argc == 4) { // check the argument 
        init_M1(argv[1]);
        init_M2(argv[2]);
        outputpath = argv[3] ;  

    } else { // use default files 
        init_M1("./tests/test3/a.txt");
        init_M2("./tests/test3/b.txt");
        outputpath = "c.txt" ; 
    }
    
    struct timeval stop , start ;
    allocate_M3(N,L) ;

    //////////////////////////////////  THREAD PER MATRIX  /////////////////////////////////
    clear_M3(N,L); 
    gettimeofday(&start,NULL) ; 
    run_matrix_threaded(M1,M2,M3,N,M,L) ; 
    gettimeofday(&stop,NULL);
    printf("Number of threads created in the \"Thread per Matrix\" function = %d\n",1);
    printf("Time taken in seconds =  %lu\n", stop.tv_sec - start.tv_sec);
    printf("Time taken in microseconds = %lu\n\n", stop.tv_usec - start.tv_usec);
    write_output("c1.txt",M3,N,L) ;
    /////////////////////////////////  THREAD PER ROW  ////////////////////////////////////
    clear_M3(N,L);
    gettimeofday(&start,NULL) ; 
    run_row_threaded(M1,M2,M3,N,M,L) ; 
    gettimeofday(&stop,NULL);
    printf("Number of threads created in the \"Thread per Row\" function = %d\n",N);
    printf("Time taken in seconds =  %lu\n", stop.tv_sec - start.tv_sec);
    printf("Time taken in microseconds = %lu\n\n", stop.tv_usec - start.tv_usec);
    write_output("c2.txt",M3,N,L) ;
    /////////////////////////////////  THREAD PER ELEMENT  /////////////////////////////////////
    clear_M3(N,L);
    gettimeofday(&start,NULL) ; 
    run_row_threaded(M1,M2,M3,N,M,L) ; 
    gettimeofday(&stop,NULL);
    printf("Number of threads created in the \"Thread per Element\" function = %d\n",N*L);
    printf("Time taken in seconds =  %lu\n", stop.tv_sec - start.tv_sec);
    printf("Time taken in microseconds = %lu\n\n", stop.tv_usec - start.tv_usec);
    write_output("c3.txt",M3,N,L) ;

    return 0 ; 
}
