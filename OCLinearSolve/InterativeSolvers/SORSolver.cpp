#include <iostream>
#include <cassert>
#include "SORSolver.hpp"

// Specialised constructor
SORSolver::
SORSolver(
    const LinearSystem* pLinearSystem,
    const Vector* pInitialGuess,
    const double omega,
    const int maxIterations,
    const double tolerance,
    const bool saveData)
{

  // Initialising protected variables
  // inherited from AbstractIterativeLinearSolver
  mMaxIterations = maxIterations;
  mTolerance = tolerance;

  // Initialising private variables
  mpInitialGuess = pInitialGuess;
  mpLinearSystem = pLinearSystem;
  mpConvergenceCriterion = new ConvergenceCriterion(mTolerance);
  mSaveData = saveData;

   // Damping factor
  assert(omega > 0);
  assert(omega < 2);
  mOmega = omega;

}

// Destructor
SORSolver::~SORSolver()
{
  delete mpConvergenceCriterion;
}

// Solution method
void SORSolver::Solve(Vector* px)
{

  // Check size
  assert( px->GetSize() == mpInitialGuess->GetSize() );

  // Print header (inherited protected method from abstract class)
  PrintHeader();

  // Assign variables to improve readability
  Matrix rA = *(mpLinearSystem->GetMatrix());
  Vector rb = *(mpLinearSystem->GetRightHandSide());
  int size = rA.GetNumberOfRows();

  // Temporary vector
  Vector y(size);

  // Iterator
  int k = 0;

  // Initialise solution to initial guess
  (*px) = (*mpInitialGuess);

  // Compute residual
  Vector* p_residual = new Vector( mpLinearSystem->GetRightHandSide()->GetSize() );
  mpLinearSystem->CalculateResidual(px,p_residual);

  // Residual norm
  double residual_norm;
  residual_norm = p_residual->CalculateNorm(2);

  // Print and eventually save first iteration
  PrintIteration(k,residual_norm,true);
  if (mSaveData)
  {
    SaveIteration(k,px);
  }

  // Convergence test
  bool converged = mpConvergenceCriterion->TestConvergence(residual_norm);

  // Start iterations
  while ( (k < mMaxIterations) && !converged )
  {

    for (int i=1; i<=size; i++)
    {

       double y = 0.0;
       for (int j=1; j<=i-1; j++)
       {
            y += rA(i,j) * (*px)(j);
       }
       for (int j=i+1; j<=size; j++)
       {
            y += rA(i,j) * (*px)(j);
       }
       y =  ( rb(i) - y )/rA(i,i);
       (*px)(i) += mOmega*( y - (*px)(i) );

    }

    // Update iterator
    k++;

    // Update residual and residual norm
    mpLinearSystem->CalculateResidual(px,p_residual);
    residual_norm = p_residual->CalculateNorm(2);

    // Check convergence
    converged = mpConvergenceCriterion->TestConvergence(residual_norm);

    // Print and eventually save current iteration
    PrintIteration(k,residual_norm);
    if (mSaveData)
    {
      SaveIteration(k,px);
    }


  }

  // Print final message
  PrintFooter(k,converged);

  // Clean
  delete p_residual;

}

// Overriden initial infos to display omega values
void SORSolver::PrintHeader() const
{
  std::cout << "------------------------------------------------"
            << std::endl
            << " Attempt to solve Ax = b using damped Jacobi method"
            << std::endl
	    << " damping factor omega = " << mOmega
            << std::endl
	    << " max number of iterations = " << mMaxIterations
            << std::endl
	    << " tolerance = " << mTolerance
            << std::endl
            << "------------------------------------------------"
            << std::endl;
}

