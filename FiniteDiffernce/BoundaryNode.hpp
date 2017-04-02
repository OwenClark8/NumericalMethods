#ifndef BOUNDARYNODEHEADERDEF
#define BOUNDARYNODEHEADERDEF


#include <array>
#include "../OCPDE/BoundaryConditions.hpp"
//Direction of neighbours
enum class Direction{North, South, East, West, Up, Down};

template<typename T,int n>
struct Coordinate
{
    std::array<T,n> xyz;
    Coordinate(const Coordinate& c)
    {
        xyz=c.xyz;
    }

};


//
template<int dim>
class BoundaryNode : public BoundaryConditions
{
private:
    int mGlobalNumber;

    Coordinate<double,dim> mxyz;

public:
    BoundaryNode(const Coordinate<double,dim>& c, const int globalnumber,const double value, bool isdir);

    double GetValue() const;

    int GetGlobalNumber() const;

    void ChangeValues(const int globalnumber,const double value);

};



#endif // INTERIORNODEHEADERDEF
