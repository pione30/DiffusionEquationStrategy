#pragma once
#include "utilities.h"

namespace handmade{
  // A is a symmetric tridiagonal matrix.
  // b will be overwritten by the result.
  void GaussSeidel_st(const vd& A, vd& b);
}
