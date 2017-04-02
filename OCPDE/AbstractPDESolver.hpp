#ifndef ABSTRACTPDESOLVERHEADERDEF
#define ABSTRACTPDESOLVERHEADERDEF

#include "PDEInterface.hpp"
#include "../FiniteDiffernce/GridFunction.hpp"
#include <fstream>
#include <cassert>
#include <string>
#include <math.h>
#include <sstream>
#include <vector>

class AbstractPDESolver
{
    protected:
        GridFunction<2>* mpxGrid;

        std::string mOutputFileName;

    public:
        virtual ~AbstractPDESolver();
        //Pure virtual method to solve our ODE and return an approximation u_h(t).
        virtual void Solve()=0;

        virtual void SaveToFile(const Vector& solution) const;

        virtual void PrintHeader(std::string MethodName) const;

        void ChangeOutFileName(const std::string filename);

        std::string GetOutFileName() const;

        void ChangeStepSize(const double h);
};



void inputtofile(std::ofstream& inputfile, std::string filename);





#endif // ABSTRACTODESOLVERHEADERDEF

