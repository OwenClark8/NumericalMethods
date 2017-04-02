#ifndef PDEINTERFACEHEADERDEF
#define PDEINTERFACEHEADERDEF
#include "../OCMathLib/OCMathLib.hpp"
#include <fstream>
#include <cassert>
#include <string>
#include <math.h>
#include <sstream>
#include <vector>
using namespace OCMathLib;
// Interface class for PDE problems of the type
//  du/dt = f(t,u)
//  where t is a real number
//  u is a vector of state variables

class PDEInterface
{
private:


  public:
    // Compute right-hand side (pure virtual)
    virtual void ComputeF(Vector &f) const=0;

    // Compute analytical solution
    virtual void ComputeAnalyticSolution(Vector& u) const;

    virtual void PrintHeader(const std::string PDEType) const;

    virtual ~PDEInterface(){};


};

std::string to_string(int i);

#endif
