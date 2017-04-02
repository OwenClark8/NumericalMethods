#include <iostream>
#include <cassert>
#include "JacobiSolver.hpp"

// Specialised constructor
JacobiSolver::
JacobiSolver(
    const LinearSystem& pLinearSystem,
    const Vector& pInitialGuess,
    const double tolerance,
    const int maxIterations,
    const bool saveData)
{

  // Initialising protected variables
  // inherited from AbstractIterativeLinearSolver
  mMaxIterations = maxIterations;
  mTolerance = tolerance;

  // Initialising private variables
  mpInitialGuess = new Vector(pInitialGuess);
  mpLinearSystem =new  LinearSystem(pLinearSystem);
  mpConvergenceCriterion = new ConvergenceCriterion(mTolerance);
  mSaveData = saveData;

}

// Destructor
JacobiSolver::~JacobiSolver()
{
  delete mpConvergenceCriterion;
  delete mpLinearSystem;
  delete mpInitialGuess;
}

// Solution method
void JacobiSolver::Solve(Vector& px)
{

  // Check size
  assert( px.GetSize() == mpInitialGuess->GetSize() );

  // Print header (inherited protected method from abstract class)
  PrintHeader("Jacobi method");

  // Assign variables to improve readability
  Matrix rA = *(mpLinearSystem->GetMatrix());
  Vector rb = *(mpLinearSystem->GetVector());
  int size = rA.GetNumberOfRows();

  // Temporary vector
  Vector y(size);

  // Iterator
  int k = 0;

  // Initialise solution to initial guess
  (px) = (*mpInitialGuess);

  // Compute residual
  Vector* p_residual = new Vector( mpLinearSystem->GetVector()->GetSize() );
  mpLinearSystem->CalculateResidual(px,*p_residual);

  // Residual norm
  double residual_norm;
  residual_norm = p_residual->CalculateNorm(2);

  // Print and eventually save first iteration
  PrintIteration(k,residual_norm,true);


  // Convergence test
  bool converged = mpConvergenceCriterion->TestConvergence(residual_norm);

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
    mpLinearSystem->CalculateResidual(px,*p_residual);
    residual_norm = p_residual->CalculateNorm(2);

    // Check convergence
    converged = mpConvergenceCriterion->TestConvergence(residual_norm);

    PrintIteration(k,residual_norm);

  }

    //save current solution
    if (mSaveData)
    {
      SaveSolution(px);
    }

  // Print final message
  PrintFooter(k,converged);

  // Clean
  delete p_residual;

}
