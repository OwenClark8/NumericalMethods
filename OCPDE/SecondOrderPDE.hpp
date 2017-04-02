#ifndef SecondOrderPDEHEADERDEF
#define SecondOrderPDEHEADERDEF

//-----------------------------------------------------------------------------------------
//
//  This class models
//

#include "PDEInterface.hpp"
#include <tr1/functional>

class SecondOrderPDE
{
public:
    typedef std::tr1::function<double(double)> ComputeRHS;
    typedef std::tr1::function<double(double)> ComputeTrueSol;
    typedef std::tr1::function<double(double)> ComputeTruederSol;
private:
    double mCoeUxx;

    double mCoeUx;

    double mCoeU;

    ComputeRHS mComputeRHS;

    ComputeTrueSol mTrueSol;

    ComputeTruederSol mTruederSol;





    //Variable to show if class was constructed with the analytical
    //solution defined or not
    const bool mExact;

    //Hidden copy assigner
    SecondOrderPDE& operator=(const SecondOrderPDE&);

public:
    SecondOrderPDE(const double CoeUxx,const double CoeUx,const double CoeU,
                   ComputeRHS rhs);

    SecondOrderPDE(const double CoeUxx,const double CoeUx,const double CoeU,
                   ComputeRHS rhs,ComputeTrueSol uexact,ComputeTruederSol du);

    SecondOrderPDE(const SecondOrderPDE& otherpde);


    double ComputeF(const double f) const;

    double ComputeAnalyticSolution(const double u) const;

    double ComputederAnalyticSolution(const double u) const;

    double GetUxx() const;

    double GetUx() const;

    double GetU() const;

    bool ExactSolDefined() const;

    void PrintHeader(const std::string PDEType) const;


};

#endif // ELLIPTICPDEHEADERDEF
