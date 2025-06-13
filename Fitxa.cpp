#include "Fitxa.h"
#include "Moviment.h"
#include "Posicio.h"
#include "Tauler.h"
#include "info_joc.hpp"

#include <ostream>
#include "GraphicManager.h"

using namespace std;

stringstream &operator<<(stringstream &out, const Fitxa &f)
{
    char c;
    if (f.m_tipo == TIPUS_NORMAL)
    {
        if (f.m_color == COLOR_BLANC)
            c = 'O';
        else
            c = 'X';
    }
    else if (f.m_tipo == TIPUS_DAMA)
    {
        if (f.m_color == COLOR_NEGRE)
            c = 'R';
        else
            c = 'D';
    }
    else if (f.m_tipo == TIPUS_BUIT)
    {
        c = '_';
    }
    else
    {
        c = '?';
    }
    out.put(c);
    return out;
}

int DIRECCIO_ENDEVANT(Color color)
{
    return color == COLOR_NEGRE ? 1 : -1;
}

const Posicio DIRECCIONS_DAMA[4] = {{1, 1}, {-1, 1}, {1, -1}, {-1, -1}};
void Fitxa::trobaKillsDama(vector<Posicio> &kills, vector<Posicio> &posicions, Posicio nodeActual,
                           const Moviment &currentPath, Tauler *tauler) const
{
    for (int i = 0; i < 4; i++)
    {
        int dist = 1;
        Posicio correctedDir(DIRECCIONS_DAMA[i].getX(), DIRECCIONS_DAMA[i].getY() * DIRECCIO_ENDEVANT(m_color));
        const Fitxa *victima;
        while ((victima = tauler->getFitxa(nodeActual + correctedDir * dist)) && victima->getTipo() == TIPUS_BUIT)
        {
            dist += 1;
        }

        Posicio ourPosicio(nodeActual + correctedDir * (dist + 1));
        Posicio victim(nodeActual + correctedDir * dist);
        if (victima && victima->getCol() != m_color && victima->getTipo() != TIPUS_BUIT)
        {
            Fitxa *moureA = tauler->getFitxa(ourPosicio);
            if (moureA && moureA->getTipo() == TIPUS_BUIT)
            {
                if (!currentPath.conte(victim))
                {
                    kills.push_back(victim);
                    posicions.push_back(ourPosicio);
                }
            }
        }
    }
}
const Posicio DIRECCIONS_NORMAL[2] = {{1, 1}, {-1, 1}};
void Fitxa::trobaKillsNormal(vector<Posicio> &kills, vector<Posicio> &posicions, Posicio nodeActual,
                             const Moviment &currentPath, Tauler *t) const
{
    for (int i = 0; i < 2; i++)
    {
        Posicio correctedDir(DIRECCIONS_NORMAL[i].getX(), DIRECCIONS_NORMAL[i].getY() * DIRECCIO_ENDEVANT(m_color));
        Posicio victim = nodeActual + correctedDir;
        Posicio destination = nodeActual + correctedDir * 2;
        Fitxa *v = t->getFitxa(victim);
        Fitxa *d = t->getFitxa(destination);

        if (v && v->getCol() != m_color && v->getTipo() != TIPUS_BUIT)
        {
            if (d && d->getTipo() == TIPUS_BUIT)
            {
                if (!currentPath.conte(victim))
                {
                    posicions.push_back(destination);
                    kills.push_back(victim);
                }
            }
        }
    }
}

void Fitxa::trobaKills(Posicio nodeActual, vector<Posicio> &kills, vector<Posicio> &posicions,
                       const Moviment &currentPath, Tauler *tauler) const
{
    switch (m_tipo)
    {
    case TIPUS_DAMA:
        trobaKillsDama(kills, posicions, nodeActual, currentPath, tauler);
        break;
    case TIPUS_NORMAL:
        trobaKillsNormal(kills, posicions, nodeActual, currentPath, tauler);
        break;
    case TIPUS_BUIT:
        break;
    }
}

void Fitxa::trobaSaltsDama(vector<Posicio> &salts, Posicio nodeActual, Tauler *tauler) const
{
    for (int i = 0; i < 4; i++)
    {
        Posicio correctedDir(DIRECCIONS_DAMA[i].getX(), DIRECCIONS_DAMA[i].getY() * DIRECCIO_ENDEVANT(m_color));
        int dist = 1;
        const Fitxa *f;
        // Mientras que la ficha este dentro del tablero y sea vacía exploramos la siguiente.
        while ((f = tauler->getFitxa(nodeActual + correctedDir * dist)) && f->getTipo() == TIPUS_BUIT)
        {
            salts.push_back(nodeActual + correctedDir * dist);
            dist += 1;
        }
    }
}

