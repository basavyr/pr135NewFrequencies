#ifndef EXPERIMENTALDATA_HH
#define EXPERIMENTALDATA_HH

#include <vector>
#include <iostream>
#include <utility>
#include <memory>
#include <string>

class ExpData_ENSDF
{
public:
    //container which holds the entire experimental energies
    std::vector<double> energiesExp;
    //container which holds the entire set of spins
    std::vector<double> spins;

public:
    //STATIC CONTAINERS WHICH HOLD THE ENSDF EXPERIMENTAL DATA
    //CONTAINERS ARE INITIALIZED BEFORE THE PROGRAM STARTS
    //THE CONTAINERS ARE CREATED WITH THE CORRESPONDING INIT FUNCTIONS
    static std::vector<double> yrastExp;

    //STATIC CONTAINERS WHICH HOLD THE ENSDF EXPERIMENTAL DATA
    //CONTAINERS ARE INITIALIZED BEFORE THE PROGRAM STARTS
    //THE CONTAINERS ARE CREATED WITH THE CORRESPONDING INIT FUNCTIONS
    static std::vector<double> wobbExp;

    //STATIC CONTAINERS WHICH HOLD THE ENSDF EXPERIMENTAL DATA
    //CONTAINERS ARE INITIALIZED BEFORE THE PROGRAM STARTS
    //THE CONTAINERS ARE CREATED WITH THE CORRESPONDING INIT FUNCTIONS
    static std::vector<double> spin1;

    //STATIC CONTAINERS WHICH HOLD THE ENSDF EXPERIMENTAL DATA
    //CONTAINERS ARE INITIALIZED BEFORE THE PROGRAM STARTS
    //THE CONTAINERS ARE CREATED WITH THE CORRESPONDING INIT FUNCTIONS
    static std::vector<double> spin2;

public:
    //constructor
    ExpData_ENSDF();
    //destructor
    ~ExpData_ENSDF();

public:
    //INIT FUNCTION FOR THE FIRST SPIN SET
    template <typename T>
    static std::vector<T> init_spin1()
    {
        //Containers to hold the experimental data from ENSDF
        //Spins from the first band. YRAST exp band
        std::vector<double> dataExp_spin1 = {7.5, 9.5, 11.5, 13.5, 15.5, 17.5, 19.5, 21.5, 23.5, 25.5};
        std::vector<T> directory;
        for (auto index = 0; index < dataExp_spin1.size(); ++index)
        {
            directory.emplace_back(std::move(dataExp_spin1.at(index)));
        }
        return directory;
    }

    //INIT FUNCTION FOR THE SECOND SPIN SET
    template <typename T>
    static std::vector<T> init_spin2()
    {
        //Containers to hold the experimental data from ENSDF
        //Spins from the first band. YRAST exp band
        std::vector<double> dataExp_spin2 = {8.5, 10.5, 12.5, 14.5, 16.5};
        std::vector<T> directory;
        for (auto index = 0; index < dataExp_spin2.size(); ++index)
        {
            directory.emplace_back(std::move(dataExp_spin2.at(index)));
        }
        return directory;
    }

    //INIT FUNCTION FOR THE YRAST ENERGIES
    template <typename T>
    static std::vector<T> init_yrast()
    {
        //Containers to hold the experimental data from ENSDF
        //Spins from the first band. YRAST exp band
        std::vector<double> dataExp_energy1 = {0.37277, 1.03284, 1.88684, 2.88674, 3.96174, 4.80574, 5.63974,
                                               6.52174, 7.44474, 8.35794};

        std::vector<T> directory;
        for (auto index = 0; index < dataExp_energy1.size(); ++index)
        {
            directory.emplace_back(std::move(dataExp_energy1.at(index)));
        }
        return directory;
    }

    //INIT FUNCTION FOR THE WOBBLING ENERGIES
    template <typename T>
    static std::vector<T> init_wobbling()
    {
        //Containers to hold the experimental data from ENSDF
        //Spins from the first band. YRAST exp band
        std::vector<double> dataExp_energy2 = {1.07524, 1.80044, 2.64294, 3.59894, 4.71094};

        std::vector<T> directory;
        for (auto index = 0; index < dataExp_energy2.size(); ++index)
        {
            directory.emplace_back(std::move(dataExp_energy2.at(index)));
        }
        return directory;
    }

    static void generateDataSet(std::vector<double> &set1, std::vector<double> &set2, std::vector<double> &destination);
};

#endif // EXPERIMENTALDATA_HH
