#include "DiffusionEq_CrankNicolson.h"

// public:

DiffusionEq_CrankNicolson::DiffusionEq_CrankNicolson(double _D, int _NX, double _L, int _NT, double _TEND) :
  D(_D), NX(_NX), L(_L), DX(L / (NX + 1)), NT(_NT), TEND(_TEND), DT(TEND / NT)
{
  A.resize(2 * NX);
  B.resize(2 * NX);
  psi.resize(NX);
  Bpsi.resize(NX);
  makeA(A);
  makeB(B);
  initPsi(psi);
}

void DiffusionEq_CrankNicolson::timeStepEvolution_GaussSeidel(){
  cblas_dsbmv(CblasColMajor, CblasUpper, NX, 1, 1.0, B.data(), 2, psi.data(), 1, 0, Bpsi.data(), 1);
  GaussSeidel_st(A, Bpsi);
  cblas_dcopy(NX, Bpsi.data(), 1, psi.data(), 1);
}

void DiffusionEq_CrankNicolson::timeStepEvolution_LAPACK(){
  cblas_dsbmv(CblasColMajor, CblasUpper, NX, 1, 1.0, B.data(), 2, psi.data(), 1, 0, Bpsi.data(), 1);

  vd d(NX, 1 / DT + D / (DX * DX));
  vd e(NX - 1, -D / (2 * DX * DX));
  int info = LAPACKE_dptsv(LAPACK_COL_MAJOR, NX, 1, d.data(), e.data(), Bpsi.data(), NX);
  if(info != 0){
    cerr << "LAPACKE_dptsv ERROR! info = " << info << endl;
    exit(1);
  }

  cblas_dcopy(NX, Bpsi.data(), 1, psi.data(), 1);
}

void DiffusionEq_CrankNicolson::output(int ti) const {
  ostringstream os;
  os << "res/output" << ti << ".txt";
  ofstream ofs(os.str());
  ofs << "### x \t psi(x)" << endl;
  rep(i, NX) ofs << i2x(i) << "\t" << psi[i] << endl;
}

// private:

double DiffusionEq_CrankNicolson::i2x(int i) const {
  return -L / 2 + (i + 1) * DX;
}

void DiffusionEq_CrankNicolson::makeA(vd& A){
  rep(i, NX) A[i * 2] = -D / (2 * DX * DX);
  rep(i, NX) A[i * 2 + 1] = 1 / DT + D / (DX * DX);
}

void DiffusionEq_CrankNicolson::makeB(vd& B){
  rep(i, NX) B[i * 2] = D / (2 * DX * DX);
  rep(i, NX) B[i * 2 + 1] = 1 / DT - D / (DX * DX);
}

void DiffusionEq_CrankNicolson::initPsi(vd& psi){
  auto fx0 = [&](int i) {
    return pow(2 * M_PI * D, -0.5) * exp(-i2x(i) * i2x(i) / (2 * D));
  };
  rep(i, NX) psi[i] = fx0(i);
}
