#include "DiffusionEq.h"
#include "GSL.h"
#include "CrankNicolson_GaussSeidel.h"
#include "CrankNicolson_LAPACK.h"
#include "FFTW.h"
using namespace chrono;

namespace context {
  constexpr double D = 1;          // diffusion coefficient
  constexpr int NXINI = (1 << 2);  // initial division number of the system
  constexpr int NXMAX = (1 << 15); // maximum division number of the system
  constexpr double L = 50;         // system size
  constexpr int NT = 10000;        // divison number of time
  constexpr double TEND = 10;      // the end of time

  template<class T>
  void solveDiffusionEq(){
    // diffusion equation strategy
    unique_ptr<T> des;
    string strategy_name = typeid(des.get()).name();

    ostringstream os;
    os << "res/exectime_" << strategy_name << ".txt";
    ofstream ofs(os.str());
    ofs << "### NX \t time[ms]" << endl;
    
    for(int NX = NXINI; NX <= NXMAX; NX <<= 1){
      cout << strategy_name << " NX = " << NX << endl;

      des = make_unique<T>(D, NX, L, NT, TEND);

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
  context::solveDiffusionEq<GSL>();
  context::solveDiffusionEq<CrankNicolson_GaussSeidel>();
  context::solveDiffusionEq<CrankNicolson_LAPACK>();
  context::solveDiffusionEq<FFTW>();
  return 0;
}
