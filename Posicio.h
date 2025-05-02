#pragma once

#include <ostream>
#include <string>

using namespace std;

class Posicio
{
  public:
    Posicio() : m_x(0), m_y(0)
    {
    }

    int getX() const
    {
        return m_x;
    }

    Posicio operator*(int s) const
    {
        Posicio t = *this;
        t.m_x *= s;
        t.m_y *= s;
        return t;
    }

    Posicio operator+(const Posicio &p) const
    {
        Posicio t = *this;
        t.m_x += p.m_x;
        t.m_y += p.m_y;
        return t;
    }

    bool operator==(const Posicio &o) const
    {
        return o.m_y == m_y && o.m_x == m_x;
    }

    friend std::ostream &operator<<(std::ostream &out, const Posicio &p)
    {
        return out << char(p.m_x + 'a') << char(p.m_y + '1');
    }

    Posicio(int x, int y) : m_x(x), m_y(y)
    {
    }

    Posicio(const string &posicio)
    {
        m_y = posicio[1] - '1';
        m_x = posicio[0] - 'a';
    }

    bool operator!=(const Posicio &other) const
    {
        return !(*this == other);
    }

    int getY() const
    {
        return m_y;
    }

  private:
    int m_x;
    int m_y;
};
