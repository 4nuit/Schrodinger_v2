#include "../headers/basis.h"
#include "../headers/algorithms.h"
#include "../headers/constantes.h"
#include <iostream>
#include <armadillo>

arma::mat naive(arma::mat rho, Basis basis, arma::vec zVals, arma::vec rVals)
{
  arma::mat result = arma::zeros(rVals.size(), zVals.size()); // number of points on r- and z- axes

  //Il faut incrémenter a et b à la fin de la dernière boucle qui change funcA et funcB respectivement
  int a=0;
  int b=0;
  for (int m = 0; m < basis.mMax; m++)
  {
    for (int n = 0; n < basis.nMax(m); n++)
    {
      for (int n_z = 0; n_z < basis.n_zMax(m, n); n_z++)
      {
        b=0;
        for (int mp = 0; mp < basis.mMax; mp++)
        {
          for (int np = 0; np < basis.nMax(mp); np++)
          {
            for (int n_zp = 0; n_zp < basis.n_zMax(mp, np); n_zp++)
            {
              arma::mat funcA = basis.basisFunc( m,  n,  n_z, zVals, rVals);
              arma::mat funcB = basis.basisFunc(mp, np, n_zp, zVals, rVals);
              result += rho(a, b) * funcA % funcB; // mat += mat % mat * double
              b++;
            }
          }
        }
        a++;
      }
    }
  }
  return result;
}

arma::mat algo_opti(arma::mat rho, Basis basis, arma::vec zVals, arma::vec rVals)
{
  // matrice resultat
  arma::mat result = arma::zeros(rVals.size(), zVals.size());

  // precalcul de Z
  arma::vec * Z = new arma::vec[basis.n_zMax(0, 0)];
  for (int n_z = 0; n_z < basis.n_zMax(0, 0); n_z++) {
      Z[n_z] = basis.zPart(zVals, n_z);
  }

  // precalcul de R*Z
  int i = 0;
  arma::mat * RZ = new arma::mat[basis.mMax * basis.nMax(0) * basis.n_zMax(0, 0)];
  for (int m = 0 ; m < basis.mMax ; m++) {
      for (int n = 0 ; n < basis.nMax(m) ; n++) {
          arma::mat R = basis.rPart(rVals, m, n);
          for (int n_z = 0; n_z < basis.n_zMax(m, n); n_z++) {
              RZ[i] = R * Z[n_z].t();
              i++;
          }
      }
  }

  // calcul de la sommme
  int a = 0;
  int b_init = 0;
  for (int m = 0; m < basis.mMax; m++) {
      for (int na = 0; na < basis.nMax(m); na++) {
          for (int n_za = 0; n_za < basis.n_zMax(m, na); n_za++) {
              // on utilise la symetrie
              for (int b = b_init ; b < a ; b++) {
                  result += rho(a, b) * RZ[a] % RZ[b] * 2.0;
              }
              result += rho(a, a) * RZ[a] % RZ[a];
              a++;
          }
      }
      b_init = a;
  }

  return result;
}