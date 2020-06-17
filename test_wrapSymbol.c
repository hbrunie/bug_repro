#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>

typedef void (*dgemm_ptr) (char const *transa, char const *transb, int* m, int* n, int* k,
                        double* alpha, double *A, int* lda, double *B, int* ldb,
                        double* beta, double *C, int* ldc);
dgemm_ptr sym;

__attribute__ ((constructor))
void start_test(void){
    fprintf(stderr, "start0...\n");
    sym = (dgemm_ptr)dlsym(RTLD_NEXT, "dgemm_");
    fprintf(stderr, "start1 %p\n",sym);
}

extern "C" void dgemm_ (char const *transa, char const *transb, int* m, int* n, int* k,
                        double* alpha, double *A, int* lda, double *B, int* ldb,
                        double* beta, double *C, int* ldc){

    fprintf(stderr, "TRY WRAP...\n");
    sym(transa, transb,m,n, k,
                         alpha, A, lda, B, ldb,
                         beta, C, ldc);
    fprintf(stderr, "WRAP SUCCESS\n");
}
