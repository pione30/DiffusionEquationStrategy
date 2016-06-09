#include "CrankNicolson_LAPACK.h"

// public:

CrankNicolson_LAPACK::CrankNicolson_LAPACK(double _D, int _NX, double _L, int _NT, double _TEND) :
  DiffusionEq(_D, _NX, _L, _NT, _TEND)
{
  B.resize(2 * NX);
  Bpsi.resize(NX);
  makeB(B);
}

void CrankNicolson_LAPACK::timeStepEvolution(){
  cblas_dsbmv(CblasColMajor, CblasUpper, NX, 1, 1.0, B.data(), 2, psi.data(), 1, 0, Bpsi.data(), 1);

  vd d(NX, 1 / DT + D / (DX * DX));
  vd e(NX - 1, -D / (2 * DX * DX));
  int info = LAPACKE_dptsv(LAPACK_COL_MAJOR, NX, 1, d.data(), e.data(), Bpsi.data(), NX);
  if(info != 0){
    cerr << "LAPACKE_dptsv ERROR! info = " << info << endl;
    exit(1);
  }

  swap(psi, Bpsi);
}

// private:

void CrankNicolson_LAPACK::makeB(vd& B){
  rep(i, NX) B[i * 2] = D / (2 * DX * DX);
  rep(i, NX) B[i * 2 + 1] = 1 / DT - D / (DX * DX);
}

