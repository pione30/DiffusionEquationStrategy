#pragma once
#include "DiffusionEq.h"

class CrankNicolson_LAPACK : DiffusionEq {
public:
  CrankNicolson_LAPACK(double _D, int _NX, double _L, int _NT, double _TEND);
  void timeStepEvolution() override;

private:

  vd B;
  vd Bpsi;

  void makeB(vd& B);

};
