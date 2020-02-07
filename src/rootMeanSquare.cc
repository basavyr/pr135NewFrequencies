#include "../include/rootMeanSquare.hh"
#include "../include/experimentalData.hh"
#include "../include/energyFormulae.hh"


double RootMeanSquare::RMS_calculation(std::vector<double> &exp, std::vector<double> &th)
{
    //FAIL IF EMPTY CONTAINERS AND FIF UNEQUAL
    if ((!exp.size() || !th.size()) && (exp.size() != th.size()))
        return 6969;
    double sum = 0;
    int count = 0;
    for (int i = 0; i < exp.size(); ++i)
    {
        auto currentValue = pow(exp.at(i) - th.at(i), 2);
        if (!isnan(currentValue))
        {
            sum += currentValue;
            count++;
        }
    }
    if (count == exp.size())
    {
        auto result = static_cast<double>(sqrt(sum / exp.size()));
        return result;
    }
    return 6969;
}

std::vector<double> RootMeanSquare::generateTheoreticalData(double I1, double I2, double I3, double theta)
{
    std::vector<double> energyContainer;
    std::vector<double> nullContainer = {};
    int count = 0;
    for (int i = 0; i < ExpData_ENSDF::spin1.size(); ++i)
    {
        //replace with energy formula
        auto currentValue = 1;
        if (currentValue != 6969)
        {
            energyContainer.emplace_back(currentValue);
            count++;
        }
    }
    for (int i = 0; i < ExpData_ENSDF::spin2.size(); ++i)
    {
        //replace with energy formula
        auto currentValue = 1;
        if (currentValue != 6969)
        {
            energyContainer.emplace_back(currentValue);
            count++;
        }
    }
    auto size = static_cast<size_t>(ExpData_ENSDF::spin1.size() + ExpData_ENSDF::spin2.size());
    if (count == size)
    {
        return energyContainer;
    }
    return nullContainer;
}

void RootMeanSquare::generateSubsets(std::vector<double> &source, std::vector<double> &set1, std::vector<double> &set2)
{
    //only work for non-empty containers
    if (!source.size())
        return;
    if (!set1.size())
        set1.clear();
    if (!set2.size())
        set2.clear();
    auto size = static_cast<size_t>(ExpData_ENSDF::spin1.size() + ExpData_ENSDF::spin2.size());
    for (int i = 0; i < ExpData_ENSDF::spin1.size(); ++i)
    {
        set1.emplace_back(source.at(i));
    }
    for (int i = ExpData_ENSDF::spin1.size(); i < size; ++i)
    {
        set2.emplace_back(source.at(i));
    }
}