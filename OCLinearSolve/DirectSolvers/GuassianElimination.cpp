#include "GuassianElimination.hpp"


GuassianElimination::GuassianElimination(const LinearSystem* linearsyst)
{
    mpLinearSystem=linearsyst;
}

GuassianElimination::~GuassianElimination()
{

}


void GuassianElimination::Solve(Vector& u)
{

    double size=mpLinearSystem->GetVector()->GetSize();

    Matrix *M=mpLinearSystem->GetMatrix();
    Vector *V=mpLinearSystem->GetVector();


    for (int i=0;i<size;i++)
    {
        double am=fabs((*M)(i,i));
        int p=i;
        for (int j=i+1;j<size;j++)
        {
            if (fabs((*M)(j,i))>am)
            {
                am=fabs((*M)(j,i));
                p=j;
            }

        }
        if (p>i)
        {
            double hold(0);
            for (int j=i;j<size;j++)
            {
                hold=(*M)(i,j);
                (*M)(i,j)=(*M)(p,j);
                (*M)(p,j)=hold;
            }
            hold=(*V)[i];
            (*V)[i]=(*V)[p];
            (*V)[p]=hold;
        }
        for (int j=i+1;j<size;j++)
        {
            double m=(*M)(j,i)/(*M)(i,i);
            for (int k=i;k<size;k++)
            {
                (*M)(j,k)=(*M)(j,k)-m*(*M)(i,k);
            }
            (*V)[j]=(*V)[j]-m*(*V)[i];
        }

    }


    //Now solve using backward substitution
    double h(0);
    for (int i=0;i<size;i++)
    {
        for (int j=0;j<i;j++)
        {
            h+=(*M)(size-1-i,size-1-j)*u[size-1-j];
        }
        u[size-1-i]=((*V)[size-1-i]-h)/(*M)(size-1-i,size-1-i);
        h=0;
    }


}
