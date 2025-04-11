#include "fitxa.h"
#include <iostream>

using namespace std;

Fitxa::Fitxa() {
    tipus = TIPUS_EMPTY;
    color = COLOR_BLANC;
    nMoviments = 0;
}

Fitxa::Fitxa(TipusFitxa t, ColorFitxa c) {
    tipus = t;
    color = c;
    nMoviments = 0;
}

TipusFitxa Fitxa::getTipus() const {
    return tipus;
}

ColorFitxa Fitxa::getColor() const {
    return color;
}

void Fitxa::setTipus(TipusFitxa t) {
    tipus = t;
}

void Fitxa::setColor(ColorFitxa c) {
    color = c;
}

void Fitxa::convertirEnDama() {
    if (tipus == TIPUS_NORMAL) {
        tipus = TIPUS_DAMA;
    }
}

void Fitxa::setMovimentsValids(const Moviment movs[], int n) {
    nMoviments = n;
    for (int i = 0; i < n; ++i) {
        movimentsValids[i] = movs[i];
    }
}

const Moviment* Fitxa::getMovimentsValids() const {
    return movimentsValids;
}

int Fitxa::getNumMoviments() const {
    return nMoviments;
}
