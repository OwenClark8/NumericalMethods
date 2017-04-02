#include "BoundaryNode.hpp"

template class BoundaryNode<2>;


template<int dim>
BoundaryNode<dim>::BoundaryNode(const Coordinate<double,dim>& c,const int globalnumber,const double value, bool isdir)
                            :mGlobalNumber(globalnumber),mxyz(c)
{
    Set(isdir,value);
}

template<int dim>
double BoundaryNode<dim>::GetValue() const
{
    return mValue;
}

template<int dim>
int BoundaryNode<dim>::GetGlobalNumber() const
{
    return mGlobalNumber;
}

template<int dim>
void BoundaryNode<dim>::ChangeValues(const int globalnumber, const double values)
{
    mValue=values;
    mGlobalNumber=globalnumber;
}
