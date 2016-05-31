#include "DiffusionEq.h"

// public:

void DiffusionEq::output(int ti) const {
  ostringstream os;
  os << "res/output" << ti << ".txt";
  ofstream ofs(os.str());
  ofs << "### x \t psi(x)" << endl;
  rep(i, NX) ofs << i2x(i) << "\t" << psi[i] << endl;
}

// protected:

DiffusionEq::DiffusionEq(double _D, int _NX, double _L, int _NT, double _TEND) :
  D(_D),
  NX(_NX), 
  L(_L),
  DX(L / (NX + 1)),
  NT(_NT),
  TEND(_TEND),
  DT(TEND / NT)
{
  psi.resize(NX);
  initPsi(psi);
}

double DiffusionEq::i2x(int i) const{
  return -L / 2 + (i + 1) * DX;
}

// private:

void DiffusionEq::initPsi(vd& psi){
  auto fx0 = [&](int i) {
    return pow(2 * M_PI * D, -0.5) * exp(-i2x(i) * i2x(i) / (2 * D));
  };
  rep(i, NX) psi[i] = fx0(i);
}
