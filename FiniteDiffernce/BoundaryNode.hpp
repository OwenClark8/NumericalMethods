#ifndef BOUNDARYNODEHEADERDEF
#define BOUNDARYNODEHEADERDEF


#include <array>
#include "../OCPDE/BoundaryConditions.hpp"
//Direction of neighbours
enum class Direction{North, South, East, West, Up, Down};

template<typename T,int n>
struct Coordinate1
{
    std::array<T,n> xyz;
    Coordinate1(const Coordinate1& c)
    {
        xyz=c.xyz;
    }


};

//using Coordinate<typename T,int n> = std::array<T,n>;


//
template<int dim>
class BoundaryNode : public BoundaryConditions
{
public:
    using Coordinate= std::array<double,dim>;
private:
    int mGlobalNumber;

    Coordinate mxyz;

public:
    BoundaryNode(const Coordinate& c, const int globalnumber,const double value, bool isdir);

    double GetValue() const;

    int GetGlobalNumber() const;

    void ChangeValues(const Coordinate& c,const int globalnumber,const double value);

};

template<int dim>
BoundaryNode<dim>::BoundaryNode(const Coordinate& c,const int globalnumber,const double value, bool isdir)
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
void BoundaryNode<dim>::ChangeValues(const Coordinate& c,const int globalnumber, const double values)
{
    mxyz=c;
    mValue=values;
    mGlobalNumber=globalnumber;
}


#endif // INTERIORNODEHEADERDEF
