#include "matrix_threaded.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int **M1 , ** M2 , ** M3 ; 
int N,M,L ; 

void run_matrix_threaded(int ** A,int **B ,int** C , int n,int m,int l){

    M1 = A ; 
    M2 = B ;
    M3 = C ; 
    N = n ; 
    M = m ; 
    L = l ; 

    pthread_t thread ; 

    if (pthread_create(&thread,NULL,calc_matrix,NULL)){
        printf("Couldn't create a thread\n");
        exit(-1);
    }

    pthread_join(thread,NULL) ; 
}


void* calc_matrix(void){
    for (int i=0;i<N;i++)
        for (int j=0;j<L;j++)
            for (int k=0;k<M;k++)
                M3[i][j] += M1[i][k] * M2[k][j] ; 
} 