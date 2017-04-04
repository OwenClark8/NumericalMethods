#include "C:\Users\Owen\Documents\PhDC++\OCMathLib\OCMathLib.hpp"
#include "C:\Users\Owen\Documents\PhDC++\OCLinearSolve\LinearSystem.hpp"
//#include "shape.hpp"
#include "..\..\..\FiniteDiffernce/FDBuilder.h"

#include <array>
#include <utility>
#include <stdio.h>
#include <vector>

//enum class Direction{North, South, West, East};

using namespace OCMathLib;


int main()
{

    double xstepsize= 0.01;
    double ystepsize = 0.01;

    double tollerance = 10e-10;

    std::vector<std::array<double,2>> coordinates;


    std::vector<std::pair<std::array<double,2>,std::array<double,2> > > Lines;
    Lines.reserve(4);
    Lines.push_back({{0.5,0},{1,0.5}});
    Lines.push_back({{0.5,0},{0,0.5}});
    Lines.push_back({{0,0.5},{0.5,1}});
    Lines.push_back({{1,0.5},{0.5,1}});



    std::vector<std::pair<std::array<double,2>,std::array<double,2> > > h(Lines);


    std::unique_ptr<Shape<2>> Square(new Polygon<2>(Lines));



    FDBuilder myBuilder(std::move(Square),xstepsize,ystepsize,1.0,0.0,1.0,0.0);
    std::cout<<"Start"<<std::endl;
    myBuilder.BuildPart();

    auto mp_Grid(myBuilder.GetProduct());


    SecondOrderPDE2d myPDE(1,0,1,0,0,[](double x,double y){return 1;});


    FiniteDifferenceSolver<Matrix,Vector,JacobiSolver<Matrix,Vector>> mySolver(*(mp_Grid),"Square.dat",myPDE,tollerance);

    mySolver.Solve();













}

