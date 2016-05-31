#pragma once
#include <bits/stdc++.h>
extern "C" {
  #include <cblas.h>
  #include <lapacke.h>
  #include <gsl/gsl_errno.h>
  #include <gsl/gsl_odeiv2.h>
  #include <fftw3.h>
}
#define FOR(i, a, b) for(int (i) = (a); (i) <= (b); ++(i))
#define rep(i, n) FOR(i, 0, n - 1)
#define rep1(i, n) FOR(i, 1, n)
#define rrep(i, n) for(int (i) = (n) - 1; (i) >= 0; --(i))
#define rrep1(i, n) for(int (i) = (n); (i) >= 1; --(i))
#define all(a) (a).begin(),(a).end()
#define PB push_back
using namespace std;
using vi = vector<int>;
using vd = vector<double>;
using vvi = vector<vi>;
using vvd = vector<vd>;
