#ifndef ELEMENT_THREADED
#define ELEMENT_THREADED

typedef struct {
	int row ; 
	int col ;
} position ; 

void run_element_threaded(int** A , int** B, int** C ,int N , int M , int L);

void* calc_element(void* pos);

#endif