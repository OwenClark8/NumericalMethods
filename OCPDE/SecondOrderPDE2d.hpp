#ifndef SecondOrderPDE2DHEADERDEF
#define SecondOrderPDE2DHEADERDEF

#include "PDEInterface.hpp"
#include <tr1/functional>
#include <functional>

class SecondOrderPDE2d : public PDEInterface
{
public:
    typedef std::function<double(double,double)> ComputeRHS;
    typedef std::function<double(double,double)> ComputeTrueSol;
private:
    double mCoeUxx;

    double mCoeUyy;

    double mCoeUx;

    double mCoeUy;

    double mCoeU;

    ComputeRHS mComputeRHS;

    ComputeTrueSol mTrueSol;

    double mx;

    double my;

    const bool mExact;

    SecondOrderPDE2d& operator=(const SecondOrderPDE2d&);

public:
    SecondOrderPDE2d(const double CoeUxx,const double CoeUx,
                     const double CoeUyy,const double CoeUy,
                     const double CoeU,ComputeRHS rhs);

    SecondOrderPDE2d(const double CoeUxx,const double CoeUx,
                     const double CoeUyy,const double CoeUy,
                     const double CoeU,ComputeRHS rhs,ComputeTrueSol uexact);

    SecondOrderPDE2d(const SecondOrderPDE2d& otherpde);

    ~SecondOrderPDE2d(){};


    void SetFInputs(const double x,const double y);

    void ComputeF(Vector& f) const;

    void ComputeAnalyticSolution(Vector& u) const;

    double GetUxx() const;

    double GetUyy() const;

    double GetUx() const;

    double GetUy() const;

    double GetU() const;

    bool ExactSolDefined() const;

    void PrintHeader(const std::string PDEType) const;


};

#endif // ELLIPTICPDEHEADERDEF
