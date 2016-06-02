#include "FFTW.h"

// public:

FFTW::FFTW(double _D, int _NX, double _L, int _NT, double _TEND) :
  DiffusionEq(_D, _NX, _L, _NT, _TEND)
{
  psi_in.resize(NX);
  psi_out.resize(NX);
  time_evolver.resize(NX);

  plan_initPsiTilde = fftw_plan_dft_1d(NX, fftwcast(psi_in), fftwcast(psi_in),  FFTW_FORWARD, FFTW_ESTIMATE);
  plan              = fftw_plan_dft_1d(NX, fftwcast(psi_in), fftwcast(psi_out), FFTW_BACKWARD, FFTW_MEASURE);

  initPsi_in(psi_in);
  psi_out = psi_in; // for outputting initial psi
  makeTimeEvolver(time_evolver);

  fftw_execute(plan_initPsiTilde); // make \tilde{psi}(k, 0)
}

FFTW::~FFTW(){
  fftw_destroy_plan(plan);
  fftw_destroy_plan(plan_initPsiTilde);
}

void FFTW::timeStepEvolution(){
  rep(i, NX) psi_in[i] *=time_evolver[i];
  fftw_execute(plan);
  cblas_zdscal(NX, 1.0 / NX, psi_out.data(), 1);
}

void FFTW::output(int ti) const {
  ostringstream os;
  os << "res/output" << ti << ".txt";
  ofstream ofs(os.str());
  ofs << "### x \t f(x, t)" << endl;
  rep(i, NX) ofs << i2x(i) << "\t" << psi_out[i].real() << endl;
}

// private:

inline fftw_complex* FFTW::fftwcast(vC& f){ return reinterpret_cast<fftw_complex*>(f.data()); }

double FFTW::m2k(int m) const { return 2 * M_PI * (m < NX / 2 ? m : m - NX) / L; }

void FFTW::initPsi_in(vC& psi_in){
  rep(i, NX) psi_in[i].real(psi[i]);
}

void FFTW::makeTimeEvolver(vd& te){
  rep(m, NX) te[m] = exp(-D * m2k(m) * m2k(m) * DT);
}

