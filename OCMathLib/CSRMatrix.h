#ifndef CSRMATRIX_H
#define CSRMATRIX_H

namespace OCMathLib{
class Vector;
class CSRMatrix
{

     private:
        Vector* mpMatrixEntries;
        Vector* mpColumnNo;
        Vector* mpRowStart;
    public:
        CSRMatrix(const CSRMatrix& othermatrix);

        CSRMatrix(CSRMatrix&& othermatrix);

        CSRMatrix(const Vector& entries,const Vector& columns,const Vector& rowstart);

        CSRMatrix(Vector&& entries,Vector&& columns, Vector&& rowstart);

        ~CSRMatrix();

        int GetNumberOfRows() const;
        int GetNumberOfColumns() const;
        int GetNumberEntries() const;

        CSRMatrix& operator=(const CSRMatrix& othermatrix);

        CSRMatrix& operator=(CSRMatrix&& othermatrix);

        CSRMatrix operator*(double x);

        const double& operator()(const int i,const int j) const;

        friend Vector operator*(const CSRMatrix& m,const Vector& v);

        friend void PrintCSRMatrix(const CSRMatrix& M);


};
}
#endif // CSRMATRIX_H
