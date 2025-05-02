#pragma once

#include "Fitxa.h"
#include "Posicio.h"
#include <string>

using namespace std;

const int N_FILES = 8;
const int N_COLUMNES = 8;

class Tauler
{
  public:
    Tauler() : m_nMorts(0), m_topMortsPos(-1, -1)
    {
    }
    string toString() const;
    void inicialitza(const string &nomFitxer);
    void getPosicionsPossibles(Posicio origen, int &nPosicions, Posicio posicionsPossibles[]);
    void actualitzaMovimentsValids();
    bool mouFitxa(Posicio a, Posicio b);

    Fitxa *getFitxa(Posicio p);
    void set(Posicio p, const Fitxa &f);
    void del(Posicio p);

  private:
    void bufaFitxa(Posicio fitxaQueMovem, Posicio dest, int nMata);
    const Moviment *cercaExisteixCami(Posicio a, Posicio b);

  private:
    Fitxa m_tauler[N_FILES][N_COLUMNES];
    int m_nMorts;
    Posicio m_topMortsPos;
};