void Fitxa::trobaSaltsNormal(vector<Posicio> &salts, Posicio nodeActual, Tauler *tauler) const
{
    for (int i = 0; i < 2; i++)
    {
        Posicio correctedDir(DIRECCIONS_NORMAL[i].getX(), DIRECCIONS_NORMAL[i].getY() * DIRECCIO_ENDEVANT(m_color));
        Posicio destination(nodeActual + correctedDir);
        const Fitxa *f = tauler->getFitxa(destination);
        if (f && f->getTipo() == TIPUS_BUIT)
        {
            salts.push_back(destination);
        }
    }
}

vector<Posicio> Fitxa::trobaSalts(Posicio nodeActual, Tauler *tauler) const
{
    vector<Posicio> salts;
    switch (m_tipo)
    {
    case TIPUS_DAMA:
        trobaSaltsDama(salts, nodeActual, tauler);
        break;
    case TIPUS_NORMAL:
        trobaSaltsNormal(salts, nodeActual, tauler);
        break;
    case TIPUS_BUIT:
        break;
    }
    return salts;
}

vector<Moviment> &Fitxa::getMoviments(Posicio inici, Tauler *tauler)
{
    // Algoritme DFS
    vector<Moviment> pendents = {Moviment(inici)};
    m_moviments = {};
    // Troba cadenes de matar fitxes.
    while (!pendents.empty())
    {
        Moviment actual = pendents.back();
        pendents.pop_back();
        vector<Posicio> posicions;
        vector<Posicio> kills;
        trobaKills(actual.getLastPos(), kills, posicions, actual, tauler);
        if (kills.empty())
        {
            m_moviments.push_back(actual);
        }
        else
        {
            for (int i = 0; i < kills.size(); i++)
            {
                Moviment copy(actual);
                copy.pushKill(posicions[i], kills[i]);
                pendents.push_back(copy);
            }
        }
    }

    // Afegeix m_moviments simples.
    vector<Posicio> salts = trobaSalts(inici, tauler);
    for (int i = 0; i < salts.size(); i++)
    {
        Moviment base(inici);
        base.pushSalt(salts[i]);
        m_moviments.push_back(base);
    }
    return m_moviments;
}

void Fitxa::upgrade(Posicio pos)
{

    if (pos.getY() == N_FILES - 1 || pos.getY() == 0)
    {
        m_tipo = TIPUS_DAMA;
    }
}

Fitxa::Fitxa(char type)
{
    if (type == 'D')
    {
        m_tipo = TIPUS_DAMA;
        m_color = COLOR_BLANC;
    }
    else if (type == 'O')
    {
        m_tipo = TIPUS_NORMAL;
        m_color = COLOR_BLANC;
    }
    else if (type == 'R')
    {
        m_tipo = TIPUS_DAMA;
        m_color = COLOR_NEGRE;
    }
    else if (type == 'X')
    {
        m_tipo = TIPUS_NORMAL;
        m_color = COLOR_NEGRE;
    }
}

void Fitxa::visualitza(int x, int y) const {
    int posX = POS_X_TAULER + CASELLA_INICIAL_X + (x * AMPLADA_CASELLA);
    int posY = POS_Y_TAULER + CASELLA_INICIAL_Y + (y * ALCADA_CASELLA);
    if (m_color == COLOR_NEGRE)
    {
        if (m_tipo == TIPUS_NORMAL)
        {
            GraphicManager::getInstance()->drawSprite(GRAFIC_FITXA_NEGRA, posX, posY);
        }
        else if (m_tipo == TIPUS_DAMA)
        {
            GraphicManager::getInstance()->drawSprite(GRAFIC_DAMA_NEGRA, posX, posY);
        }
    }
    else if (m_color == COLOR_BLANC)
    {
        if (m_tipo == TIPUS_NORMAL)
        {
            GraphicManager::getInstance()->drawSprite(GRAFIC_FITXA_BLANCA, posX, posY);
        }
        else if (m_tipo == TIPUS_DAMA)
        {
            GraphicManager::getInstance()->drawSprite(GRAFIC_DAMA_BLANCA, posX, posY);
        }
    }
}
