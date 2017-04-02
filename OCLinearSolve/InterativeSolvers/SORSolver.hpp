#ifndef SORSOLVERHEADERDEF
#define SORSOLVERHEADERDEF

#include"LinearSystem.hpp"
#include"Vector.hpp"
#include"AbstractIterativeLinearSolver.hpp"
#include"ConvergenceCriterion.hpp"

class SORSolver: 
  public AbstractIterativeLinearSolver
{

  public:

    //Specialised constructor
    SORSolver( 
	const LinearSystem* pLinearSystem, 
	const Vector* pInitialGuess, 
	const double omega,
	const int maxIterations, 
	const double tolerance,
	const bool saveData = false);

    // Destructor
    ~SORSolver();

    // Solution method - overriding abstract class  pure virtual method
    void Solve(Vector* px);

  private:

    // Hiding default constructor
    SORSolver();

    // Print header is different from the one implemented in
    // AbstractIterative Solver, as we want to display omega
    void PrintHeader() const;

    // Initial guess
    const Vector* mpInitialGuess;

    // Linear system
    const LinearSystem* mpLinearSystem;

    // Convergence criterion
    ConvergenceCriterion* mpConvergenceCriterion;

    // Damping constant
    double mOmega;

    // Determines whether to save data on files
    bool mSaveData;

};

#endif
