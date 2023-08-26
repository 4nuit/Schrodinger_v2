#include "../headers/basis.h"
#include "../headers/poly.h"
#include "../headers/constantes.h"
#include <math.h>
#include <assert.h>

/**
 * @brief Fonction nu définie dans le sujet du projet.
 * 
 * @param N paramètre >=0
 * @param Q paramètre >=0
 * @param i argument en entrée de la fonction
 * @return double Résultat de nu(i)
 */
double nu(const int N, const double Q, const int i)
{
    return (N+2)*pow(Q, 2.0/3.0) + 1/2 - i * Q;
}

/**
 * @brief Retourne l'indice mMax pour la troncature de base.
 * 
 * @todo Vérifier que les arguments soient positifs ou nuls.
 * 
 * @return L'indice mMax pour la troncature de base
 */
int calcule_mMax(const int N, const double Q)
{
    //Vérifier que Q est bien positif ou nul
    assert (Q>=0);

    //Initialisation
    int res=1;
    double nu_i=nu(N, Q, 1);
    
    //On incrémente res tant que nu_i est supérieur/égal à 1
    for(int i=1; nu_i >= 1.0; i++)
    {
        nu_i=nu(N, Q, i);
        res=i;
    }
    return res;
};

/**
 * @brief Construct a new Basis:: Basis object
 * 
 * @param br paramètre de déformation de base
 * @param bz 2e paramètre de déformation de base
 * @param N paramètre de troncation de base
 * @param Q paramètre de troncation de base
 */
Basis::Basis(double br, double bz, int N, double Q) 
{
    /* Préparation de la troncature */
    //Calcul de mMax
    mMax=calcule_mMax(N, Q);
    //Calcul de nMax
    nMax.zeros(mMax);
    for(int m=0; m<mMax; m++)
    {
        nMax(m)=0.5 * (mMax - m - 1) + 1;
    }
    //Calcul de n_zMax
    //La taille de cette matrice est égale à mMax x (plus grand des nMax)
    n_zMax.zeros(mMax, nMax(0));
    for(int m=0; m<mMax; m++)
    {
        for(int n=0; n<nMax(m); n++)
        {
            n_zMax(m, n)=round(nu(N, Q, m + 2 * n + 1));
        }
    }

    b_r=br;
    b_z=bz;
};

arma::vec Basis::zPart(const arma::vec & zVals, int n_z)
{
    //Récupération de la matrice Hermite
    Poly poly;
    poly.calcHermite(n_z+1,zVals/b_z);

    int tailleZ = zVals.size();
    //On crée le vecteur resultat
    arma::vec res(tailleZ, arma::fill::zeros);

    //Calculs des Z
    double c = 1/( sqrt(sqrt(pi)*pow(2,n_z) ) * sqrt(b_z));

    //Factorielle 
    for (int i=1; i<=n_z; i++)
    {
        c=c/sqrt(i);
    }

    res= c * poly.hermite(n_z) % ( exp(-square(zVals)/(2*pow(b_z,2))));

    return res;
}

arma::vec Basis::rPart(const arma::vec & rVals, int m, int n)
{
    //Récupération de la matrice Hermite
    Poly poly;
    poly.calcLaguerre(abs(m)+1, n+1, pow( (rVals/b_r),2 ));

    int tailleR = rVals.size();
    //On crée le vecteur resultat
    arma::vec res(tailleR, arma::fill::zeros);

    double c = 1/ (b_r*sqrt(pi));

    //Factorielle
    for (int i=1; i<=n; i++)
    {
        c=c*sqrt(i);
    }
    for (int i=1; i<=n+abs(m); i++)
    {
        c=c/sqrt(i);
    }


    res = c * poly.laguerre(abs(m),n) % ( exp(-pow(rVals,2)/(2*pow(b_r,2))) % pow((rVals/b_r),abs(m)));
    

    return res;

}

arma::mat Basis::basisFunc(int m, int n, int n_z, const arma::vec &zVals, const arma::vec &rVals)
{
    //Récupération Z et R
    arma::vec zPart_vec = zPart(zVals, n_z);
    arma::vec rPart_vec = rPart(rVals, m, n);

    //Module (pas de theta) (?)
    return rPart_vec * zPart_vec.t();
}