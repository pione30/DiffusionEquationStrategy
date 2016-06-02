#include "DiffusionEq.h"
#include "GSL.h"
#include "CrankNicolson_GaussSeidel.h"
#include "CrankNicolson_LAPACK.h"
#include "FFTW.h"
using namespace chrono;

int main(){
  double _D = 1;
  int _NX = 1000;
  double _L = 50;
  int _NT = 1000;
  double _TEND = 10;
  
  auto de = make_unique<CrankNicolson_GaussSeidel>(_D, _NX, _L, _NT, _TEND);
  
  auto start = system_clock::now();
  rep(t, _NT + 1){
    // cout << "t = " << t << endl;
    // de->output(t);
    if(t == _NT) break;
    de->timeStepEvolution();
  }
  auto end = system_clock::now();

  cout << duration_cast<milliseconds>(end - start).count() / 1.0e3 << "[s]" << endl;

  return 0;
}
