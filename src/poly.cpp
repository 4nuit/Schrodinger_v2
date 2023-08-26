#include "../headers/poly.h"
#include "../headers/constantes.h"
#include <iostream>


Poly::Poly(){
    arma::mat mat(0,0,arma::fill::zeros);
    arma::cube cube(0,0,0,arma::fill::zeros);

    internHermiteMat = mat;
    internLaguerreMat = cube;
};


/**
 * @brief Calcule les résultats du polynome d'Hermite d'indice i=0 à un entier donné deg_max
 *  appliqué à un vecteur colonne Z, sous forme d'une matrice.
 *
 * @param deg_max Indice max des polynomes d'Hermites utilisés dans la matrice
 * @param Z Vecteur colonne contenant les points à appliquer aux polynomes d'Hermite
 * Calcule une matrice de la forme suivante : \f$Z=\begin{bmatrix} z_0 & ... & z_{q-1} \end{bmatrix}\f$
    \f[
    \begin{bmatrix}
    H_0(z_0) & .. & H_{n_{max}-1}(z_0) \\
    .. & .. & .. \\
    H_0(z_q) & .. & H_{n_{max}-1}(z_q)
    \end{bmatrix}
    \f]
 */
void Poly::calcHermite(int deg_max, const arma::vec &Z) {
    //deg_max car deg_max non inclus
    arma::mat res(Z.size(), deg_max, arma::fill::zeros);
    for(int i=0; i<deg_max; i++)
    {
        //1er cas i = 0; H_0(z)=1
        //2e cas i=1; H_1(z)=2z
        //3e cas i>1; H_i(z)=2z*H_(i-1)(z) - 2(i-1)*H_(i-2)(z)
        if(i==0)
            res.col(0)=arma::vec(arma::size(Z), arma::fill::value(1));
        else if(i==1)
            res.col(1)=2*Z;
        else
        {
            res.col(i)=2*(Z % res.col(i-1))-2*(i-1)*res.col(i-2);
        }
    }
    internHermiteMat = res;
}


/**
 * @brief Calcule les résultats du polynome généralisé de Laguerre d'indice i=0 à un entier donné deg_max
 *  appliqué à un vecteur colonne vec_eta, sous forme d'une matrice à 3 dimensions.
 * 
 * @param deg_max Indice max des polynomes d'Hermites utilisés dans la matrice
 * @param m_max Valeur maximals de m
 * @param vec_eta Vecteur colonne contenant les points à appliquer aux polynomes d'Hermite
 * 
 * Calcule un cube, dont chaque tranche (m fixé) à la forme suivante : 
 * \f$vec\_eta=\begin{bmatrix} \eta_0 & ... & \eta_{q-1} \end{bmatrix}\f$
    \f[
    \begin{bmatrix}
    L_0^m(\eta_0) & .. & L_{n_{max}-1}^m(\eta_0) \\
    .. & .. & .. \\
    L_0^m(\eta_q) & .. & L_{n_{max}-1}^m(\eta_q)
    \end{bmatrix}
    \f]
 */
void Poly::calcLaguerre(int m_max, int deg_max, const arma::vec &vec_eta) {
    //deg_max car deg_max non inclus
    arma::cube res(vec_eta.size(), deg_max, m_max, arma::fill::zeros);

    for(int m=0 ; m<m_max ; m++)
    {
        for(int n=0 ; n<deg_max ; n++)
        {
            if(n==0)
                res.slice(m).col(0) = arma::vec(arma::size(vec_eta),arma::fill::value(1));
            
            else if(n==1)
                res.slice(m).col(1) = 1+m-vec_eta ;
            else
            {
                res.slice(m).col(n) = ((m-1-vec_eta)/((double) n) + 2) % res.slice(m).col(n-1)
                                - ((m-1)/((double) n) + 1) * res.slice(m).col(n-2) ;

            }
             
        }
        
    }
    
    internLaguerreMat = res;
}


/**
 * @brief Renvoie le vecteur de valeurs du polynome d'Hermite de degré n
 * pour les valeurs de z qui ont été fournies dans calcHermite
 * 
 * @param n entier
 * @return const arma::vec
 */
const arma::vec Poly::hermite(int n){
    return internHermiteMat.col(n);
}


/**
 * @brief Renvoie le vecteur de valeurs du polynome de Laguerre avec les valeurs
 * m et n pour les valeurs de z qui ont été fournies dans calcLaguerre
 * 
 * @param m entier
 * @param n entier
 * @return const arma::vec 
 */
const arma::vec Poly::laguerre(int m, int n){
    return internLaguerreMat.slice(m).col(n);
}