# Specification #
> Perform all the elementary operations with matrices: sum, subtraction, product, multiplication element by element. It also perform the pade approximation to the exponential matrix.

> It also should wrap Lapack more advanced functions: inverse, eigenvalues and eigenvectors.

  * _(Planned) Singular value decomposition, QR decomposition, Cholesky decomposition._
  * _(Planned) Optimization for  symmetric, diagonal and triangular matrices (following Lapack classification)_
  * _(Planned) Fast Fourier Transform._
  * _(Planned) Sparse Matrices_


# Design #
> template class **`M_Matrix`** is just a pointer wrap.


# Implementation #
> in Markov\_LA\_template.h
