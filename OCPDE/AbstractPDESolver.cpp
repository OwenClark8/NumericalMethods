#include "AbstractPDESolver.hpp"
#include <cassert>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
AbstractPDESolver::~AbstractPDESolver()
{
}

void AbstractPDESolver::PrintHeader(std::string MethodName) const
{
      std::cout << "----------------------------------------------------"
            << std::endl
            << " Attempt to solve PDE using the " + MethodName
            << std::endl
            << "----------------------------------------------------"
            << std::endl;
}

void AbstractPDESolver::SaveToFile(const Vector& solution) const
{
    // Setting stream file precision
  std::ofstream output_file;
  output_file.setf(std::ios::scientific,std::ios::floatfield);
  output_file.precision(6);

  // Opening file
  std::ostringstream iterate_label;
  iterate_label.width(5);
  iterate_label.fill('0');
  //iterate_label << k;

  std::string file_name = mOutputFileName+"_" + iterate_label.str() + ".dat";

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

void AbstractPDESolver::ChangeStepSize(const double h)
{

}

void AbstractPDESolver::ChangeOutFileName(const std::string filename)
{
    mOutputFileName=filename;
}

std::string AbstractPDESolver::GetOutFileName() const
{
    return mOutputFileName;
}



void inputtofile(std::ofstream& inputfile, std::string filename)
{
    inputfile.open(filename.c_str());
    inputfile.setf(std::ios::scientific,std::ios::floatfield);
    inputfile.precision(10);
    assert(inputfile.is_open());

}
