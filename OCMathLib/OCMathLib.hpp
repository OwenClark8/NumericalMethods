#ifndef OMATH
#define OMATH

#include "Matrix.hpp"
#include "Vector.hpp"


template<typename T>
struct Type2Type
{
    typedef T OrigionalType;
};

template<int v>
struct Int2Type
{
    enum {value=v};
};

template<typename Vec>
double pNorm(const Vec& V,int n)
{
    double out;
    for(int i=0;i<V.GetSize();i++)
    {
        out+=pow(V[i],n);
    }
    return pow(out,1.0/double(n));
}

class CSRMatrix
{

};


#endif // OMATH
