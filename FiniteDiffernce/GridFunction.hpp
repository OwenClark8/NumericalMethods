#ifndef GRIDFUNCTIONHEADERDEF
#define GRIDFUNCTIONHEADERDEF

#include "../OCMathLib/OCMathLib.hpp"
#include "BoundaryNode.hpp"
#include "InteriorNode.hpp"
using namespace OCMathLib;


template<int n>
class GridFunction
{
private:
    std::array<double, n> mstepsize;

    std::vector<InteriorNode<n>> mInteriorPoints;

    std::vector<BoundaryNode<n>> mBoundaryPoints;

    GridFunction& operator=(const GridFunction&);

public:

    GridFunction(const std::vector<InteriorNode<n>>& interiornodes,
                 const std::vector<BoundaryNode<n>>& Boundarynodes,
                 const std::array<double,n>& xss);

    GridFunction(const GridFunction& othergrid);

    //double GetInitialX() const;
    //double GetFinalX() const;
    //double GetXStepSize() const;

    //double GetInitialY() const;
    //double GetFinalY() const;
    //double GetYStepSize() const;

    int GetSize() const;

    double Getstepsize(int i) const;


    BoundaryNode<n> GetBoundaryNode(const int i) const;

    InteriorNode<n> GetInteriorNode(const int i) const;

};


template<int n>
GridFunction<n>::GridFunction(const std::vector<InteriorNode<n>>& interiornodes,
                 const std::vector<BoundaryNode<n>>& boundarynodes,
                 const std::array<double,n>& xss)
                           :mInteriorPoints(interiornodes),
                           mBoundaryPoints(boundarynodes),
                           mstepsize(xss)
{
}
template<int n>
GridFunction<n>::GridFunction(const GridFunction<n>& othergrid)
                            :mInteriorPoints(othergrid.mInteriorPoints),
                            mBoundaryPoints(othergrid.mBoundaryPoints),
                            mstepsize(othergrid.mstepsize)
{
}

template<int n>
int GridFunction<n>::GetSize() const
{
    return mInteriorPoints.size();
}

template<int n>
double GridFunction<n>::Getstepsize(int i) const
{
    return mstepsize[i];
}

template<int n>
InteriorNode<n> GridFunction<n>::GetInteriorNode(const int i) const
{
    return mInteriorPoints.at(i);
}

template<int n>
BoundaryNode<n> GridFunction<n>::GetBoundaryNode(const int i) const
{
    return mBoundaryPoints.at(i);
}
#endif // GRIDFUNCTIONHEADERDEF
