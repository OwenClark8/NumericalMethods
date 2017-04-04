#ifndef FDBUILDER_H
#define FDBUILDER_H

#include "FiniteDifferenceSolver.hpp"
#include "GridFunction.hpp"
#include <math.h>
#include <algorithm>

struct ConnectS{
using Coordinate = std::array<double,2>;
    Coordinate C;
    int type;
    int globalval;
    ConnectS(const Coordinate& Co,int t,int gv):
        C(Co),type(t),globalval(gv){};
    ConnectS& operator=(const ConnectS& Co)
    {
        C=Co.C;
        type=Co.type;
        globalval=Co.globalval;
        return *this;
    }
};


template<int n>
class Shape
{
public:
using Coordinate = std::array<double,n>;
using Line = std::pair<Coordinate,Coordinate>;
    virtual ~Shape(){};
    Shape(){};

    virtual Line CutViaY(double y,double tol) const =0;


};

template<int n>
class Polygon : public Shape<n>
{
public:

using Coordinate = typename Shape<n>::Coordinate;
using Line = typename Shape<n>::Line;
private:
    std::unique_ptr<std::vector<Line>> Vertices;

    double findon(const Line& L,double y) const
    {
        //std::cout<<"On Line y= "<<L.first[1]<<"  "<<L.second[1]<<std::endl;
        //std::cout<<"On Line x= "<<L.first[0]<<"  "<<L.second[0]<<std::endl;
        if(L.first[0] - L.second[0] == 0)
        {
            return L.first[0];
        }
        else if(L.first[1] - L.second[1] == 0)
        {
            return  (L.first[0] > L.second[0]) ? L.first[0] : L.second[0];
        }
        else
        {

            Coordinate diff{{L.first[0] - L.second[0],L.first[1] - L.second[1]}};

            double grad = diff[1]/diff[0];
            //std::cout<<"grad = "<<grad<<std::endl;
            double c = (L.first[1]-grad * L.first[0]);
            //std::cout<<"result is "<<(1.0/grad) * (y -c)<<std::endl;
            return (1.0/grad) * (y -c);

        }

    };
public:

    Polygon(std::vector<Line>& co):Vertices(new std::vector<Line>(co))
    {
    };

    Line CutViaY(double y,double tol) const
    {
        auto it1 = std::find_if(Vertices->begin(),Vertices->end(),
                        [y,tol](const Line& c){
                               return ((c.second[1]< y +tol && c.first[1]>y-tol)
                                       || (c.second[1]> y-tol && c.first[1]<y+tol));});

        //std::cout<<"Iterator 1 x is "<<(*it1).second[0]<<"   "<<(*it1).first[0]<<std::endl;
        //std::cout<<"Iterator 1 y is "<<(*it1).second[1]<<"   "<<(*it1).first[1]<<std::endl;
        auto X = findon(*it1,y);
        //auto X(0);

        auto X2(X);


        auto temp = it1;
        do
        {
            temp=it1;
            X2 = findon(*temp,y);
            it1++;
            it1 = std::find_if(it1,Vertices->end(),
                        [y,tol](const Line& c){
                               return ((c.second[1]< y +tol && c.first[1]>y-tol)
                                       || (c.second[1]> y-tol && c.first[1]<y+tol));});


        }while(X2 == X && it1 != Vertices->end());

        //std::cout<<"Iterator 2 x is "<<(*temp).second[0]<<"   "<<(*temp).first[0]<<std::endl;
        //std::cout<<"Iterator 2  y is "<<(*temp).second[1]<<"   "<<(*temp).first[1]<<std::endl;
        Line out;
        if (X>=X2)
            out={{X2,y},{X,y}};
        else
            out={{X,y},{X2,y}};

        return out;
    };
};

class FDBuilder
{
public:
    using Coordinate = std::array<double,2>;
    FDBuilder(std::unique_ptr<Shape<2>> s, double xstepsize,double ystepsize,double ymax,
              double ymin,double xmax,double xmin);

    void BuildPart();

    std::unique_ptr<GridFunction<2>> GetProduct();

protected:

private:
    std::unique_ptr<GridFunction<2>> mGF;
    double mxstepsize;
    double mystepsize;
    std::unique_ptr<Shape<2>> mShape;
    double maxy;
    double miny;
    double maxx;
    double minx;
};


#endif // FDBUILDER_H
