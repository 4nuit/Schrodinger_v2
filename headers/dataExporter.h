#include <armadillo>
#include <iostream>
#include <fstream>

#ifndef EXPORTER
#define EXPORTER
/**
 * @brief Exporte les résultats d'une fonction sous forme d'un fichier .csv dans ./target (Pour les visualiser sur matplotlib par exemple)
 *
 * @param X tableau des abscisses non nul
 * @param Y tableau des ordonnées, doit avoir le même nombre de lignes que X
 * @param nom Le nom du fichier.
 */
void exportToCsv(arma::vec X, arma::mat Y, char* nom);

/**
 * @brief Exporte la matrice au format Df3
 * 
 * @param m la matrice à exporter
 * @return Le résultat de l'exportation de la matrice
 */
std::string exportToDf3(const arma::cube &m);
/**
 * @brief Exporte la matrice au format Raw
 * 
 * @param m la matrice à exporter
 * @return std::string  le résultat de l'exportation
 */
std::string cubeToRaw(const arma::cube &m);

#endif