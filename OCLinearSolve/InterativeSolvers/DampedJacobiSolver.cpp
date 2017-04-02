#include <iostream>
#include <cassert>
#include "DampedJacobiSolver.hpp"

// Specialised constructor
DampedJacobiSolver::
DampedJacobiSolver( 
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
DampedJacobiSolver::~DampedJacobiSolver()
{
  delete mpConvergenceCriterion;
}

// Solution method
void DampedJacobiSolver::Solve(Vector* px)
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
       y(i) = 0.0;
       for (int j=1; j<=size; j++)
       {
	 if (i!=j)
	 {
	   y(i) += rA(i,j) * (*px)(j);
	 }

       }
       y(i) = ( rb(i) - y(i) )/rA(i,i);
    }

    // Update solution
    *px = y * mOmega +   (*px) * (1-mOmega);
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
void DampedJacobiSolver::PrintHeader() const
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

