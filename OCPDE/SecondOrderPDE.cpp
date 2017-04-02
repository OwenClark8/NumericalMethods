#include "SecondOrderPDE.hpp"


SecondOrderPDE::SecondOrderPDE(const double CoeUxx,const double CoeUx,const double CoeU,
               ComputeRHS rhs)
               :mCoeUxx(CoeUxx),mCoeUx(CoeUx),mCoeU(CoeU),
               mComputeRHS(rhs),mExact(false)
{
}

SecondOrderPDE::SecondOrderPDE(const double CoeUxx,const double CoeUx,const double CoeU,
               ComputeRHS rhs, ComputeTrueSol uexact, ComputeTruederSol du)
               :mCoeUxx(CoeUxx),mCoeUx(CoeUx),mCoeU(CoeU),
               mComputeRHS(rhs),mTrueSol(uexact),mTruederSol(du), mExact(true)
{
}

SecondOrderPDE::SecondOrderPDE(const SecondOrderPDE& otherpde):
                mCoeUxx(otherpde.mCoeUxx),mCoeUx(otherpde.mCoeUx),
                mCoeU(otherpde.mCoeU),mComputeRHS(otherpde.mComputeRHS),
                mTrueSol(otherpde.mTrueSol),mExact(otherpde.mExact)
{
}


double SecondOrderPDE::ComputeF(const double f) const
{
    double x=mComputeRHS(f);
    return x;
}

double SecondOrderPDE::ComputeAnalyticSolution(const double u) const
{
    assert(mExact==true);
    double x=mTrueSol(u);
    return x;
}

double SecondOrderPDE::ComputederAnalyticSolution(const double u) const
{
    assert(mExact==true);
    double x=mTruederSol(u);
    return x;
}

double SecondOrderPDE::GetUxx() const
{
    return mCoeUxx;
}

double SecondOrderPDE::GetUx() const
{
    return mCoeUx;
}

double SecondOrderPDE::GetU() const
{
    return mCoeU;
}

bool SecondOrderPDE::ExactSolDefined() const
{
    return mExact;
}

void SecondOrderPDE::PrintHeader(const std::string PDEtype) const
{
    std::cout << "------------------------------------------------"
            << std::endl
            << to_string(mCoeUxx)+"Uxx + "+to_string(mCoeUx)+"Ux + "
            <<to_string(mCoeU)+"U = f, for in (0,1)"
            << std::endl;
}
