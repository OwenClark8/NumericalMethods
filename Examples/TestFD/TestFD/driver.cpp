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

    double xstepsize= 0.001;
    double ystepsize = 0.001;

    double tollerance = 10e-10;

    std::vector<std::array<double,2>> coordinates;


    std::vector<std::pair<std::array<double,2>,std::array<double,2> > > Lines;
    Lines.reserve(4);
    Lines.push_back({{0,0},{0,1}});
    Lines.push_back({{0,0},{1,0}});
    Lines.push_back({{0,1},{1,1}});
    Lines.push_back({{1,0},{1,1}});



    std::vector<std::pair<std::array<double,2>,std::array<double,2> > > h(Lines);


    std::unique_ptr<Shape<2>> Square(new Polygon<2>(Lines));



    FDBuilder myBuilder(std::move(Square),xstepsize,ystepsize,1.0,0.0,1.0,0.0);

    myBuilder.BuildPart();

    auto mp_Grid(myBuilder.GetProduct());


    SecondOrderPDE2d myPDE(1,0,1,0,0,[](double x,double y){return 1;});


    FiniteDifferenceSolver<CSRMatrix,Vector,CGLinearSolver<CSRMatrix,Vector>> mySolver(*(mp_Grid),"Square.dat",myPDE,tollerance);
    std::cout<<"Start"<<std::endl;
    mySolver.Solve();


    /*
     Vector V2(100000);
    for(int i=0;i<10000;i++)
    {
       V2[i]=i;

    }
     Vector V1((V2));
    for(int i=0;i<100000;i++)
    {

        V1[i]=i;
        V2[i]=i+1;

    }
    std::cout<<"hi"<<V1[4];
    for(int i=0;i<1;i++)
    {
       V1=V1+V2;
       //std::cout<<"end";

    }
    //std::cout<<"hiya";
    //V1=V1+V2;
    //V1=V1+V2;
    std::cout<<"end";
    std::cout<<V1[1];




*/






}

