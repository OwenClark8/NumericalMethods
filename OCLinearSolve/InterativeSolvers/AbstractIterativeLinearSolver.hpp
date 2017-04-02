#ifndef ABSTRACTITERATIVELINEARSOLVERHEADERDEF
#define ABSTRACTITERATIVELINEARSOLVERHEADERDEF

#include "../../OCMathLib/OCMathLib.hpp"
#include "../LinearSystem.hpp"
using namespace OCMathLib;

class AbstractIterativeLinearSolver
{

  public:

    AbstractIterativeLinearSolver(const int maxit, const double tol):
        mMaxIterations(maxit),mTolerance(tol)
    {
    };

    // Pure virtual method for solving Ax = b
    virtual void Solve(Vector& px) = 0;

    // Printing infos when iterations begin
    virtual void PrintHeader(const std::string solverName) const;

    // Printing infos when iterations terminate
    virtual void PrintFooter(const int k,
	const bool converged) const;

    // Print infos about current iterate
    virtual void PrintIteration(const int k,
	const double residualNorm,
	const bool initialise = false) const;

    // Save iteration to file
    virtual void SaveSolution(const Vector& p_solution,
	const int labelWidth=5) const;

	AbstractIterativeLinearSolver() = delete;


  protected:

    // Max number of iterations
    int mMaxIterations;

    // User-specified tolerance
    double mTolerance;

};

#endif

