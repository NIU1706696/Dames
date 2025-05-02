#pragma once
#include "Posicio.h"
#include <vector>
#include <algorithm>

using namespace std;

class Moviment
{
  private:
    vector<Posicio> m_salts;
    vector<Posicio> m_kills;
    Posicio m_inicial;

  public:
    Moviment(Posicio inicial) : m_inicial(inicial)
    {
    }
    void pushSalt(Posicio salt)
    {
        m_salts.push_back(salt);
    }
    void pushKill(Posicio salt, Posicio kill)
    {
        m_salts.push_back(salt);
        m_kills.push_back(kill);
    }
    const vector<Posicio> &getKills() const
    {
        return m_kills;
    }
    const vector<Posicio> &getSalts() const
    {
        return m_salts;
    }
    Posicio getLastPos() const
    {
        if (m_salts.empty())
        {
            return m_inicial;
        }
        return m_salts.back();
    }
    bool conte(Posicio kill) const
    {
        return std::find(m_kills.begin(), m_kills.end(), kill) != m_kills.end();
    }
    bool visita(Posicio salt) const
    {
        return std::find(m_salts.begin(), m_salts.end(), salt) != m_salts.end();
    }
};
