#include "SecondOrderPDE2d.hpp"


SecondOrderPDE2d::SecondOrderPDE2d(const double CoeUxx,const double CoeUx,
                                   const double CoeUyy,const double CoeUy,
                                   const double CoeU,ComputeRHS rhs)
               :mCoeUxx(CoeUxx),mCoeUyy(CoeUyy),mCoeUx(CoeUx),
               mCoeUy(CoeUy),mCoeU(CoeU),
               mComputeRHS(rhs),mx(0),mExact(false)
{
}

SecondOrderPDE2d::SecondOrderPDE2d(const double CoeUxx,const double CoeUx,
                                const double CoeUyy,const double CoeUy,
                                const double CoeU,ComputeRHS rhs, ComputeTrueSol uexact)
               :mCoeUxx(CoeUxx),mCoeUyy(CoeUyy),mCoeUx(CoeUx),
               mCoeUy(CoeUy),mCoeU(CoeU),
               mComputeRHS(rhs),mTrueSol(uexact),mx(0),mExact(true)
{
}

SecondOrderPDE2d::SecondOrderPDE2d(const SecondOrderPDE2d& otherpde):
                mCoeUxx(otherpde.mCoeUxx),mCoeUx(otherpde.mCoeUx),
                mCoeUyy(otherpde.mCoeUyy),mCoeUy(otherpde.mCoeUy),
                mCoeU(otherpde.mCoeU),mx(0),mComputeRHS(otherpde.mComputeRHS),
                mTrueSol(otherpde.mTrueSol),mExact(otherpde.mExact)
{
}

void SecondOrderPDE2d::SetFInputs(const double x,const double y)
{
    mx=x;
    my=y;
}

void SecondOrderPDE2d::ComputeF(Vector& f) const
{
    assert(f.GetSize()==1);
    double x=mComputeRHS(mx,my);
    f[0]=x;
}

void SecondOrderPDE2d::ComputeAnalyticSolution(Vector& u) const
{
    assert(mExact==true);
    double x=mTrueSol(mx,my);
    u[0]=x;
}

double SecondOrderPDE2d::GetUxx() const
{
    return mCoeUxx;
}

double SecondOrderPDE2d::GetUyy() const
{
    return mCoeUyy;
}

double SecondOrderPDE2d::GetUx() const
{
    return mCoeUx;
}

double SecondOrderPDE2d::GetUy() const
{
    return mCoeUy;
}

double SecondOrderPDE2d::GetU() const
{
    return mCoeU;
}

bool SecondOrderPDE2d::ExactSolDefined() const
{
    return mExact;
}

void SecondOrderPDE2d::PrintHeader(const std::string PDEtype) const
{
    std::cout << "------------------------------------------------"
            << std::endl
            << to_string(mCoeUxx)+"Uxx + "+to_string(mCoeUx)+"Ux + "
            <<to_string(mCoeU)+"U = f, for in (0,1)"
            << std::endl;
}
