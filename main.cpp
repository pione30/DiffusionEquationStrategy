#include "DiffusionEq.h"
#include "CrankNicolson_LAPACK.h"
using namespace chrono;

int main(){
  double _D = 1;
  int _NX = 1000;
  double _L = 50;
  int _NT = 1000;
  double _TEND = 10;
  
  auto de_cn = make_unique<CrankNicolson_LAPACK>(_D, _NX, _L, _NT, _TEND);
  
  auto start = system_clock::now();
  rep(t, _NT + 1){
    cout << "t = " << t << endl;
    de_cn->output(t);
    if(t == _NT) break;
    de_cn->timeStepEvolution();
  }
  auto end = system_clock::now();

  cout << duration_cast<milliseconds>(end - start).count() / 1.0e3 << "[s]" << endl;

  return 0;
}
