#ifndef FINITEDIFFERENCESOLVERHEADERDEF
#define FINITEDEFFERENCESOLVERHEADERDEF

#include "../OCPDE/AbstractPDESolver.hpp"
#include "../OCPDE/SecondOrderPDE2d.hpp"
#include "../OCLinearSolve/InterativeSolvers/CGLinearSolver.hpp"
#include "../OCLinearSolve/InterativeSolvers/JacobiSolver.hpp"
#include "../OCLinearSolve/InterativeSolvers/GaussSeidelSolver.hpp"


template<typename M,typename V,typename Solver>
class FiniteDifferenceSolver:public AbstractPDESolver
{
public:

    FiniteDifferenceSolver(const GridFunction<2>& xgrid,
                            const std::string filename,
                            const SecondOrderPDE2d& myPDE,
                            const double tolerance);

    ~FiniteDifferenceSolver();

    void Solve();

private:

    std::unique_ptr<SecondOrderPDE2d> mpPDESystem;

    double mTolerance;

    std::unique_ptr<LinearSystem<M,V>> BuildSystem(M&& mat) const;

    //LinearSystem<M,V>&& BuildSystem(Type2Type<CSRMatrix>&& mat) const{};


    //Prevent automatic definition of operator =
    FiniteDifferenceSolver& operator=(const FiniteDifferenceSolver&);
};



template<typename M,typename V,typename Solver>
FiniteDifferenceSolver<M,V,Solver>::FiniteDifferenceSolver(const GridFunction<2>& grid,
                            const std::string filename,
                            const SecondOrderPDE2d& myPDE,
                            const double tolerance):
                                mpPDESystem(new SecondOrderPDE2d(myPDE))

{
    mOutputFileName=filename;
    mpxGrid=new GridFunction<2>(grid);
    mTolerance=tolerance;
}



template<typename M,typename V,typename Solver>
FiniteDifferenceSolver<M,V,Solver>::~FiniteDifferenceSolver()
{
    delete mpxGrid;
}


