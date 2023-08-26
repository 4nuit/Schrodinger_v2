#include <armadillo>
#include "basis.h"

#ifndef ALGORITHMS
#define ALGORITHMS
/**
 * @brief Algorithme naïf pour calculer la matrice de densité locale.
 * Pour des valeurs de Z=\f$Z=\begin{bmatrix} z_0 & ... & z_{m-1} \end{bmatrix}\f$
 * et de R=\f$Z=\begin{bmatrix} r_0 & ... & r_{m-1} \end{bmatrix}\f$
 * 
 * 
 * 
 * @param rho 
 * @param basis
 * @param zVals 
 * @param rVals 
 * @return arma::mat 
 */
arma::mat naive(arma::mat rho, Basis basis, arma::vec zVals, arma::vec rVals);
/**
 * @brief Algorithme optimisé pour calculer la matrice de densité locale.
 * Pour des valeurs de Z=\f$Z=\begin{bmatrix} z_0 & ... & z_{m-1} \end{bmatrix}\f$
 * et de R=\f$Z=\begin{bmatrix} r_0 & ... & r_{m-1} \end{bmatrix}\f$
 * 
 * @param rho 
 * @param zVals 
 * @param rVals 
 * @return arma::mat 
 */
arma::mat algo_opti(arma::mat rho, Basis basis, arma::vec zVals, arma::vec rVals);

#endif