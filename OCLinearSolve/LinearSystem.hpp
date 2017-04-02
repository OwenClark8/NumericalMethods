#ifndef LINEARSYSTEMDEF
#define LINEARSYSTEMDEF

//----------------------------------------------------------------------------------------
//
// This class models a linear system Ax=b where A is a matrix and x and b vectors
//
//----------------------------------------------------------------------------------------


#include "C:\Users\Owen\Documents\PhDC++\OCMathLib\OCMathLib.hpp"
#include <memory>

using namespace OCMathLib;

template<typename M,typename V>
class LinearSystem
{
using pMatrix = std::unique_ptr<M>;
using pVector = std::unique_ptr<V>;

private:
    pMatrix mpLHS;
    pVector mpRHS;

public:
    //Specialised constructors
    LinearSystem(const M& amatrix,const V& avector);

    LinearSystem(const M&& amatrix,const V&& avector);

    //Copy constructors
    LinearSystem(const LinearSystem& otherlinearsolver);

    LinearSystem(const LinearSystem&& otherlinearsolver);

    //Destructor
    ~LinearSystem();

    //Accessors
    M GetMatrix() const;
    V GetVector() const;

    //Method to calculate the residual of the system and vector x
    //r is our output vector
    void CalculateResidual(const V& x, V& r) const;

    //Print Linear system information to output stream
    void PrintHeader() const;

    //Hide copy assigner
    LinearSystem& operator=(const LinearSystem&) = delete;

    LinearSystem& operator=(const LinearSystem&&) = delete;

};





template<typename M, typename V>
LinearSystem<M,V>::LinearSystem(const M& amatrix,const V& avector):
    mpLHS(new M(amatrix)),mpRHS(new V(avector))
{
}

template<typename M, typename V>
LinearSystem<M,V>::LinearSystem(const M&& amatrix,const V&& avector):
    mpLHS(std::move(amatrix)),mpRHS(std::move(avector))
{
}

template<typename M,typename V>
LinearSystem<M,V>::LinearSystem(const LinearSystem& otherlinearsystem):
    mpLHS(new M(*otherlinearsystem.mpLHS)),mpRHS(new V(*otherlinearsystem.mpRHS))
{
}

template<typename M,typename V>
LinearSystem<M,V>::LinearSystem(const LinearSystem&& otherlinearsystem):
    mpLHS((std::move(otherlinearsystem.mpLHS))),mpRHS(std::move(otherlinearsystem.mpRHS))
{
}

template<typename M,typename V>
LinearSystem<M,V>::~LinearSystem<M,V>()
{
}

template<typename M,typename V>
M LinearSystem<M,V>::GetMatrix() const
{
    return *mpLHS;
}

template<typename M,typename V>
V LinearSystem<M,V>::GetVector() const
{
    return *mpRHS;
}

template<typename M,typename V>
void LinearSystem<M,V>::CalculateResidual(const V& x, V& r) const
{
    assert(x.GetSize()==r.GetSize());
    assert (mpLHS->GetNumberOfRows()==x.GetSize());
    (r)=(*mpRHS)-((*mpLHS)*(x));
}


template<typename M,typename V>
void LinearSystem<M,V>::PrintHeader() const
{
      std::cout << "------------------------------------------------"
            << std::endl
            << " The system Ax=B is defined as follows"
            << std::endl
            <<"A="
            <<std::endl;
    PrintMatrix(*mpLHS);
    std::cout<<"B="
            <<std::endl;
    PrintVector(*mpRHS);
    std::cout<<"------------------------------------------------"
            << std::endl;
}




#endif
