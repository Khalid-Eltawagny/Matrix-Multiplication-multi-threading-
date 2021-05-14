#include"row_threaded.h"
#include<stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

int ** M1, ** M2,** M3 ; 
int N,M,L ; 
// M3 = N * L 
void run_row_threaded(int** A ,int** B ,int** C , int n , int m ,int l){
    M1 = A ; 
    M2 = B ; 
    M3 = C ; 
    N = n ; 
    M = m ; 
    L = l ; 
    pthread_t threads[N] ; 
    for (int i=0;i<N;i++){
        if(pthread_create(&threads[i],NULL,calc_row,(void *)i )){
            printf("Couldn't create a thread\n") ; 
            exit(-1) ; 
        }
    }

    for (int i=0;i<N;i++){
        pthread_join(threads[i],NULL);
    }
}

void* calc_row(void* row){
    int r = (int) row  ;
    for (int c = 0 ; c < L ; c++){
        for (int j=0;j<M;j++){
            M3[r][c] += M1[r][j] * M2[j][c] ; 
        }
    }
}