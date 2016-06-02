#pragma once
#include "DiffusionEq.h"

class FFTW : public DiffusionEq {
public:
  FFTW(double _D, int _NX, double _L, int _NT, double _TEND);
  ~FFTW() override;
  void timeStepEvolution() override;
  void output(int ti) const override;

private:

  inline fftw_complex* fftwcast(vC& f);
  double m2k(int m) const;

  vC psi_in;
  vC psi_out;
  void initPsi_in(vC& psi_in);
  
  vd time_evolver;
  void makeTimeEvolver(vd& te);

  fftw_plan plan_initPsiTilde;
  fftw_plan plan;
  
};
