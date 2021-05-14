#include "element_threaded.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int **M1 , **M2, **M3 ; 
int N,M,L ;  

//M3 will be N * L 


position* create_struct(int i,int j){
	position* p = malloc(sizeof(position)) ; 
	p->row = i ; 
	p->col = j ; 
	return p ; 
}

void run_element_threaded(int** A , int** B, int** C ,int n , int m , int l){
	M1 = A ; 
	M2 = B ; 
	M3 = C ; 
	N = n  ;
	M = m  ;
	L = l  ;
	pthread_t threads[N][L] ; 
	for (int i=0;i<N;i++){
		for (int j=0;j<L;j++){
			if (pthread_create(&threads[i][j],NULL,calc_element,(void *)create_struct(i,j))){
				printf("%s\n","Couldn't create a thread\n" );
				exit(-1);
			}
		}
	}

	for (int i=0;i<N;i++){
		for (int j=0;j<L;j++){
			pthread_join(threads[i][j],NULL) ; 
		}
	}

}

void* calc_element(void* pos){

	position* p = (position*) pos ; 

	int r = p->row ;
	int c = p->col ;  

	for (int j=0;j<M;j++)
		M3[r][c] += M1[r][j] * M2[j][c] ;

}