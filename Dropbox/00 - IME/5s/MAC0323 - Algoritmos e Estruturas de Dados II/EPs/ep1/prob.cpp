#include "prob.hpp"
using namespace std;

// A função randomInteger devolve um inteiro
// aleatório entre low e high inclusive,
// ou seja, no intervalo fechado low..high.
// Vamos supor que low <= high e que
// high - low <= RAND_MAX. (O código foi copiado
// da biblioteca random de Eric Roberts.)
int randInteger(int a, int b) {
    double d = (double) rand() / ((double) RAND_MAX + 1);
    // 0 <= d < 1
    int k = d * (b - a + 1); // 0 <= k <= b-a
    return a + k;
}

// A função randProb() devolve uma probabilidade aleatória entre 0 e 1.
double randProb() {
   double r;
   r = rand() / ((double) RAND_MAX);
   return r;
}
