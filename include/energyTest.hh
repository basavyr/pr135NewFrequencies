#ifndef ENERGYTEST_HH
#define ENERGYTEST_HH

#include <vector>
#include <iostream>
#include <string>
#include <fstream>

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
    std::vector<double> band1_MATTA = {0.3728, 1.033, 1.8872, 2.8873, 3.9628, 4.8068, 5.6407, 6.5224, 7.4453, 8.4023};
    std::vector<double> band2_MATTA = {1.1198, 1.8458, 2.6418, 3.5974, 4.7094};
    std::vector<double> band1_ENSDF = {0.37277, 1.03284, 1.88684, 2.88674, 3.96174, 4.80574, 5.63974, 6.52174, 7.44474, 8.35794};
    std::vector<double> band2_ENSDF = {1.07524, 1.80044, 2.64294, 3.59894, 4.71094};
    std::vector<double> spin1 = {7.5, 9.5, 11.5, 13.5, 15.5, 17.5, 19.5, 21.5, 23.5, 25.5};
    std::vector<double> spin2 = {8.5, 10.5, 12.5, 14.5, 16.5};

public:
    template <typename T>
    static void printTable(std::vector<T> &spins, std::vector<T> &energyExp, std::vector<T> &energyTh, paramSet &params, int choice)
    {
        const std::string file = "../output/energies.out";
        std::ofstream out(file);
        //only work for equal arrayss
        if (spins.size() != energyExp.size() || energyExp.size() != energyTh.size())
        {
            return;
        }
        if (choice == 1)
        {
            std::cout << "Comaprison between experiment and theory with ENSDF data"
                      << "\n";
            out << "Comaprison between experiment and theory with ENSDF data"
                << "\n";
        }
        else
        {
            std::cout << "Comaprison between experiment and theory with MATTA el al data"
                      << "\n";
            out << "Comaprison between experiment and theory with MATTA el al data"
                << "\n";
        }

        std::cout << "Results for the set of parameters: "
                  << "\n";
        out << "Results for the set of parameters: "
            << "\n";
        std::cout << "A1= " << params.I1 << " A2= " << params.I2 << " A3= " << params.I3 << " theta= " << params.theta << "\n";
        out << "A1= " << params.I1 << " A2= " << params.I2 << " A3= " << params.I3 << " theta= " << params.theta << "\n";
        std::cout << "Spin [hbar]   "
                  << "E_exp [MeV]   "
                  << "E_th [MeV]"
                  << "\n";
        out << "Spin [hbar]   "
            << "E_exp [MeV]   "
            << "E_th [MeV]"
            << "\n";
        for (int i = 0; i < spins.size(); ++i)
        {
            std::cout << spins.at(i) << " " << energyExp.at(i) << " " << energyTh.at(i) << "\n";
            out << spins.at(i) << " " << energyExp.at(i) << " " << energyTh.at(i) << "\n";
        }
        auto rms = RMS_Calculation(energyExp, energyTh);
        std::cout << "The RMS is: " << rms << "\n";
        out << "The RMS is: " << rms << "\n";
    }
    static void unitfySets(std::vector<double> &set1, std::vector<double> &set2, std::vector<double> &destination);
    std::vector<double> generateTheoreticalData();
    static double RMS_Calculation(std::vector<double> &v1, std::vector<double> &v2);
};

#endif // ENERGYTEST_HH
