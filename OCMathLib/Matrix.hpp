#ifndef MATRIXHEADERDEF
#define MATRIXHEADERDEF

#include <math.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include <cassert>
#include <iomanip>
#define M_PI=3.14

//----------------------------------------------------------
//
//  To do: Make move constructors and assignment//
//  transform into template class.
//
//----------------------------------------------------------





namespace OCMathLib
{
class Vector;
class Matrix
{
    private:

      // Entries of matrix
      double** mData;

      // Dimensions
      int mNumRows, mNumCols;

    public:

      // Copy constructor
      Matrix(const Matrix& otherMatrix);

      Matrix(Matrix&& otherMatrix);

      // Specialised Constructor
      Matrix(int numRows, int numCols);

      //Create matrix of type ones, Identity or TriDiagonal
      Matrix(int numRows,int numCols,std::string type);

      // Destructor
      ~Matrix();

      // Accessors
      int GetNumberOfRows() const;
      int GetNumberOfColumns() const;



      const double& operator()(const int i,const int j) const;

      // 0-based indexing
      double& operator()(const int i,const int j);

      //Overloaded assignment operator
      Matrix& operator=(const Matrix& otherMatrix);

      Matrix& operator=(Matrix&& otherMatrix);

      // Unary +
      const Matrix operator+() const;

      // Unary -
      Matrix operator-() const;

      // Binary +
      Matrix operator+(const Matrix& m1) const;

      // Binary -
      Matrix operator-(const Matrix& m1) const;

      // Scalar multiplication
      Matrix operator*(double a) const;

      //Matrix multiplication
      Matrix operator*(const Matrix& m1) const;

      // Determinant
      double CalculateDeterminant() const;

      // Declare vector multiplication friendship
      friend Vector operator*(const Matrix& m,
                              const Vector& v);
      friend Vector operator*(const Vector& v,
                              const Matrix& m);

      // Overridden << operator
      friend std::ostream& operator<<(std::ostream& output,
                            const Matrix& A);

      friend void PrintMatrix(Matrix& m);


};
}

#endif // MATRIXHEADERDEF
