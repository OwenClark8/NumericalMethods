#ifndef INTERIORNODEHEADERDEF
#define INTERIORNODEHEADERDEF

#include <utility>


#include <vector>
#include "BoundaryNode.hpp"
using Connection = std::pair<bool,int>;
//Substitute array for pair maybe use boost library flyweight
template<int n>
class InteriorNode
{
//using Connection = std::array<int,2>;

private:
    Coordinate<double,n> mxyz;

    int mGlobalNumber;

    Connection mNorth;

    Connection mSouth;

    Connection mWest;

    Connection mEast;

public:
    InteriorNode(const Coordinate<double,n>& c,const int globalnumber,const Connection north,const Connection east,
                 const Connection south,const Connection west);

    Connection GetNode(const Direction& d) const;

    int GetGlobalNumber() const;

    void ChangeValues(const int globalnumber,const Connection north,const Connection east,
                 const Connection south,const Connection west);

    double GetLoc(int i) const;


};



template<int n>
InteriorNode<n>::InteriorNode(const Coordinate<double,n>& c, const int globalnumber, Connection north,Connection south,
                 Connection west,Connection east):
                 mxyz(c), mGlobalNumber(globalnumber),
                 mNorth(north),mEast(east),mSouth(south),mWest(west)
{
}

template<int n>
Connection InteriorNode<n>::GetNode(const Direction& d) const
{
    if (d==Direction::North)
    {
        return mNorth;
    }
    else if (d==Direction::East)
    {
        return mEast;
    }
    else if (d==Direction::South)
    {
        return mSouth;
    }
    else if (d==Direction::West)
    {
        return mWest;
    }

    //Add options for up and down
}

template<int n>
int InteriorNode<n>::GetGlobalNumber() const
{
    return mGlobalNumber;
}

template<int n>
void InteriorNode<n>::ChangeValues(const int globalnumber,const Connection north,const Connection east,
                 const Connection south,const Connection west)
{
    mGlobalNumber=globalnumber;
    mNorth=north;
    mWest=west;
    mSouth=south;
    mEast=east;
}


template<int n>
double InteriorNode<n>::GetLoc(int i) const
{
    return mxyz.xyz[i];
}





#endif // INTERIORNODEHEADERDEF
