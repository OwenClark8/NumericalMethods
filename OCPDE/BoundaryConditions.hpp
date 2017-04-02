#ifndef BOUNDARYCONDITIONSHEADERDEF
#define BOUNDARYCONDITIONSHEADERDEF

#include "PDEInterface.hpp"

class BoundaryConditions
{
protected:
    bool mDir;
    bool mNeu;
    double mValue;

public:
    BoundaryConditions();
    BoundaryConditions(const BoundaryConditions& otherbc);
    void Set(const bool IsDir,const double x);
    bool IsDir() const;
    double GetValue() const;
    void PrintHeader(const double val) const;

    BoundaryConditions& operator=(const BoundaryConditions&) = delete;
    BoundaryConditions& operator=(const BoundaryConditions&&) = delete;
    BoundaryConditions(const BoundaryConditions&& otherbc) = delete;

};

#endif // BOUNDARYCONDITIONSHEADERDEF
