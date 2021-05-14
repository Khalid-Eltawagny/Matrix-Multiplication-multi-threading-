#ifndef ROW_THREADED
#define ROW_THREADED

void run_row_threaded(int** A ,int** B ,int** C , int n , int m ,int l); 
void* calc_row(void* row) ; 

#endif