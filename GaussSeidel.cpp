#include "GaussSeidel.h"

// A is a symmetric tridiagonal matrix.
// b will be overwritten by the result.
void GaussSeidel_st(const vd& A, vd &b){
  double EPS = 1e-10;
  int N = b.size();

  vd prevx(N);
  vd x(N);

  while(true){
    rep(i, N){
      x[i] = b[i];
      if(i - 1 >= 0) x[i] -= A[i * 2] * x[i - 1];
      if(i + 1 < N)  x[i] -= A[(i + 1) * 2] * x[i + 1];
      x[i] /= A[i * 2 + 1];
    }

    // evaluate the difference between x and prevx
    cblas_daxpy(N, -1.0, x.data(), 1, prevx.data(), 1);
    if(cblas_dnrm2(N, prevx.data(), 1) < EPS) break;

    cblas_dcopy(N, x.data(), 1, prevx.data(), 1);
  }
  
  b = move(x);
}
