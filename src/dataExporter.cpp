#include "../headers/dataExporter.h"
#include <iostream>
#include <fstream>
#include <armadillo>
/**
 * @brief Délimiteur de base des fichiers .csv
 *
 */
#define defaultDelimiter ';'
/**
 * @brief Exporte les résultats d'une fonction sous forme d'un fichier .csv dans ./target (Pour les visualiser sur matplotlib par exemple)
 *
 * @param X tableau des abscisses non nul
 * @param Y tableau des ordonnées, doit avoir le même nombre de lignes que X
 * @param nom Le nom du fichier.
 */
void exportToCsv(arma::vec X, arma::mat Y, char* nom)
{
    std::ofstream fichierExport;
    char filename[255]="target/";
    strcat(filename, nom);
    strcat(filename, ".csv");
    fichierExport.open(filename);
    int nb_col=Y.n_cols;
    //Ecrire les labels
    for(int j=-1; j<nb_col; j++)
    {
        char input[255]="";
        if(j==-1)
            sprintf(input, "X%i", j);
        else
            sprintf(input, "Y%i", j);
        fichierExport<<input;
        if(j<nb_col-1)
            fichierExport<<defaultDelimiter;
    }
    fichierExport<<"\n";
    int nb_lig=Y.n_rows;
    //Ecrire les données
    for(int i=0; i<nb_lig; i++)
    {
        for(int j=-1; j<nb_col; j++)
        {
            char input[255]="";
            if(j==-1)
                sprintf(input, "%f", X(i));
            else
                sprintf(input, "%f", Y(i, j));
            fichierExport<<input;
            if(j<nb_col-1)
                fichierExport<<defaultDelimiter;
        }
        fichierExport<<"\n";
    }
    fichierExport.close();
}

std::string exportToDf3(const arma::cube &m)
{
  std::stringstream ss(std::stringstream::out | std::stringstream::binary);
  int nx = m.n_rows;
  int ny = m.n_cols;
  int nz = m.n_slices;
  ss.put(nx >> 8); ss.put(nx & 0xff);
  ss.put(ny >> 8); ss.put(ny & 0xff);
  ss.put(nz >> 8); ss.put(nz & 0xff);
  double theMin = 0.0;
  double theMax = m.max();
  for (unsigned int k = 0; k < m.n_slices; k++)
  {
    for (unsigned int j = 0; j < m.n_cols; j++)
    {
      for (unsigned int i = 0; i < m.n_rows; i++)
      {
        int v = 255 * (fabs(m(i, j, k)) - theMin) / (theMax - theMin);
        ss.put(v);
      }
    }
  }
  return ss.str();
}

std::string cubeToRaw(const arma::cube &m)
{
  std::stringstream ss(std::stringstream::out | std::stringstream::binary);
  double theMin = 0.0;
  double theMax = m.max();
  for (unsigned int k = 0; k < m.n_slices; k++)
  {
    for (unsigned int j = 0; j < m.n_cols; j++)
    {
      for (unsigned int i = 0; i < m.n_rows; i++)
      {
        int v = 255 * (fabs(m(i, j, k)) - theMin) / (theMax - theMin);
        ss.put(v);
      }
    }
  }
  return ss.str();
}