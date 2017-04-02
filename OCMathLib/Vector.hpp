#ifndef VECTORHEADERDEF

#define VECTORHEADERDEF

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
    class Matrix;
    class Vector
    {
    private:

      // Data stored in vector
      double* mData;

      // Size of vector
      int mSize;

    public:

      // Copy constructor
      Vector(const Vector& otherVector);

      // Specialised constructor
      Vector(int size);

      // Destructor
      ~Vector();

      // Accessor
      int GetSize() const;

      // Zero-based indexing
      const double& operator[](int i) const;

      double& operator[](int i);

      // Read-only zero-based indexing
      //double Read(int i) const;

      // One-based indexing
      double& operator()(int i);

      // Assignment
      Vector& operator=(const Vector& otherVector);

      // Unary +
      Vector operator+() const;

      // Unary -
      Vector operator-() const;

      // Binary +
      Vector operator+(const Vector& v1) const;

      // Binary -
      Vector operator-(const Vector& v1) const;

      // Scalar multiplication
      Vector operator*(double a) const;

      // p-norm method
      double CalculateNorm(int p=2) const;

      // Scalar product with another vector
      double ScalarProduct(const Vector& v) const;

      double MaxElement() const;

      // Declare length function as a friend
      friend int length(const Vector& v);

      // Override << operator
      friend std::ostream& operator<<(std::ostream& output,
                           const Vector& v);


      friend void PrintVector(const Vector& PrintV);

      friend double Maxofvec(Vector& B);

      friend Matrix operator*(const Vector& v1,const Vector& v2);
    };

}
#endif // VECTORHEADERDEF
