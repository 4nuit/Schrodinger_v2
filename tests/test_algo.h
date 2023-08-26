#include <cxxtest/TestSuite.h>
#include <armadillo>
#include "../headers/algorithms.h"
#include "../headers/basis.h"

class TestAlgoSuite : public CxxTest::TestSuite
{
public:
    void testSizeOfRho( void )
    {
        Basis basis(1.935801664793151, 2.829683956491218, 14, 1.3);
        int i = 0;
        for (int m = 0; m < basis.mMax; m++)
            for (int n = 0; n < basis.nMax(m); n++)
                for (int n_z = 0; n_z < basis.n_zMax(m, n); n_z++) 
                    i++;
        TS_ASSERT_EQUALS(i, 374); //Nombre de vecteurs dans Rho
    }

};
