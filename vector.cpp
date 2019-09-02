#include "vector.h"

namespace simulation 
{
    vector vector::operator +(const vector& b) const	{
        vector c(r + b.r, phi + b.phi, v + b.v, w + b.w);
        return(c);
    }
    vector vector::operator -(const vector& b) const{
        vector c(r - b.r, phi - b.phi, v - b.v, w - b.w);
        return(c);
    }
    vector vector::operator *(const double a) const{
        vector c(a * r, a * phi, a * v, a * w);
        return(c);
    }

    vector operator *(double a, const vector& b){
        vector c(a * b.r, a * b.phi, a * b.v, a * b.w);
        return(c);
    }
}
