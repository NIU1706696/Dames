#include "tauler.hpp"
#include "Fitxa.h"
#include "Posicio.h"

#include <fstream>

using namespace std;

void Tauler::actualitzaMovimentsValids()
{
    m_nMorts = 0;
    for (int i = 0; i < N_FILES; i++)
    {
        for (int j = 0; j < N_COLUMNES; j++)
        {
            Posicio p(j, i);
            if (getFitxa(p)->getCol() == COLOR_BLANC && getFitxa(p)->getTipo() != TIPUS_BUIT)
            {
                auto &movs = getFitxa(p)->getMoviments(p, this);
                for (int k = 0; k < movs.size(); k++)
                {
                    if (m_nMorts < movs[k].getKills().size())
                    {
                        m_nMorts = movs[k].getKills().size();
                        m_topMortsPos = p;
                    }
                }
            }
        }
    }
}

void Tauler::getPosicionsPossibles(Posicio origen, int &nPosicions, Posicio posicionsPossibles[])
{
    nPosicions = 0;
    const vector<Moviment> &ms = getFitxa(origen)->getMoviments(origen, this);
    for (int i = 0; i < ms.size(); i++)
    {
        const vector<Posicio> &ps = ms[i].getSalts();
        for (int j = 0; j < ps.size(); j++)
        {
            posicionsPossibles[nPosicions] = ps[j];
            nPosicions += 1;
        }
    }
}

void Tauler::set(Posicio pos, const Fitxa &fitxa)
{
    m_tauler[pos.getY()][pos.getX()] = fitxa;
}

const Moviment *Tauler::cercaExisteixCami(Posicio a, Posicio b)
{
    const vector<Moviment> &camins = getFitxa(a)->getMoviments(a, this);
    int i = 0;
    bool trobat = false;
    while (i < camins.size() && !trobat)
    {
        if (camins[i].visita(b))
        {
            trobat = true;
        }
        else
        {
            i++;
        }
    }
    if (trobat)
    {
        return &camins[i];
    }
    else
    {
        return nullptr;
    }
}

bool Tauler::mouFitxa(Posicio a, Posicio b)
{
    const Moviment *cami = cercaExisteixCami(a, b);
    if (cami != nullptr)
    {
        // Actualitza el màxim número de fitxes que es poden matar
        // i els moviments de les fitxes.
        actualitzaMovimentsValids();
        // Elimina les fitxes que s'han de matar.
        int nMata = 0;
        if (!cami->getKills().empty())
        {
            const auto &salts = cami->getSalts();
            const auto &kills = cami->getKills();
            auto itSalts = salts.begin();
            auto itKills = kills.begin();
            // Troba índex del desti dins del cami.
            int pathLength = 0;
            while (*itSalts != b)
            {
                pathLength += 1;
                itSalts++;
                itKills++;
            }
            nMata = pathLength + 1;
            for (int i = 0; i <= pathLength; i++)
            {
                // Eliminar peçes que matem.
                del(kills[i]);
            }
        }
        // Moure la fitxa (fent una còpia) i fes-la dama si cal.
        Fitxa novaFitxa = *getFitxa(a);
        novaFitxa.upgrade(b);
        set(b, novaFitxa);
        // Bufa una fitxa si cal.
        bufaFitxa(a, b, nMata);
        // Elimina la fitxa original.
        del(a);
    }
    return cami != nullptr;
}

void Tauler::bufaFitxa(Posicio fitxaQueMovem, Posicio dest, int nMata)
{
    if (m_nMorts != nMata)
    {
        del(m_topMortsPos);
        if (m_topMortsPos == fitxaQueMovem)
        {
            del(dest);
        }
    }
}

void Tauler::del(Posicio pos)
{
    m_tauler[pos.getY()][pos.getX()] = Fitxa();
}

void Tauler::inicialitza(const string &nomFitxer)
{
    char t;
    string p;
    ifstream in;

    in.open(nomFitxer);
    if (in.is_open())
    {
        while (in >> t >> p)
        {
            set(Posicio(p), Fitxa(t));
        }
    }
}

string Tauler::toString() const
{
    stringstream out;
    for (int i = N_FILES - 1; i >= 0; i--)
    {
        for (int j = 0; j < N_COLUMNES; j++)
        {
            out << m_tauler[i][j];
        }
        out << "\n";
    }
    return out.str();
}

Fitxa *Tauler::getFitxa(Posicio p)
{
    if (p.getY() < N_FILES && p.getX() < N_COLUMNES && p.getY() >= 0 && p.getX() >= 0)
    {
        return &m_tauler[p.getY()][p.getX()];
    }
    else
    {
        return nullptr;
    }
}
