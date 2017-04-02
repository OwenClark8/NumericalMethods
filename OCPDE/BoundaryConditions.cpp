#include "BoundaryConditions.hpp"
#include <iostream>

BoundaryConditions::BoundaryConditions()
            :mDir(false),mNeu(false)
{
}

BoundaryConditions::BoundaryConditions(const BoundaryConditions& otherbc)
                    :mDir(otherbc.mDir),
                    mNeu(otherbc.mNeu),
                    mValue(otherbc.mValue)
{
}

void BoundaryConditions::Set(const bool IsDir,const double x)
{
    if (IsDir)
        mDir=true;
    else
        mNeu=true;

    mValue=x;
}

bool BoundaryConditions::IsDir() const
{
    return mDir;
}



double BoundaryConditions::GetValue() const
{
    return mValue;
}


void BoundaryConditions::PrintHeader(const double val) const
{

    if (mDir)
    {
        std::cout<<"u";
    }
    else
    {
        std::cout<<"u'";
    }
    std::cout<<"(" + to_string(val) + ") = " + to_string(mValue)
             << std::endl;

}
