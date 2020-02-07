#include "../include/experimentalData.hh"

std::vector<double> ExpData_ENSDF::yrastExp = ExpData_ENSDF::init_yrast<double>();
std::vector<double> ExpData_ENSDF::wobbExp = ExpData_ENSDF::init_wobbling<double>();
std::vector<double> ExpData_ENSDF::spin1 = ExpData_ENSDF::init_spin1<double>();
std::vector<double> ExpData_ENSDF::spin2 = ExpData_ENSDF::init_spin2<double>();

ExpData_ENSDF::ExpData_ENSDF()
{
    generateDataSet(yrastExp, wobbExp, energiesExp);
    generateDataSet(spin1, spin2, spins);
}

ExpData_ENSDF::~ExpData_ENSDF()
{
}

void ExpData_ENSDF::generateDataSet(std::vector<double> &set1, std::vector<double> &set2, std::vector<double> &destination)
{
    if (destination.size())
        destination.clear();
    for (auto &&n : set1)
    {
        destination.emplace_back(static_cast<double>(n));
    }
    for (auto &&n : set2)
    {
        destination.emplace_back(static_cast<double>(n));
    }
}
