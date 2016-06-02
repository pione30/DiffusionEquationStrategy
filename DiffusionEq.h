#pragma once
#include "utilities.h"

class DiffusionEq{
public:
  virtual ~DiffusionEq(){};
  virtual void timeStepEvolution() = 0;
  void output(int ti) const;
  
protected:
  
  DiffusionEq(double _D, int _NX, double _L, int _NT, double _TEND);

  const double D; // diffusion coefficient
  const int NX;
  const double L;
  const double DX;
  double i2x(int i) const;
  const int NT;
  const double TEND;
  const double DT;

  vd psi;

private:

  void initPsi(vd& psi);

};
