#ifndef CGLINEARSOLVERDEF
#define CGLINEARSOLVERDEF

#include "../ConvergenceCriterion.hpp"
#include "../LinearSystem.hpp"
#include "AbstractIterativeLinearSolver.hpp"


template<typename Mat,typename Vec>
class CGLinearSolver: public AbstractIterativeLinearSolver
{
private:
    const LinearSystem<Mat,Vec> mplinearsystem;

    std::unique_ptr<Vec> mpinitialguess;

    std::unique_ptr<ConvergenceCriterion> mpconvergence;

    bool mSaveData;


public:

    CGLinearSolver(const LinearSystem<Mat,Vec>& alinearsystem,
                   const Vec& initialguess,
                   const double tollerance,
                   const int maxiterations,
                   const bool savedata=false);

    CGLinearSolver(const LinearSystem<Mat,Vec>&& alinearsystem,
                   const Vec&& initialguess,
                   const double tollerance,
                   const int maxiterations,
                   const bool savedata=false);

    ~CGLinearSolver();

    void Solve(Vec& p) ;

    CGLinearSolver() = delete;

    CGLinearSolver& operator=(const CGLinearSolver&) = delete;

    CGLinearSolver& operator=(const CGLinearSolver&&) = delete;

};


template<typename Mat,typename Vec>
CGLinearSolver<Mat,Vec>::CGLinearSolver(const LinearSystem<Mat,Vec>& plinearsystem,
                               const Vec& initialguess,
                               const double tollerance,
                               const int maxiterations,
                               const bool savedata):
    AbstractIterativeLinearSolver(maxiterations,tollerance),
    mplinearsystem(plinearsystem),
    mpinitialguess(new Vec(initialguess)),
    mpconvergence(new ConvergenceCriterion(tollerance))
{

}

template<typename Mat,typename Vec>
CGLinearSolver<Mat,Vec>::CGLinearSolver(const LinearSystem<Mat,Vec>&& plinearsystem,
                               const Vec&& initialguess,
                               const double tollerance,
                               const int maxiterations,
                               const bool savedata):
    AbstractIterativeLinearSolver(maxiterations,tollerance),
    mplinearsystem(plinearsystem),
    mpinitialguess(std::move(initialguess)),
    mpconvergence(std::move(tollerance))
{

}

template<typename Mat,typename Vec>
CGLinearSolver<Mat,Vec>::~CGLinearSolver()
{

    //delete mplinearsystem;
}

template<typename Mat,typename Vec>
void CGLinearSolver<Mat,Vec>::Solve(Vec& x)
{
    assert(x.GetSize()==mpinitialguess->GetSize());
    PrintHeader("Congucate Gradiant");
    int size=x.GetSize();

    int k=0;
    Vec p(size);
    Vec r(size),r_old(size),q(size);
    double beta,alpha;
    Mat A((mplinearsystem).GetMatrix());

    mplinearsystem.CalculateResidual(x,r_old);

    p=r_old;


    double r_norm=pNorm(r_old,2.0);


    bool convergence= mpconvergence->TestConvergence(r_norm);

    while (k<mMaxIterations && !convergence)
    {

        q=(A)*(p);

        double rho_old=r_old.ScalarProduct(r_old);


        alpha=(rho_old)/(p.ScalarProduct(q));

        x=x+(p*alpha);

        r=r_old-(q*alpha);

        double rho=r.ScalarProduct(r);

        beta=(rho)/rho_old;

        p=r+(p*beta);

        r_old=r;

        k++;

        double r_norm=pNorm(r_old,2.0);

        convergence= mpconvergence->TestConvergence(r_norm);

        //PrintIteration(k,r_norm);
    }
    SaveSolution(x);

    PrintFooter(k,convergence);

}



#endif // CGLINEARSOLVERDEF
