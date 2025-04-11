#include "tauler.h"
#include "posicio.h"
#include "moviment.h"
#include "fitxa.h"
#include <stdio.h>
#include <string.h>
#include <iostream>

usin namespace std;

void Tauler::inicialitza(const char* nomFitxer) {
    for (int i = 0; i < N_FILES; ++i) {
        for (int j = 0; j < N_COLUMNES; ++j) {
            m_tauler[i][j] = Fitxa();
        }
    }

    FILE* f = fopen(nomFitxer, "r");
    if (f == 0) return;

    char tipus;
    char pos[3];
    while (fscanf(f, " %c %s", &tipus, pos) == 2) {
        Posicio p(pos);
        int fila = p.getFila();
        int col = p.getColumna();
        TipusFitxa t;
        ColorFitxa c;

        if (tipus == 'O') { t = TIPUS_NORMAL; c = COLOR_BLANC; }
        else if (tipus == 'X') { t = TIPUS_NORMAL; c = COLOR_NEGRE; }
        else if (tipus == 'D') { t = TIPUS_DAMA; c = COLOR_BLANC; }
        else if (tipus == 'R') { t = TIPUS_DAMA; c = COLOR_NEGRE; }
        else continue;

        m_tauler[fila][col] = Fitxa(t, c);
    }

    fclose(f);
} //A revisar

void Tauler::actualitzaMovimentsValids() {
    // A implementar 
}

bool Tauler::mouFitxa(const Posicio& origen, const Posicio& desti) {
    // A implementar 
    return false;
}

void Tauler::getPosicionsPossibles(const Posicio& origen, int& nPosicions, Posicio posicionsPossibles[]) {
    // A implementar 
    nPosicions = 0;
}

const char* Tauler::toString() const {
    // A implementar
    return "";
}
