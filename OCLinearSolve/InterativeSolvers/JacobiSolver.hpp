
#ifndef JACOBISOLVERHEADERDEF
#define JACOBISOLVERHEADERDEF

#include"LinearSystem.hpp"
#include"AbstractIterativeLinearSolver.hpp"
#include"ConvergenceCriterion.hpp"

class JacobiSolver:
  public AbstractIterativeLinearSolver
{

  public:

    //Specialised constructor
    JacobiSolver(
	const LinearSystem& pLinearSystem,
	const Vector& pInitialGuess,
	const double tolerance,
	const int maxIterations,
	const bool saveData = false);

    // Destructor
    ~JacobiSolver();

    // Solution method - overriding abstract class  pure virtual method
    void Solve(Vector& px);

  private:

    // Hiding default constructor
    JacobiSolver();

    //Hiding copy assigner
    JacobiSolver& operator=(const JacobiSolver&);

    // Initial guess
    const Vector* mpInitialGuess;

    // Linear system
    const LinearSystem* mpLinearSystem;

    // Convergence criterion
    ConvergenceCriterion* mpConvergenceCriterion;

    // Determines whether to save data on files
    bool mSaveData;

};

#endif
