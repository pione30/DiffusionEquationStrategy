#pragma once
#include "DiffusionEq.h"

class GSL : public DiffusionEq {
public:
  GSL(double _D, int _NX, double _L, int _NT, double _TEND);
  ~GSL() override;
  void timeStepEvolution() override;

private:
  
  double current_time;
  vd DiffEqK;
  void makeDiffEqK(vd& DiffEqK);

  gsl_odeiv2_system sys;
  gsl_odeiv2_driver* d;

};

namespace GSLfunc{
  int func(double t, const double psi[], double dpsidt[], void* params);
}
