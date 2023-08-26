#ifndef POLY_H
#define POLY_H

#include <armadillo>

class Poly
{
private:
    /**
     * @brief Matrice interne qui stocke le résultat de calcHermite
     * 
     */
    arma::mat internHermiteMat;

    /**
     * @brief Matrice interne qui stocke le résultat de calcLaguerre
     * 
     */
    arma::cube internLaguerreMat;

public:

    /**
     * @brief Construct a new Poly object
     * 
     */
    Poly();

    /**
     * @brief Calcule en interne les polynomes de Hermite, à utiliser avant hermite(int)
     *
     */
    void calcHermite(int, const arma::vec &);

    /**
     * @brief Calcule en interne les polynomes de Laguerre, à utiliser avant laguerre(int, int)
     *
     */
    void calcLaguerre(int, int, const arma::vec &);

    /**
     * @brief Retourne le résultat des polynomes de Hermite
     * pour l'indice donné, utilisez calcHermite avant
     * 
     * @return const arma::vec 
     */
    const arma::vec hermite(int);
    /**
     * @brief Retourne le résultat des polynomes de laguerre
     * pour les deux indices donnés, utilisez calcLaguerre avant
     * 
     * @return const arma::vec 
     */
    const arma::vec laguerre(int, int);
};

#endif