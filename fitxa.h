#ifndef FITXA_H
#define FITXA_H
#include "moviment.h"

#define MAX_MOVS 20

typedef enum {
    TIPUS_NORMAL,
    TIPUS_DAMA,
    TIPUS_EMPTY
} TipusFitxa;

typedef enum {
    COLOR_NEGRE,
    COLOR_BLANC
} ColorFitxa;

class Fitxa {
private:
    TipusFitxa tipus;
    ColorFitxa color;
    Moviment movimentsValids[MAX_MOVS];
    int nMoviments;

public:
    Fitxa();
    Fitxa(TipusFitxa t, ColorFitxa c);

    TipusFitxa getTipus() const;
    ColorFitxa getColor() const;
    void setTipus(TipusFitxa t);
    void setColor(ColorFitxa c);
    void convertirEnDama();

    void setMovimentsValids(const Moviment movs[], int n);
    const Moviment* getMovimentsValids() const;
    int getNumMoviments() const;
};

#endif