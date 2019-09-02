#ifndef VECTOR_H
#define VECTOR_H


#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <QElapsedTimer>
#include <inttypes.h>
#include <cmath>
#include <ctime>
#include <iostream>
#include <string.h>
#include <stdlib.h>

namespace simulation
{
    class vector
    {
    public:
        double r, phi, v, w;

        vector() : r(0), phi(0), v(0), w(0) {}
        vector(double ar, double aphi, double av, double aw) : r(ar), phi(aphi), v(av), w(aw) {}
        vector(const vector& a) : r(a.r), phi(a.phi), v(a.v), w(a.w) {} //конструктор копирования

        vector operator +(const vector& b) const;
        vector operator -(const vector& b) const;
        vector operator *(const double a) const;
    };
}

#endif // VECTOR_H
