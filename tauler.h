#ifndef TAULER_H
#define TAULER_H
#include "fitxa.h"

#define N_FILES 8
#define N_COLUMNES 8

class Tauler {
private:
    Fitxa m_tauler[N_FILES][N_COLUMNES];

public:
    void inicialitza(const char* nomFitxer);
    void actualitzaMovimentsValids();
    bool mouFitxa(const Posicio& origen, const Posicio& desti);
    void getPosicionsPossibles(const Posicio& origen, int& nPosicions, Posicio posicionsPossibles[]);
    string toString() const;
};

#endif
#pragma once
