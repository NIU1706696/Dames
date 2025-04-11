#include "posicio.h"
#include <iostream>

using namespace std;

Posicio::Posicio() {
    fila = 0;
    columna = 0;
}

Posicio::Posicio(const char* posicio) {
    columna = posicio[0] - 'a';
    fila = 8 - (posicio[1] - '0');
}

int Posicio::getFila() const {
    return fila;
}

int Posicio::getColumna() const {
    return columna;
}

bool Posicio::operator==(const Posicio& altre) const {
    return fila == altre.fila && columna == altre.columna;
}