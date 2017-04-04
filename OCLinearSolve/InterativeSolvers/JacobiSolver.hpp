
#ifndef JACOBISOLVERHEADERDEF
#define JACOBISOLVERHEADERDEF

#include"../LinearSystem.hpp"
#include"AbstractIterativeLinearSolver.hpp"
#include"../ConvergenceCriterion.hpp"

template<typename Mat,typename Vec>
class JacobiSolver:
  public AbstractIterativeLinearSolver
{

  public:

    //Specialised constructors
    JacobiSolver(
	const LinearSystem<Mat,Vec>& pLinearSystem,
	const Vector& pInitialGuess,
	const double tolerance,
	const int maxIterations,
	const bool saveData = false);

    JacobiSolver(
	const LinearSystem<Mat,Vec>&& pLinearSystem,
	const Vector&& pInitialGuess,
	const double tolerance,
	const int maxIterations,
	const bool saveData = false);

    // Destructor
    ~JacobiSolver();

    // Solution method - overriding abstract class  pure virtual method
    void Solve(Vec& px);

    //Delete unwanted default functions
    JacobiSolver() = delete;

    JacobiSolver& operator=(const JacobiSolver&) = delete;

    JacobiSolver& operator=(const JacobiSolver&&) = delete;

  private:

    // Initial guess
    std::unique_ptr<Vec> mpinitialguess;

    // Linear system
    const LinearSystem<Mat,Vec> mplinearsystem;

    // Convergence criterion
    std::unique_ptr<ConvergenceCriterion> mpconvergence;

    // Determines whether to save data on files
    bool mSaveData;


};

// Specialised constructor
template<typename Mat,typename Vec>
JacobiSolver<Mat,Vec>::
JacobiSolver(
    const LinearSystem<Mat,Vec>& pLinearSystem,
    const Vector& pInitialGuess,
    const double tolerance,
    const int maxIterations,
    const bool saveData):
        AbstractIterativeLinearSolver(maxIterations,tolerance),
    mplinearsystem(pLinearSystem),
    mpinitialguess(new Vec(pInitialGuess)),
    mpconvergence(new ConvergenceCriterion(tolerance)),
    mSaveData(saveData)
{
}

// Specialised constructor
template<typename Mat,typename Vec>
JacobiSolver<Mat,Vec>::
JacobiSolver(
    const LinearSystem<Mat,Vec>&& pLinearSystem,
    const Vector&& pInitialGuess,
    const double tolerance,
    const int maxIterations,
    const bool saveData):
            AbstractIterativeLinearSolver(maxIterations,tolerance),
    mplinearsystem(pLinearSystem),
    mpinitialguess(std::move(pInitialGuess)),
    mpconvergence(std::move(tolerance)),
    mSaveData(saveData)
{
}

// Destructor
template<typename Mat,typename Vec>
JacobiSolver<Mat,Vec>::~JacobiSolver()
{
}

// Solution method
template<typename Mat,typename Vec>
void JacobiSolver<Mat,Vec>::Solve(Vec& px)
{

  // Check size
  assert( px.GetSize() == mpinitialguess->GetSize() );

  // Print header (inherited protected method from abstract class)
  PrintHeader("Jacobi method");

  // Assign variables to improve readability
  Matrix rA((mplinearsystem.GetMatrix()));
  Vector rb((mplinearsystem.GetVector()));
  int size = rA.GetNumberOfRows();

  // Temporary vector
  Vector y(size);

  // Iterator
  int k = 0;

  // Initialise solution to initial guess
  (px) = (*mpinitialguess);

  // Compute residual
  Vec p_residual(size);
  mplinearsystem.CalculateResidual(px,p_residual);

  // Residual norm
  double residual_norm;
  residual_norm = pNorm(p_residual,2);

  // Print and eventually save first iteration
  //PrintIteration(k,residual_norm,true);


  // Convergence test
  bool converged = mpconvergence->TestConvergence(residual_norm);

  // Start iterations
  while ( (k < mMaxIterations) && !converged )
  {

    for (int i=0; i<size; i++)
    {

       y[i] = 0.0;
       for (int j=0; j<size; j++)
       {

            if (i!=j)
            {
                y[i] += rA(i,j) * (px)[j];

            }

        }
        y[i] = ( rb[i] - y[i] )/rA(i,i);
     }

    // Update solution
    px = y;
    k++;

    // Update residual and residual norm
    mplinearsystem.CalculateResidual(px,p_residual);
    residual_norm = pNorm(p_residual,2);

    // Check convergence
    converged = mpconvergence->TestConvergence(residual_norm);

    // Print and eventually save current iteration
    //PrintIteration(k,residual_norm);
    if (mSaveData)
    {
      SaveSolution(px);
    }

  }

  // Print final message
  PrintFooter(k,converged);

}

#endif
