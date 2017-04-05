#include "Vector.hpp"
#include "Matrix.hpp"
#include <memory>


namespace OCMathLib
{
    // Overridden copy constructor
    // Allocates memory for new vector, and copies
    // entries of other vector into it
    Vector::Vector(const Vector& otherVector)
    {
        //std::cout<<"normalConst";
       mSize = otherVector.GetSize();
       mData = new double [mSize];
       for (int i=0; i<mSize; i++)
       {
          mData[i] = otherVector.mData[i];
       }
    }

    Vector::Vector(Vector&& otherVector):mData(nullptr)
    {
        mSize = otherVector.mSize;
        mData=otherVector.mData;
        otherVector.mData = nullptr;
        //std::cout<<"MoveConst";
    }

    // Constructor for vector of a given size
    // Allocates memory, and initialises entries
    // to zero
    Vector::Vector(int size)
    {
       assert(size > 0);
       mSize = size;
       mData = new double [mSize];
       for (int i=0; i<mSize; i++)
       {
          mData[i] = 0.0;
       }
    }

    // Overridden destructor to correctly free memory
    Vector::~Vector()
    {
       delete[] mData;
       //std::cout<<"destroy";
    }

    // Method to get the size of a vector
    int Vector::GetSize() const
    {
       return mSize;
    }
/*
    // Overloading square brackets
    // Note that this uses `zero-based' indexing,
    // and a check on the validity of the index
    double& Vector::operator[](int i)
    {
       assert(i > -1);
       assert(i < mSize);
       return mData[i];
    }

    // Read-only variant of []
    // Note that this uses `zero-based' indexing,
    // and a check on the validity of the index
    double Vector::Read(int i) const
    {
       assert(i > -1);
       assert(i < mSize);
       return mData[i];
    }
   */
    const double& Vector::operator[](const int i) const
    {
        assert(i >= 0);
        assert(i < mSize);
        return mData[i];
    }

        // Overloading the round brackets
    // and a check on the validity of the index
    double& Vector::operator[](int i)
    {
        return
            const_cast<double&>
                    (static_cast<const Vector&>(*this)[i]);

    }

    // Overloading round brackets
    // Note that this uses `one-based' indexing,
    // and a check on the validity of the index
    double& Vector::operator()(int i)
    {
       assert(i > 0);
       assert(i < mSize+1);
       return mData[i-1];
    }

    // Overloading the assignment operator
    Vector& Vector::operator=(const Vector& otherVector)
    {
       assert(mSize == otherVector.mSize);
       for (int i=0; i<mSize; i++)
       {
          mData[i] = otherVector.mData[i];
       }
       return *this;
    }

        // Overloading the assignment operator

    Vector& Vector::operator=(Vector&& otherVector)
    {
        //PrintVector(*this);
        delete[] mData;
        //mData=(otherVector.mData);
        assert(mSize == otherVector.mSize);
        //mData=nullptr;
        mData=otherVector.mData;
        otherVector.mData = nullptr;

        //otherVector.mData=temp;
        //mData=std::move(temp);
        //PrintVector(*this);
        //std::cout<<"assignment";
        return *this;

    }

    // Overloading the unary + operator
    Vector Vector::operator+() const
    {
        //std::cout<<"unary";
       Vector v(mSize);
       for (int i=0; i<mSize; i++)
       {
          v[i] = mData[i];
       }
       return std::move(v);
    }

    // Overloading the unary - operator
    Vector Vector::operator-() const
    {
       Vector v(mSize);
       for (int i=0; i<mSize; i++)
       {
          v[i] = -mData[i];
       }
       return std::move(v);
    }

    // Overloading the binary + operator
    Vector Vector::operator+(const Vector& v1) const
    {
        //std::cout<<"pluss"<<std::endl;
       assert(mSize == v1.mSize);
       Vector v(mSize);
       for (int i=0; i<mSize; i++)
       {
          v[i] = mData[i] + v1.mData[i];
       }
       //std::cout<<"pluss"<<std::endl;
       return std::move(v);
    }

    // Overloading the binary - operator
    Vector Vector::operator-(const Vector& v1) const
    {
       assert(mSize == v1.mSize);
       Vector v(mSize);
       for (int i=0; i<mSize; i++)
       {
          v[i] = mData[i] - v1.mData[i];
       }
       return std::move(v);
    }

    // Overloading scalar multiplication
    Vector Vector::operator*(double a) const
    {
       Vector v(mSize);
       for (int i=0; i<mSize; i++)
       {
          v[i] = a*mData[i];
       }
       return std::move(v);
    }

    // Method to calculate norm (with default value p=2)
    // corresponding to the Euclidean norm
    double Vector::CalculateNorm(int p) const
    {
       double norm_val, sum = 0.0;
       for (int i=0; i<mSize; i++)
       {
          sum += pow(fabs(mData[i]), p);
       }
       norm_val = pow(sum, 1.0/((double)(p)));
       return norm_val;
    }

    // Method to calculate scalar product with another vector
    double Vector::ScalarProduct(const Vector& v) const
    {
       double scalar_product = 0.0;
       assert(mSize == v.GetSize());
       for (int i=0; i<mSize; i++)
       {
          scalar_product += mData[i]*v[i];
       }
       return scalar_product;
    }

    double Vector::MaxElement() const
    {
        double max=mData[0];
        for (int i=1;i<mSize;i++)
        {
            if (mData[i]>max)
            {
                max=mData[i];
            }
        }
        return max;
    }

    // MATLAB style friend to get the size of a vector
    int length(const Vector& v)
    {
       return v.mSize;
    }
    //Code from Chapter10.tex line 60 save as Vector.cpp


    std::ostream& operator<<(std::ostream& output,
                            const Vector& v)
    {
       for (int i=0; i<v.mSize; i++)
       {
          output << std::setw(14)
                 << std::setprecision(5)
             << std::scientific
             << v[i]
             << std::endl;
       }
       output << std::endl;

       return output;
    }


    //MATLAB style friend for printing a vector to the output stream.
    void PrintVector(const Vector& PrintV)
    {
        int a=PrintV.GetSize();
        for (int i=0;i<a;i++)
        {
            std::cout<<std::setprecision(15)<<"|  "<<PrintV[i]<<"  |\n";
        }
    }

    //MATLAB style friend for finding the maximum of a vector.
    double Maxofvec(Vector& B)
    {
        int N=B.GetSize();
        double Max=0;
        for (int i=0;i<N;i++)
        {
            if (fabs(B[i])>Max)
            {
                Max=fabs(B[i]);
            }
        }
        return Max;
    }

    Matrix operator*(const Vector& v1,const Vector& v2)
    {
        int size=v1.GetSize();
        assert(size==v2.GetSize());
        Matrix output(size,size);
        for (int i=0;i<size;i++)
        {
            for (int j=0;j<size;j++)
            {

                output(i,j)=v1[i]*v2[j];
            }
        }
        return output;
    }
}
