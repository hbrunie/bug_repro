#include <gotcha/gotcha.h>
#include <cstdio>
gotcha_wrappee_handle_t wrappee_dgemm_handle;
typedef void (*dgemm_ptr) (char const *transa, char const *transb, int* m, int* n, int* k,
                        double* alpha, double *A, int* lda, double *B, int* ldb,
                        double* beta, double *C, int* ldc);
void __overloaded_dgemm (char const *transa, char const *transb, int* m, int* n, int* k,
                        double* alpha, double *A, int* lda, double *B, int* ldb,
                        double* beta, double *C, int* ldc);
struct gotcha_binding_t wrap_actions [] = {
    { "dgemm_", (void*)__overloaded_dgemm, &wrappee_dgemm_handle },
};

dgemm_ptr wrappee_dgemm;

__attribute__ ((constructor))
void start_test(void){
    printf("Start test\n");
    gotcha_wrap(wrap_actions, 1, "PrecisionTuner");
    wrappee_dgemm = (dgemm_ptr) gotcha_get_wrappee(wrappee_dgemm_handle); // get my wrappee from Gotcha
    //wrappee_dgemm(transa, transb, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc);//return void
}

void __overloaded_dgemm (char const *transa, char const *transb, int* m, int* n, int* k,
                        double* alpha, double *A, int* lda, double *B, int* ldb,
                        double* beta, double *C, int* ldc){

    fprintf(stderr, "Before wrappee dgemm call\n");
    wrappee_dgemm(transa, transb, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc);//return void
    fprintf(stderr, "After wrappee dgemm call\n");
}
