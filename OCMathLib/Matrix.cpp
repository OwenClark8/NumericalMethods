#include "Matrix.hpp"
#include "Vector.hpp"




namespace OCMathLib
{
Matrix::Matrix(const Matrix& otherMatrix)
{
   mNumRows = otherMatrix.mNumRows;
   mNumCols = otherMatrix.mNumCols;
   mData = new double* [mNumRows];
   for (int i=0; i<mNumRows; i++)
   {
      mData[i] = new double [mNumCols];
   }
   for (int i=0; i<mNumRows; i++)
   {
      for (int j=0; j<mNumCols; j++)
      {
         mData[i][j] = otherMatrix.mData[i][j];
      }
   }
}

// Constructor for vector of a given length
// Allocates memory, and initialises entries
// to zero
Matrix::Matrix(int numRows, int numCols)
{
   assert(numRows > 0);
   assert(numCols > 0);
   mNumRows = numRows;
   mNumCols = numCols;
   mData = new double* [mNumRows];
   for (int i=0; i<mNumRows; i++)
   {
      mData[i] = new double [mNumCols];
   }
   for (int i=0; i<mNumRows; i++)
   {
      for (int j=0; j<mNumCols; j++)
      {
         mData[i][j] = 0.0;
      }
   }
}

Matrix::Matrix(int numRows,int numCols,std::string type)
{
    assert(numRows > 0);
    assert(numCols > 0);
    mNumRows = numRows;
    mNumCols = numCols;
    mData = new double* [mNumRows];
    for (int i=0; i<mNumRows; i++)
    {
      mData[i] = new double [mNumCols];
    }
    if (type=="Identity")
    {
        for (int i=0; i<mNumRows; i++)
        {
            for (int j=0; j<mNumCols; j++)
            {
                if (i==j)
                {
                    mData[i][j]=1.0;
                }
                else
                {
                    mData[i][j]=0.0;
                }
            }
        }

    }
    else if (type=="Ones")
    {
        for (int i=0; i<mNumRows; i++)
        {
            for (int j=0; j<mNumCols; j++)
            {
                mData[i][j] = 1.0;
            }
        }
    }
    else if (type=="TriDiagonal")
    {
        for (int i=0; i<mNumRows; i++)
        {
            for (int j=0; j<mNumCols; j++)
            {
                if (i==j||i==j-1||i==j+1)
                {
                    mData[i][j]=1.0;
                }
                else
                {
                    mData[i][j]=0.0;
                }
            }
        }

    }
    else
    {
        std::cout<<"Invalid type setting up standard matrix";
        for (int i=0; i<mNumRows; i++)
        {
            for (int j=0; j<mNumCols; j++)
            {
                mData[i][j] = 0.0;
            }
        }

    }
}

// Overwritten destructor to correctly free memory
Matrix::~Matrix()
{
   for (int i=0; i<mNumRows; i++)
   {
      delete[] mData[i];
   }
   delete[] mData;
}

// Method to get number of rows of matrix
int Matrix::GetNumberOfRows() const
{
   return mNumRows;
}

// Method to get number of columns of matrix
int Matrix::GetNumberOfColumns() const
{
   return mNumCols;
}


const double& Matrix::operator()(const int i,const int j) const
{
    assert(i >= 0);
    assert(i < mNumRows);
    assert(j >= 0);
    assert(j < mNumCols);
    return mData[i][j];
}

