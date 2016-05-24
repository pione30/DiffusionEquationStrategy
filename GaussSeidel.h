#pragma once
#include "utilities.h"

// A is a symmetric tridiagonal matrix.
// b will be overwritten by the result.
void GaussSeidel_st(const vd& A, vd &b);
