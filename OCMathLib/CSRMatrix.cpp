#include "CSRMatrix.h"
#include "Vector.hpp"


namespace OCMathLib
{

//Overridden default constructor
CSRMatrix::CSRMatrix(const CSRMatrix& othermatrix):
    mpMatrixEntries(new Vector(*othermatrix.mpMatrixEntries)),
    mpColumnNo(new Vector(*othermatrix.mpColumnNo)),
    mpRowStart(new Vector(*othermatrix.mpRowStart))
{

}

CSRMatrix::CSRMatrix(CSRMatrix&& othermatrix):
        mpMatrixEntries(nullptr),
    mpColumnNo(nullptr),
    mpRowStart(nullptr)
{

    mpMatrixEntries=othermatrix.mpMatrixEntries;
    mpColumnNo=othermatrix.mpColumnNo;
    mpRowStart=othermatrix.mpRowStart;

    othermatrix.mpMatrixEntries = nullptr;
    othermatrix.mpColumnNo = nullptr;
    othermatrix.mpRowStart = nullptr;
}

CSRMatrix::CSRMatrix(const Vector& entries,const Vector& columns,const Vector& rowstart):
    mpMatrixEntries(new Vector(entries)),mpColumnNo(new Vector(columns)),
    mpRowStart(new Vector(rowstart))
{
}

CSRMatrix::CSRMatrix(Vector&& entries,Vector&& columns, Vector&& rowstart):
    mpMatrixEntries(new Vector(std::move(entries))),mpColumnNo(new Vector(std::move(columns))),
    mpRowStart(new Vector(std::move(rowstart)))
{
}

CSRMatrix::~CSRMatrix()
{
    delete mpMatrixEntries;
    delete mpColumnNo;
    delete mpRowStart;
}

int CSRMatrix::GetNumberOfColumns() const
{
    return int(Maxofvec(*mpColumnNo))+1;
}

int CSRMatrix::GetNumberOfRows() const
{
    return (mpRowStart->GetSize()-1);
}

int CSRMatrix::GetNumberEntries() const
{
    return (mpMatrixEntries->GetSize());
}

CSRMatrix& CSRMatrix::operator=(CSRMatrix&& othermatrix)
{

    delete[] mpMatrixEntries;
    delete[] mpColumnNo;
    delete[] mpRowStart;
    mpMatrixEntries=othermatrix.mpMatrixEntries;
    mpColumnNo=othermatrix.mpColumnNo;
    mpRowStart=othermatrix.mpRowStart;

    othermatrix.mpMatrixEntries = nullptr;
    othermatrix.mpColumnNo = nullptr;
    othermatrix.mpRowStart = nullptr;
    return *this;
}


CSRMatrix& CSRMatrix::operator=(const CSRMatrix& othermatrix)
{
    Vector *tempEntries=mpMatrixEntries;
    mpMatrixEntries=new Vector(*othermatrix.mpMatrixEntries);
    delete tempEntries;
    Vector *tempColumns=mpColumnNo;
    mpColumnNo=new Vector(*othermatrix.mpColumnNo);
    delete tempColumns;
    Vector *tempRows=mpRowStart;
    mpRowStart=new Vector(*othermatrix.mpRowStart);
    delete tempColumns;
    return *this;
}

const double& CSRMatrix::operator()(const int a,const int b) const
{
    for (int i=0;i<(mpRowStart->GetSize())-1;i++)
    {
        for (int j=(*mpRowStart)[i];j<(*mpRowStart)[i+1];j++)
        {
            if (a==(*mpColumnNo)[j]&& b==i)
            {
                return (*mpMatrixEntries)[j];
            }
            if (j==b)
            {
                break;
            }
        }
        if (i==a)
        {
            break;
        }
    }
    return 0.0;
}

Vector operator*(const CSRMatrix& m,const Vector& v)
{
    int n=v.GetSize();
    int Rows=m.GetNumberOfRows();
    int columns=m.GetNumberOfColumns();
    assert(columns==n);
    Vector output(Rows);
    for (int i=0;i<(Rows);i++)
    {
        for (int j=(*m.mpRowStart)[i];j<(*m.mpRowStart)[i+1];j++)
        {
            //if(j==)
            output[i]+=(*m.mpMatrixEntries)[j]*(v[(*m.mpColumnNo)[j]]);
        }
    }
    return std::move(output);
}



/*
CSRMatrix CSRMatrix::operator*(CSRMatrix& amatrix)
{

}
*/
CSRMatrix CSRMatrix::operator*(double x)
{
    Vector t(this->GetNumberEntries());
    t=(*mpMatrixEntries)*x;
    CSRMatrix output(t,*mpColumnNo,*mpRowStart);
    return std::move(output);
}
/*
CSRMatrix CSRMatrix::operator+(CSRMatrix& m)
{
    assert(m.GetNumberOfRows()==this->GetNumberOfRows());
    int counter;
    NumList entries;
    for (int i=0;i<(mpRowStart->GetSize());i++)
    {
        for (int j=mpRowStart->Read(i)-1;j<mpRowStart->Read(i+1)-1;j++)
        {
            if (m.mpColumnNo->Read(j)==mpColumnNo->Read(j))
            {
                counter++;
                entries.push_back(mpMatrixEntries->Read(j));

            }
            if (m.mpColumnNo->Read(j)>mpColumnNo->Read(j))
            {
                counter=counter+2;
                entries.push_back(mpMatrixEntries->Read(j));
                entries.push_back(m.mpMatrixEntries->Read(j));
            }
            else if (m.mpColumnNo->Read(j)<mpColumnNo->Read(j))
            {
                counter=counter+2;
                entries.push_back(m.mpMatrixEntries->Read(j));
                entries.push_back(mpMatrixEntries->Read(j));
            }
        }
    }
    Vector matrixentries(counter);

}

CSRMatrix CSRMatrix::operator-(CSRMatrix& amatrix)
{

}
*/

void PrintCSRMatrix(const CSRMatrix& M)
{
    int size(M.GetNumberOfRows());
    for (int i=0;i<(size);i++)
    {
        std::cout<<"|";
        int row=(*M.mpRowStart)[i+1];
        int k=(*M.mpRowStart)[i];
        for (int j=0;j<size;j++)
        {

            if (j!=(*M.mpColumnNo)[k] || k==row)
            {
                std::cout<<"  "<<0<<"  ";
            }
            else
            {
                std::cout<<std::setprecision(15)<<"  "<<(*M.mpMatrixEntries)[k]<<"  ";
                k++;

            }

        }
        std::cout<<"|"<<std::endl;

    }


}
}
