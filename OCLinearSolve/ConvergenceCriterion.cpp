#include"ConvergenceCriterion.hpp"

// Constructor
ConvergenceCriterion::
ConvergenceCriterion(const double tolerance)
                    :mTolerance(tolerance)
{
}

// True if || r || < tolerance
bool ConvergenceCriterion::
TestConvergence(double residualNorm) const
{
  return residualNorm <= mTolerance;
}
