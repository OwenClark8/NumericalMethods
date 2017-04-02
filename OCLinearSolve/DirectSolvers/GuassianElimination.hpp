#ifndef GUASSIANELIMINATIONHEADERDEF
#define GUASSIANELIMINATIONHEADERDEF

#include "OCMathLib.hpp"
#include "LinearSystem.hpp"

using namespace OCMathLib;

class GuassianElimination
{

private:
    const LinearSystem* mpLinearSystem;


public:
    GuassianElimination(const LinearSystem* linearsyst);

    ~GuassianElimination();

    void Solve(Vector& u);
};
#endif // GUASSIANELIMINATIONHEADERDEF
