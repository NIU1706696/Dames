#pragma once
#include "Moviment.h"
#include "Posicio.h"
#include <sstream>
#include <vector>

using namespace std;

enum Tipus
{
    TIPUS_BUIT,
    TIPUS_NORMAL,
    TIPUS_DAMA
};
enum Color
{
    COLOR_BLANC,
    COLOR_NEGRE
};

class Tauler;
class Fitxa
{
  public:
    Fitxa() : m_color(COLOR_BLANC), m_tipo(TIPUS_BUIT)
    {
    }
    Fitxa(Color color, Tipus type) : m_color(color), m_tipo(type)
    {
    }
    Fitxa(char type);
    void visualitza(int x, int y) const;
    Color getCol() const
    {
        return m_color;
    }
    Tipus getTipo() const
    {
        return m_tipo;
    }
    void upgrade(Posicio pos);
    vector<Moviment> &getMoviments(Posicio pos, Tauler *tauler);
    friend stringstream &operator<<(stringstream &out, const Fitxa &f);

  private:
    Color m_color;
    Tipus m_tipo;
    vector<Moviment> m_moviments;

  private:
    void trobaKillsDama(vector<Posicio> &kills, vector<Posicio> &posicions, Posicio nodeActual,
                        const Moviment &currentPath, Tauler *t) const;
    void trobaKillsNormal(vector<Posicio> &kills, vector<Posicio> &posicions, Posicio nodeActual,
                          const Moviment &currentPath, Tauler *t) const;
    void trobaKills(Posicio nodeActual, vector<Posicio> &kills, vector<Posicio> &posicions, const Moviment &currentPath,
                    Tauler *tauler) const;
    void trobaSaltsDama(vector<Posicio> &salts, Posicio nodeActual, Tauler *tauler) const;
    void trobaSaltsNormal(vector<Posicio> &salts, Posicio nodeActual, Tauler *tauler) const;
    vector<Posicio> trobaSalts(Posicio nodeActual, Tauler *tauler) const;
};
