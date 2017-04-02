#ifndef GAUSSSEIDELSOLVERHEADERDEF
#define GAUSSSEIDELSOLVERHEADERDEF

#include"LinearSystem.hpp"
#include"Vector.hpp"
#include"AbstractIterativeLinearSolver.hpp"
#include"ConvergenceCriterion.hpp"

class GaussSeidelSolver: 
  public AbstractIterativeLinearSolver
{

  public:

    //Specialised constructor
    GaussSeidelSolver( 
	const LinearSystem* pLinearSystem, 
	const Vector* pInitialGuess, 
	const int maxIterations, 
	const double tolerance,
	const bool saveData = false);

    // Destructor
    ~GaussSeidelSolver();

    // Solution method - overriding abstract class  pure virtual method
    void Solve(Vector* px);

  private:

    // Hiding default constructor
    GaussSeidelSolver();

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
