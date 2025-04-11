#ifndef POSICIO_H
#define POSICIO_H

class Posicio {
private:
    int fila;
    int columna;

public:
    Posicio();
    Posicio(const char* posicio);

    int getFila() const;
    int getColumna() const;
    const char* toString() const;

    bool operator==(const Posicio& altre) const;
};
#pragma once
