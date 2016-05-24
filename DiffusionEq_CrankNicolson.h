#pragma once
#include "utilities.h"
#include "GaussSeidel.h"

class DiffusionEq_CrankNicolson {
public:
  DiffusionEq_CrankNicolson(double _D, int _NX, double _L, int _NT, double _TEND);
  void timeStepEvolution_GaussSeidel();
  void timeStepEvolution_LAPACK();
  void output(int ti) const;

private:

  double D; // diffusion coefficient
  int NX;
  double L;
  double DX;
  double i2x(int i) const;
  int NT;
  double TEND;
  double DT;

  vd A;
  vd B;
  vd psi;
  vd Bpsi;

  void makeA(vd& A);
  void makeB(vd& B);
  void initPsi(vd& psi);

};
