#include "../include/rootMeanSquare.hh"
#include "../include/experimentalData.hh"
#include "../include/energyFormulae.hh"
#include "../include/bandAdjustment.hh"
#include "../include/minimalParams.hh"

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
    auto yrast = [&](auto spin) {
        return static_cast<double>(EnergyFormulas::energyExpression(0, spin, I1, I2, I3, theta));
    };
    auto wobbling = [&](auto spin) {
        return static_cast<double>(EnergyFormulas::energyExpression(0, spin, I1, I2, I3, theta));
    };
    int count = 0;
    for (int i = 0; i < ExpData_ENSDF::spin1.size(); ++i)
    {
        //replace with energy formula
        auto currentValue = yrast(ExpData_ENSDF::spin1.at(i));
        if (currentValue != 6969)
        {
            energyContainer.emplace_back(currentValue);
            count++;
        }
    }
    for (int i = 0; i < ExpData_ENSDF::spin2.size(); ++i)
    {
        //replace with energy formula
        auto currentValue = wobbling(ExpData_ENSDF::spin2.at(i));
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

//theory - experiment
std::vector<double> RootMeanSquare::deltaArray(std::vector<double> &v1, std::vector<double> &v2)
{
    std::vector<double> results;
    std::vector<double> nullVector = {};
    if (v1.size() != v2.size() || !v1.size() || !v2.size())
        return nullVector;
    for (int i = 0; i < v1.size(); ++i)
    {
        results.emplace_back(v2.at(i) - v1.at(i));
    }
    return results;
}

double RootMeanSquare::RMS_fromAdjustQuantas(double quanta1, double quanta2)
{
    auto expData1_Adjusted = BandAdjuster::mobileSubtractor(ExpData_ENSDF::yrastExp, 0, 3, quanta1);
    auto expData2_Adjusted = BandAdjuster::mobileSubtractor(ExpData_ENSDF::wobbExp, 3, 5, quanta2);
    std::vector<double> expData_Adjusted;
    ExpData_ENSDF::generateDataSet(expData1_Adjusted, expData2_Adjusted, expData_Adjusted);
    MinimalParameters::minSetOfParams bestParams;
    MinimalParameters::searchMinimum(expData_Adjusted, bestParams);
    ExpData_ENSDF::printArray(expData_Adjusted);
    // MinimalParameters::paramPrinter(bestParams);
    return bestParams.RMS;
}

double RootMeanSquare::rms_fromFitParameters(double a1, double a2, double a3, double theta)
{
    auto i1 = static_cast<double>(1 / (2 * a1));
    auto i2 = static_cast<double>(1 / (2 * a2));
    auto i3 = static_cast<double>(1 / (2 * a3));
    auto data = generateTheoreticalData(i1, i2, i3, theta);
    std::vector<double> expData;
    auto x1 = ExpData_ENSDF::yrastExp;
    auto x2 = ExpData_ENSDF::wobbExp;
    ExpData_ENSDF::generateDataSet(x1, x2, expData);
    ExpData_ENSDF::printArray(expData);
    auto result = static_cast<double>(RMS_calculation(expData, data));
    return result;
    // BandAdjuster::generateDataSet(x1, , expData);
    // return RMS_calculation(expData, data);
}