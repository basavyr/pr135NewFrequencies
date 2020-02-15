#include "../include/energyTest.hh"
#include "../include/energyFormulae.hh"

void EnergyTest::unitfySets(std::vector<double> &set1, std::vector<double> &set2, std::vector<double> &destination)
{
    //only work if the sets are identical in size
    // if (set1.size() != set2.size())
    //     return;
    for (int i = 0; i < set1.size(); ++i)
    {
        destination.emplace_back(set1.at(i));
    }
    for (int i = 0; i < set2.size(); ++i)
    {
        destination.emplace_back(set2.at(i));
    }
}

void EnergyTest::initParams(double i1, double i2, double i3, double theta)
{
    setOfParams.I1 = i1;
    setOfParams.I2 = i2;
    setOfParams.I3 = i3;
    setOfParams.theta = theta;
}

EnergyTest::EnergyTest(double i1, double i2, double i3, double theta, int choice)
{
    //choice stands for the two data sets
    initParams(i1, i2, i3, theta);
    auto theoreticalData = generateTheoreticalData();
    std::vector<double> experimentalData;
    std::vector<double> spins;
    unitfySets(spin1, spin2, spins);
    if (choice == 1)
        unitfySets(band1_ENSDF, band2_ENSDF, experimentalData);
    else
    {
        unitfySets(band1_MATTA, band2_MATTA, experimentalData);
    }
    std::cout << spins.size() << "\n";
    printTable<double>(spins, experimentalData, theoreticalData, setOfParams);
}

EnergyTest::~EnergyTest()
{
    std::cout << "The class for energy test finished with success..."
              << "\n";
    std::cout << "********************"
              << "\n";
}

std::vector<double> EnergyTest::generateTheoreticalData()
{
    std::vector<double> results;
    for (int i = 0; i < spin1.size(); ++i)
    {
        results.emplace_back(EnergyFormulas::energyExpression(0, spin1.at(i), setOfParams.I1, setOfParams.I2, setOfParams.I3, setOfParams.theta));
    }
    for (int i = 0; i < spin2.size(); ++i)
    {
        results.emplace_back(EnergyFormulas::energyExpression(0, spin1.at(i), setOfParams.I1, setOfParams.I2, setOfParams.I3, setOfParams.theta));
    }
    return results;
}