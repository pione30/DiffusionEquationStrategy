#include "DiffusionEq.h"
#include "GSL.h"
#include "CrankNicolson_GaussSeidel.h"
#include "CrankNicolson_LAPACK.h"
#include "FFTW.h"
using namespace chrono;

namespace context {
  constexpr double D = 1;      // diffusion coefficient
  constexpr int NXINI = 10;    // initial division number of the system
  constexpr int NXMAX = 1000;  // maximum division number of the system
  constexpr int NXINC = 10;    // increment for the division number of the system
  constexpr double L = 50;     // system size
  constexpr int NT = 10000;    // divison number of time
  constexpr double TEND = 10;  // the end of time

  template<class T>
  void solveDiffusionEq(){
    ostringstream os;
    os << "res/exectime_.txt";
    ofstream ofs(os.str());
    ofs << "### NX \t time[ms]" << endl;
    
    for(int NX = NXINI; NX <= NXMAX; NX += NXINC){
      cout << "NX = " << NX << endl;

      // diffusion equation strategy
      auto des = make_unique<T>(D, NX, L, NT, TEND);

      auto start = system_clock::now();
      rep(t, NT + 1){
        // cout << "t = " << t << endl;
        // des->output(t);
        if(t == NT) break;
        des->timeStepEvolution();
      }
      auto end = system_clock::now();

      ofs << NX << "\t" << duration_cast<milliseconds>(end - start).count() << endl;
    }
  }
}


int main(){
  context::solveDiffusionEq<CrankNicolson_LAPACK>();
  return 0;
}