    // Overloading the round brackets
// and a check on the validity of the index
double& Matrix::operator()(int i, int j)
{
    return
        const_cast<double&>
                (static_cast<const Matrix&>(*this)(i,j));

}

// Overloading the assignment operator
Matrix& Matrix::operator=(const Matrix& otherMatrix)
{
   assert(mNumRows = otherMatrix.mNumRows);
   assert(mNumCols = otherMatrix.mNumCols);

   for (int i=0; i<mNumRows; i++)
   {
      for (int j=0; j<mNumCols; j++)
      {
         mData[i][j] = otherMatrix.mData[i][j];
      }
   }
   return *this;
}

// Overloading the unary + operator
const Matrix Matrix::operator+() const
{
   Matrix mat(mNumRows, mNumCols);
   for (int i=0; i<mNumRows; i++)
   {
      for (int j=0; j<mNumCols; j++)
      {
         mat(i,j) = mData[i][j];
      }
   }
   return mat;
}

// Overloading the unary - operator
Matrix Matrix::operator-() const
{
   Matrix mat(mNumRows, mNumCols);
   for (int i=0; i<mNumRows; i++)
   {
      for (int j=0; j<mNumCols; j++)
      {
         mat(i,j) = -mData[i][j];
      }
   }
   return mat;
}

// Overloading the binary + operator
Matrix Matrix::operator+(const Matrix& m1) const
{
   assert(mNumRows == m1.mNumRows);
   assert(mNumCols == m1.mNumCols);
   Matrix mat(mNumRows, mNumCols);
   for (int i=0; i<mNumRows; i++)
   {
      for (int j=0; j<mNumCols; j++)
      {
         mat(i,j) = mData[i][j] + m1.mData[i][j];
      }
   }
   return mat;
}

// Overloading the binary - operator
Matrix Matrix::operator-(const Matrix& m1) const
{
   assert(mNumRows == m1.mNumRows);
   assert(mNumCols == m1.mNumCols);
   Matrix mat(mNumRows, mNumCols);
   for (int i=0; i<mNumRows; i++)
   {
      for (int j=0; j<mNumCols; j++)
      {
         mat(i,j) = mData[i][j] - m1.mData[i][j];
      }
   }
   return mat;
}

// Overloading scalar multiplication
Matrix Matrix::operator*(double a) const
{
   Matrix mat(mNumRows, mNumCols);
   for (int i=0; i<mNumRows; i++)
   {
      for (int j=0; j<mNumCols; j++)
      {
         mat(i,j) = a*mData[i][j];
      }
   }
   return mat;
}

Matrix Matrix::operator*(const Matrix& m1) const
{
    assert(mNumCols==m1.GetNumberOfRows());
    Matrix mat(mNumRows,m1.GetNumberOfColumns());

    for (int i=0;i<mNumRows;i++)
    {
        for (int j=0;j<m1.GetNumberOfColumns();j++)
        {
            double sum=0;
            for (int k=0;k<mNumCols;k++)
            {
                sum+=mData[i][k]*m1(k,j);
            }
            mat(i,j)=sum;
        }
    }
    return mat;
}

// Overloading matrix multiplied by a vector
Vector operator*(const Matrix& m, const Vector& v)
{
   int original_vector_size = v.GetSize();
   assert(m.GetNumberOfColumns() == original_vector_size);
   int new_vector_length = m.GetNumberOfRows();
   Vector new_vector(new_vector_length);

   for (int i=0; i<new_vector_length; i++)
   {
      for (int j=0; j<original_vector_size; j++)
      {
         new_vector[i] += m.mData[i][j]*v[j];
      }
   }

   return new_vector;
}

// Overloading vector multiplied by a matrix
Vector operator*(const Vector& v, const Matrix& m)
{
   int original_vector_size = v.GetSize();
   assert(m.GetNumberOfRows() == original_vector_size);
   int new_vector_length = m.GetNumberOfColumns();
   Vector new_vector(new_vector_length);

   for (int i=0; i<new_vector_length; i++)
   {
      for (int j=0; j<original_vector_size; j++)
      {
         new_vector[i] += v[j]*m.mData[j][i];
      }
   }

   return new_vector;
}

// Calculate determinant of square matrix recursively
double Matrix::CalculateDeterminant() const
{
   assert(mNumRows == mNumCols);
   double determinant = 0.0;

   if (mNumRows == 1)
   {
      determinant = mData[0][0];
   }
   else
   {
      // More than one entry of matrix
      for (int i_outer=0; i_outer<mNumRows; i_outer++)
      {
         Matrix sub_matrix(mNumRows-1,
                             mNumRows-1);
         for (int i=0; i<mNumRows-1; i++)
         {
            for (int j=0; j<i_outer; j++)
            {
               sub_matrix(i,j) = mData[i+1][j];
            }
            for (int j=i_outer; j<mNumRows-1; j++)
            {
               sub_matrix(i,j) = mData[i+1][j+1];
            }
         }
         double sub_matrix_determinant =
                  sub_matrix.CalculateDeterminant();

         determinant += pow(-1.0, i_outer)*
                  mData[0][i_outer]*sub_matrix_determinant;
      }
   }
   return determinant;
}


std::ostream& operator<<(std::ostream& output,
                         const Matrix& A)
{

  // Local copy as Matrix does not have a "Read" method
  Matrix* p_A = new Matrix(A);

  for (int i=1; i<=p_A->GetNumberOfRows(); i++)
  {
    for (int j=1; j<=p_A->GetNumberOfColumns(); j++)
    {
      output << std::setw(14)
             << std::setprecision(5)
             << std::scientific
             << (*p_A)(i,j);
    }
    output << std::endl;
  }
  output << std::endl;

  return output;

}

void PrintMatrix(Matrix& m)
{
    int a=m.GetNumberOfRows();
    int b=m.GetNumberOfColumns();
    for (int i=0;i<a;i++)
    {
        std::cout<<"|";
        for (int j=0;j<b;j++)
        {
            std::cout<<std::setprecision(5)<<std::setw(15)<<(m)(i,j)<<std::setw(15);
        }
        std::cout<<"|"<<std::endl;

    }
}
}
