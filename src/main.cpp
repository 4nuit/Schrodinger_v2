#include <iostream>
#include <armadillo>
#include "../headers/dataExporter.h"
#include "../headers/poly.h"
#include "../headers/basis.h"
#include "../headers/algorithms.h"

#define MINVALUE -10
#define MAXVALUE 10
#define STEPS 64

int main()
{
    Basis basis(1.935801664793151,      2.829683956491218,     14,     1.3);
    arma::mat rho;
    rho.load("rho.arma", arma::arma_ascii);
    std::cout<<"Calcul en cours...\n";
    arma::vec zVals=arma::linspace(MINVALUE*2, MAXVALUE*2, STEPS*2);
    arma::vec rVals=arma::linspace(MINVALUE, MAXVALUE, STEPS);

    arma::wall_clock timer;
    timer.tic();
    arma::mat res_0=naive(rho, basis, zVals, rVals);
    std::cout<<"Algorithme naif : "<<timer.toc()<<"s\n";
    timer.tic();
    arma::mat res_1=algo_opti(rho, basis, zVals, rVals);
    std::cout<<"Algorithme opti : "<<timer.toc()<<"s\n";

    arma::vec X = arma::linspace(MINVALUE, MAXVALUE, STEPS);
    arma::vec Y = arma::linspace(MINVALUE, MAXVALUE, STEPS);
    arma::vec Z = arma::linspace(MINVALUE*2, MAXVALUE*2, STEPS*2);

    arma::cube cube=arma::zeros(X.size(), Y.size(), Z.size());
    /** Exportation en 3D
     * Il faut passer des coordonnées cartésiennes à cylindriques
     * On a R=sqrt(x²+y²), puis il faudrait chercher le r le plus proche d'un x pour x,y donné
     * 
     * Z reste le même
     */
    for (unsigned int i = 0 ; i < X.size() ; i++) {
        for (unsigned int j = 0 ; j < Y.size() ; j++) {
            double x = X(i);
            double y = Y(j);
            double r = sqrt(x * x + y * y);
            unsigned int u = 0;

            //On va chercher l'indice du r le PLUS PROCHE de r calculé
            for (unsigned int v = 1 ; v < rVals.size() ; v++) {
                if (abs(r - rVals(v)) < abs(r - rVals(u))) {
                    u = v;
                }
            }

            for (unsigned int k = 0 ; k < Z.size() ; k++) {
                //En fait c'est des plans=tranches qu'on va mettre en perspective 3d
                cube(i, j, k) = res_1(u, k);
            }
        }
    }

    std::ofstream file;
    file.open("res/df3/res.df3");
    file << exportToDf3(cube);
    file.close();

    std::ofstream file2;
    file2.open ("res/raw/res.raw");
    file2 << cubeToRaw(cube);
    file2.close();

    /**
     * Exportation en 2D
     * 
     */
    std::ofstream file3;
    file3.open("res/res.mat");
    file3 << res_1;
    file3.close();

    std::cout << "Fichiers exportés dans ./res\n";

    return 0;
}
