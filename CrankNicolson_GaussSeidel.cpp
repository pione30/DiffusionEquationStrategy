#include "CrankNicolson_GaussSeidel.h"

// public:

CrankNicolson_GaussSeidel::CrankNicolson_GaussSeidel(double _D, int _NX, double _L, int _NT, double _TEND) :
  DiffusionEq(_D, _NX, _L, _NT, _TEND)
{
  A.resize(2 * NX);
  B.resize(2 * NX);
  Bpsi.resize(NX);
  makeA(A);
  makeB(B);
}

void CrankNicolson_GaussSeidel::timeStepEvolution(){
  cblas_dsbmv(CblasColMajor, CblasUpper, NX, 1, 1.0, B.data(), 2, psi.data(), 1, 0, Bpsi.data(), 1);
  GaussSeidel_st(A, Bpsi);
  cblas_dcopy(NX, Bpsi.data(), 1, psi.data(), 1);
}

// private:

void CrankNicolson_GaussSeidel::makeA(vd& A){
  rep(i, NX) A[i * 2] = -D / (2 * DX * DX);
  rep(i, NX) A[i * 2 + 1] = 1 / DT + D / (DX * DX);
}

void CrankNicolson_GaussSeidel::makeB(vd& B){
  rep(i, NX) B[i * 2] = D / (2 * DX * DX);
  rep(i, NX) B[i * 2 + 1] = 1 / DT - D / (DX * DX);
}

