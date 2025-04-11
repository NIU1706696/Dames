#ifndef MOVIMENT_H
#define MOVIMENT_H
#include "posicio.h"

#define MAX_CAMI 12

class Moviment {
private:
    Posicio cami[MAX_CAMI];
    int nPassos;
    Posicio captures[MAX_CAMI];
    int nCaptures;

public:
    Moviment();

    void afegirPas(const Posicio& p);
    void afegirCaptura(const Posicio& p);

    const Posicio* getCami() const;
    int getNumPassos() const;

    const Posicio* getCaptures() const;
    int getNumCaptures() const;
};

#endif