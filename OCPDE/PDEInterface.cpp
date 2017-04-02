#include "PDEInterface.hpp"


void PDEInterface::ComputeAnalyticSolution(Vector& u) const
{

}

void PDEInterface::PrintHeader(const std::string PDEtype) const
{

}


std::string to_string(int i)
{
    std::stringstream ss;
    ss << i;
    return ss.str();
}
