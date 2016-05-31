#pragma once
#include "DiffusionEq.h"
#include "GaussSeidel.h"

class CrankNicolson_GaussSeidel : DiffusionEq {
public:
  CrankNicolson_GaussSeidel(double _D, int _NX, double _L, int _NT, double _TEND);
  void timeStepEvolution() override;

private:

  vd A;
  vd B;
  vd Bpsi;

  void makeA(vd& A);
  void makeB(vd& B);

};
