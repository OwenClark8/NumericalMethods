#include <cassert>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>


#include "AbstractIterativeLinearSolver.hpp"

// Printing infos when iterations begin
void AbstractIterativeLinearSolver::
PrintHeader(const std::string solverName) const
{
  std::cout << "------------------------------------------------"
            << std::endl
            << " Attempt to solve Ax = b using " + solverName
            << std::endl
	    << " max number of iterations = " << mMaxIterations
            << std::endl
	    << " tolerance = " << mTolerance
            << std::endl
            << "------------------------------------------------"
            << std::endl;
}

// Printing infos when iterations terminate
void AbstractIterativeLinearSolver::
PrintFooter(const int k, const bool converged) const
{

  if (converged)
  {
    std::cout << "------------------------------------------------"
	      << std::endl
              << "The method converged after "
              << k
	      << " iterations"
	      <<std::endl
	      << "------------------------------------------------"
	      << std::endl;
  }
  else
  {
    std::cout << "------------------------------------------------"
	      << std::endl
              << "The method did not converge after "
              << k
	      << " iterations"
	      <<std::endl
	      << "------------------------------------------------"
	      << std::endl;
  }

}

// Printing infos about current iteration
void AbstractIterativeLinearSolver::
PrintIteration(const int k, const double residualNorm,
    const bool initialise) const
{

  // At the first iterate, print the table header
  if (initialise)
  {
    std::cout << std::setw(10) << "Iteration"
              << std::setw(25) << "error estimate"
              << std::endl;
  }

  // Residual norm is printed with scientific notation
  std::cout << std::setw(10) << k

            << std::setprecision(6)
            << std::setw(25) << residualNorm
            << std::endl;

}

// Saving current iteration to file
void AbstractIterativeLinearSolver::
SaveSolution(const Vector& solution, const int labelWidth) const
{

  // Setting stream file precision
  std::ofstream output_file;
  output_file.setf(std::ios::scientific,std::ios::floatfield);
  output_file.precision(6);

  // Opening file
  std::ostringstream iterate_label;
  iterate_label.width(labelWidth);
  iterate_label.fill('0');
  //iterate_label << k;

  std::string file_name = "solution" + iterate_label.str() + ".dat";

  output_file.open(file_name);
  assert(output_file.is_open());

  // Write data
  for (int i=0; i<solution.GetSize(); i++)
  {
    output_file << std::setw(15) << solution[i] << std::endl;
  }

  // Close file
  output_file.close();

}
