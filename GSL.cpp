#include "GSL.h"

// public:

GSL::GSL(double _D, int _NX, double _L, int _NT, double _TEND) :
  DiffusionEq(_D, _NX, _L, _NT, _TEND)
{
  current_time = 0;
  DiffEqK.resize(2 * NX);
  makeDiffEqK();
  sys = { GSLfunc::func, nullptr, (size_t)NX, &DiffEqK };
  d = gsl_odeiv2_driver_alloc_y_new(&sys, gsl_odeiv2_step_rk8pd, 1e-6, 1e-6, 0.0);
}

GSL::~GSL(){
  gsl_odeiv2_driver_free(d);
}

void GSL::timeStepEvolution(){
  int status = gsl_odeiv2_driver_apply(d, &current_time, current_time + DT, psi.data());
  if (status != GSL_SUCCESS){
    cerr << "error, return value=" << status << endl;
    exit(1);
  }
}

// private:

void GSL::makeDiffEqK(){
  auto index = [&](int i, int j) { return i + 2 * j; };

  rep(j, NX) rep(i, 2){
    DiffEqK[index(i, j)] = (i == 0 ? 1 : -2) / (DX * DX);
  }
  cblas_dscal(NX, D, DiffEqK.data(), 1);
}

// GSLfunc

int GSLfunc::func(double t, const double psi[], double dpsidt[], void* params){
  vd* DiffEqK = (vd*)params;
  int NX = DiffEqK->size() / 2;

  cblas_dsbmv(CblasColMajor, CblasUpper, NX, 1, 1.0, DiffEqK->data(), 2, psi, 1, 0, dpsidt, 1);
  return GSL_SUCCESS;
}
