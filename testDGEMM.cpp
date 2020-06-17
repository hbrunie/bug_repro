#include <cstdlib>
#include <cmath>
#include <mkl.h>
#include <iostream>

extern "C"{
  void dgemm_(char const *transa, char const *transb, int *m, int *n, int *k,
              double *alpha, double *A, int *lda, double *B, int *ldb,
              double *beta, double *C, int *ldc);
  void sgemm_(char const *transa, char const *transb, int *m, int *n, int *k,
              float *alpha, float *A, int *lda, float *B, int *ldb, float *beta,
              float *C, int *ldc);
}
using namespace std;
int main(){
    int m = 10;
    int n = 10;
    int k = 10;
    double * A = (double*) mkl_malloc(m*k*sizeof(double), 64);
    double * B = (double*) mkl_malloc(k*n*sizeof(double), 64);
    double * C = (double*) mkl_malloc(m*n*sizeof(double), 64);
    for(int i=0; i<m*k;i++)
        A[i] = i;
    for(int i=0; i<n*k;i++)
        B[i] = i;
    double alpha = 1.0;
    double beta = 0.0;
    //cblas_dgemm(CblasRowMajor,CblasNoTrans,CblasNoTrans, m, n, k, alpha, A, k, B, n, beta, C, n);
    dgemm_("CblasNoTrans","CblasNoTrans", &m, &n, &k, &alpha, A, &k, B, &n, &beta, C, &n);
    double res = cblas_dnrm2(m*n,C,n);
    for(int i=0; i<3;i++)
        fprintf(stderr, "C[%d] = %f\n", i, C[i]);
    cout << "SUCCESS: "<< res << endl;
    mkl_free(A);
    mkl_free(B);
    mkl_free(C);
    return 0;
}
