#ifndef ENERGYTEST_HH
#define ENERGYTEST_HH

#include <vector>
#include <iostream>
#include <string>

class EnergyTest
{
public:
    struct paramSet
    {
        double I1, I2, I3;
        double theta;
    };
    void initParams(double i1, double i2, double i3, double theta);

private:
    paramSet setOfParams;

public:
    //constructor
    EnergyTest(double i1, double i2, double i3, double theta, int choice);
    //destructor
    ~EnergyTest();

public:
    std::vector<double> band1_MATTA = {1, 2, 3};
    std::vector<double> band2_MATTA = {1, 2, 3};
    std::vector<double> band1_ENSDF = {1, 2, 3};
    std::vector<double> band2_ENSDF = {1, 2, 3};
    std::vector<double> spin1 = {7.5, 9.5, 11.5, 13.5, 15.5, 17.5, 19.5, 21.5, 23.5, 25.5};
    std::vector<double> spin2 = {8.5, 10.5, 12.5, 14.5, 16.5};

public:
    template <typename T>
    static void printTable(std::vector<T> &spins, std::vector<T> &energyExp, std::vector<T> &energyTh, paramSet &params)
    {
        //only work for equal arrayss
        if (spins.size() != energyExp.size() || energyExp.size() != energyTh.size())
        {
            return;
        }
        std::cout << "Results for the set of parameters: "
                  << "\n";
        std::cout << "A1= " << params.I1 << " A2= " << params.I2 << " A3= " << params.I3 << " theta= " << params.theta
                  << "\n";
        std::cout << "Spin [hbar]   "
                  << "E_exp [MeV]   "
                  << "E_th [MeV]"
                  << "\n";
        for (int i = 0; i < spins.size(); ++i)
        {
            std::cout << spins.at(i) << " " << energyExp.at(i) << " " << energyTh.at(i) << "\n";
        }
    }
    static void unitfySets(std::vector<double> &set1, std::vector<double> &set2, std::vector<double> &destination);
    std::vector<double> generateTheoreticalData();
};

#endif // ENERGYTEST_HH
