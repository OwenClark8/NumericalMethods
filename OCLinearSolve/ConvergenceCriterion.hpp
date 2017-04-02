#ifndef CONVERGENCECRITERIONHEADERDEF
#define CONVERGENCECRITERIONHEADERDEF

class ConvergenceCriterion
{

  public:

    // Specialised Constructor
    ConvergenceCriterion(const double tolerance);

    // Method for checking convergence based on the residual norm
    bool TestConvergence(double residualNorm) const;

  private:

    // Hidden default constructor
    ConvergenceCriterion();

    // Tolerance
    double mTolerance;

    //Prevent automatic definition of operator =
    ConvergenceCriterion& operator=(const ConvergenceCriterion&);

};

#endif

