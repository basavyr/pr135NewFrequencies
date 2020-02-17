#include <iostream>
#include <vector>
#include <fstream>
#include "../include/minimalParams.hh"
#include "../include/energyFormulae.hh"
#include "../include/rootMeanSquare.hh"
#include "../include/experimentalData.hh"
#include "../include/bandAdjustment.hh"
#include "../include/energyTest.hh"

void arrayPrinter(std::vector<double> &vec)
{
    if (vec.size())
    {
        std::cout << " { ";
        for (int i = 0; i < vec.size(); ++i)
        {
            if (i == vec.size() - 1)
            {
                std::cout << vec.at(i) << " };\n";
            }
            else
            {
                std::cout << vec.at(i) << " , ";
            }
        }
    }
}

void arrayPrinterToFile(std::string &file, std::vector<double> &array)
{
    if (array.size())
    {
        std::ofstream out(file);
        out << "{ ";
        for (int i = 0; i < array.size(); ++i)
        {
            if (i == array.size() - 1)
            {
                out << array.at(i) << " };\n";
            }
            else
            {
                out << array.at(i) << " , ";
            }
        }
    }
}

template <typename T>
void testSubtract(T &dataExp)
{
    std::string left = "left";
    std::string right = "right";

    //YRAST LEFT
    auto test = dataExp->yrastExp;
    std::cout << "Container BEFORE subtraction"
              << "\n";
    arrayPrinter(test);
    BandAdjuster::subtractFromData(test, left, 0.1);
    std::cout << "Container AFTER subtraction to the LEFT"
              << "\n";
    arrayPrinter(test);
    //YRAST RIGHT
    test = dataExp->yrastExp;
    std::cout << "Container AFTER subtraction to the RIGHT"
              << "\n";
    BandAdjuster::subtractFromData(test, right, 0.1);
    arrayPrinter(test);

    //WOBBLING LEFT
    test = dataExp->wobbExp;
    std::cout << "Container BEFORE subtraction"
              << "\n";
    arrayPrinter(test);
    BandAdjuster::subtractFromData(test, left, 0.1);
    std::cout << "Container AFTER subtraction to the LEFT"
              << "\n";
    arrayPrinter(test);
    //WOBBLING RIGHT
    test = dataExp->wobbExp;
    arrayPrinter(test);
    std::cout << "Container AFTER subtraction to the RIGHT"
              << "\n";
    BandAdjuster::subtractFromData(test, right, 0.1);
    arrayPrinter(test);
}

void PlotMaker(std::vector<double> &x, std::vector<double> &ydata1, std::vector<double> &ydata2)
{
    std::cout << x.at(0);
    std::cout << ydata1.at(0);
    std::cout << ydata2.at(0);
    // std::string file = "../output/plot.dat";
    // {
    //     std::ofstream out(file);
    //     out << "hey";
    // }
}

void app()
{
    //plot files
    std::string plotBand1 = "../output/yrast.dat";
    std::string plotBand2 = "../output/wobbling.dat";
    std::vector<double> yrastBand;
    std::vector<double> wobblingBand;
    auto dataExp = std::make_unique<ExpData_ENSDF>();
    auto minparams = std::make_unique<MinimalParameters>();
    auto rms = std::make_unique<RootMeanSquare>();
    MinimalParameters::minSetOfParams bestParams;
    minparams->searchMinimum_NULL_Theta(dataExp->energiesExp, bestParams);
    auto xx = RootMeanSquare::generateTheoreticalData(bestParams.I1, bestParams.I2, bestParams.I3, bestParams.theta);
    std::cout << "***********************************"
              << "\n";
    MinimalParameters::paramPrinter(bestParams);
    std::cout << "***********************************"
              << "\n";
    std::cout << "EXP"
              << "\n";
    arrayPrinter(dataExp->energiesExp);
    std::cout << "TH"
              << "\n";
    arrayPrinter(xx);
    //generated the subsets of data to be plotted
    RootMeanSquare::generateSubsets(xx, yrastBand, wobblingBand);
    BandAdjuster::PlotMaker(plotBand1, dataExp->spin1, dataExp->yrastExp, yrastBand);
    BandAdjuster::PlotMaker(plotBand2, dataExp->spin2, dataExp->wobbExp, wobblingBand);

    //gcalculate the deviations from experimental data
    // auto deltas = RootMeanSquare::deltaArray(dataExp->energiesExp, xx);
    // std::cout << RootMeanSquare::RMS_fromAdjustQuantas(1, 1);
    // std::cout << RootMeanSquare::rms_fromFitParameters(0.00341388, 0.0733665, 3.25347, 30.2246);
    // arrayPrinter(deltas);

    //generate the new adjusted experimental data
    /* auto adjustedEnergy = dataExp->energiesExp;
    BandAdjuster::subtractQuantaFromContainer(adjustedEnergy, 0, deltas.at(0));
    BandAdjuster::subtractQuantaFromContainer(adjustedEnergy, 1, deltas.at(0));
    BandAdjuster::subtractQuantaFromContainer(adjustedEnergy, 2, deltas.at(0));
    BandAdjuster::subtractQuantaFromContainer(adjustedEnergy, adjustedEnergy.size() - 1, deltas.at(deltas.size() - 1));
    arrayPrinter(adjustedEnergy);
    MinimalParameters::minSetOfParams bestParams_Adjusted;

    //recalculate RMS with the new adjusted set
    minparams->searchMinimum(adjustedEnergy, bestParams_Adjusted);
    minparams->paramPrinter(bestParams_Adjusted);
    auto xxx = RootMeanSquare::generateTheoreticalData(101, 6, 121, -30);
    std::cout << RootMeanSquare::RMS_calculation(dataExp->energiesExp, xxx) << "\n"; */
}

void energyTest(int choice)
{
    double I1 = 129.0;
    double I2 = 3;
    double I3 = 52;
    double theta = -160;
    //use 1 for ENSDF data
    //use 2 for MATTA et al data
    // int choice = 1;
    auto test = std::make_unique<EnergyTest>(I1, I2, I3, theta, choice);
}

int main()
{
    // app();
    energyTest(1);
    energyTest(2);
}