template<typename M,typename V,typename Solver>
std::unique_ptr<LinearSystem<M,V>> FiniteDifferenceSolver<M,V,Solver>::BuildSystem(M&& mat) const
{
    std::unique_ptr<M> m(new M(mat));
    int size=mpxGrid->GetSize();
    V RHS(size);
    //InteriorNode Interior;

    int xi,yi,xip1,xim1,yip1,yim1;
    if (mpPDESystem->GetUx()>=0)
    {
        xi=1;
        xip1=0;
        xim1=-1;
    }
    else if (mpPDESystem->GetUx()<0)
    {
        xi=-1;
        xip1=1;
        xim1=0;
    }
    if (mpPDESystem->GetUy()>=0)
    {
        yi=1;
        yip1=0;
        yim1=-1;
    }
    else if (mpPDESystem->GetUy()<0)
    {
        yi=-1;
        yip1=1;
        yim1=0;
    }
    int q(0);
    V f(1);


    auto ystepsize = mpxGrid->Getstepsize(0);
    auto xstepsize = mpxGrid->Getstepsize(1);



    for (int i=0;i<size;i++)
    {


           (*m)(i,i)=-(((2*mpPDESystem->GetUxx())/pow(xstepsize,2.0))+
              ((2*mpPDESystem->GetUyy())/pow(ystepsize,2.0))+
              ((xi*mpPDESystem->GetUx())/xstepsize)+((yi*mpPDESystem->GetUy())/ystepsize)+
               mpPDESystem->GetU());

            auto Interior(mpxGrid->GetInteriorNode(i));
            auto k=Interior.GetNode(Direction::North);

            auto DirectionValue=((-mpPDESystem->GetUyy())/pow(ystepsize,2))+
                                  ((yip1*mpPDESystem->GetUy())/ystepsize);

            if (k.first==false)
            {
                (*m)(i,k.second)=-DirectionValue;
            }
            else if (k.first==true)
            {
                RHS[i]=-(mpxGrid->GetBoundaryNode(k.second).GetValue())/(xstepsize*ystepsize);
            }

            k=Interior.GetNode(Direction::East);
            DirectionValue=((-mpPDESystem->GetUxx())/pow(xstepsize,2.0))+
                              ((xip1*mpPDESystem->GetUx())/xstepsize);

            if (k.first==false)
            {
                (*m)(i,k.second)=-DirectionValue;
            }
            else if(k.first==true)
            {
                RHS[i]=-(mpxGrid->GetBoundaryNode(k.second).GetValue())/(xstepsize*ystepsize);

            }


            k=Interior.GetNode(Direction::South);
            DirectionValue=((-mpPDESystem->GetUyy())/pow(ystepsize,2))+
                             ((yim1*mpPDESystem->GetUy())/ystepsize);

            if (k.first==false)
            {

                (*m)(i,k.second)=-DirectionValue;
            }
            else if (k.first==true)
            {
                RHS[i]=-(mpxGrid->GetBoundaryNode(k.second).GetValue())/(xstepsize*ystepsize);
            }


            k=Interior.GetNode(Direction::West);
            DirectionValue=((-mpPDESystem->GetUxx())/pow(xstepsize,2.0))+
                              ((xim1*mpPDESystem->GetUx())/xstepsize);
            if (k.first==false)
            {
                (*m)(i,k.second)=-DirectionValue;
            }
            else if (k.first==true)
            {
                RHS[i]=-(mpxGrid->GetBoundaryNode(k.second).GetValue())/(xstepsize*ystepsize);
            }


            f[0]=0;
            mpPDESystem->SetFInputs(Interior.GetLoc(0),Interior.GetLoc(1));
            mpPDESystem->ComputeF(f);
            RHS[i]+=f[0];
    }
    /*
    int a=size;
    int b=size;
    for (int i=0;i<a;i++)
    {
        std::cout<<"|";
        for (int j=0;j<b;j++)
        {
            std::cout<<std::setprecision(5)<<std::setw(10)<<(*m)(i,j)<<std::setw(10);
        }
        std::cout<<"|"<<std::endl;

    }
    */
    std::unique_ptr<LinearSystem<M,V>> SystemToSolve(new LinearSystem<M,V>(*m,RHS));
    return std::move(SystemToSolve);

}


template<typename M,typename V,typename Solver>
void FiniteDifferenceSolver<M,V,Solver>::Solve()
{

    PrintHeader("Finite Difference method");
    mpPDESystem->PrintHeader("SecondOrderPDE");
    int size=mpxGrid->GetSize();
    M m(size,size);
    std::unique_ptr<LinearSystem<M,V>> SystemToSolve=(BuildSystem(std::move(m)));

    //SystemToSolve->PrintHeader();

    V InitialGuess(size);

    //std::unique_ptr<JacobiSolver> Mx(new JacobiSolver(*SystemToSolve,InitialGuess,10e-10,100,false));
    std::unique_ptr<Solver> PS(new Solver(*SystemToSolve,InitialGuess,mTolerance,1000,false));

    std::unique_ptr<V> U(new Vector(size));

    PS->Solve(*U);

    SaveToFile(*U);
    std::cout<<"Final Solution ="<<std::endl;
    PrintVector(*U);
    V f(1);

    if (mpPDESystem->ExactSolDefined())
    {
        Vector Err(size);
        Vector ExactSol(size);

        for (int i=0;i<size;i++)
        {
            auto Interior(mpxGrid->GetInteriorNode(i));
            mpPDESystem->SetFInputs(Interior.GetLoc(0),Interior.GetLoc(1));
            mpPDESystem->ComputeAnalyticSolution(f);
            ExactSol[i]=f[0];
        }
        //Err=ExactSol-U;

        ChangeOutFileName("ExactSol");
        SaveToFile(ExactSol);

        //ChangeOutFileName("FDError");
        //SaveToFile(Err);
    }

}


#endif
