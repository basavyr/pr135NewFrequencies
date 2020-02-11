#include "../include/minimalParams.hh"
#include "../include/rootMeanSquare.hh"
#include "../include/experimentalData.hh"
#include "../include/energyFormulae.hh"

MinimalParameters::MinimalParameters()
{
    startTime = std::chrono::high_resolution_clock::now();
}

MinimalParameters::~MinimalParameters()
{
    measureTime();
}

void MinimalParameters::measureTime()
{
    auto now = std::chrono::high_resolution_clock::now();
    auto endPoint = std::chrono::time_point_cast<std::chrono::microseconds>(now).time_since_epoch().count();
    auto startPoint = std::chrono::time_point_cast<std::chrono::microseconds>(startTime).time_since_epoch().count();
    auto durationms = static_cast<double>((endPoint - startPoint) * 0.001);
    std::cout << "The program finished succesfully \n";
    std::cout << "Process took " << durationms << " ms..."
              << "\n";
}

void MinimalParameters::searchMinimum(std::vector<double> &exp, minSetOfParams &bestParams)
{
    //setting the limits for the free parameters
    paramLimits limits;
    //making a container for storing all the params in a stack
    std::vector<minSetOfParams> param_stack;
    //store the rms values
    std::vector<double> RMS_stack;

    int index = 0;
    for (double I1 = limits.I_left; I1 <= limits.I_right; I1 += limits.I_step)
    {
        for (double I2 = limits.I_left; I2 <= limits.I_right; I2 += limits.I_step)
        {
            for (double I3 = limits.I_left; I3 <= limits.I_right; I3 += limits.I_step)
            {
                for (double theta = limits.theta_left; theta <= limits.theta_right; theta += limits.theta_step)
                {
                    auto th = RootMeanSquare::generateTheoreticalData(I1, I2, I3, theta);
                    auto currentChi = RootMeanSquare::RMS_calculation(exp, th);
                    if (!isnan(currentChi))
                    {
                        RMS_stack.emplace_back(currentChi);
                        param_stack.emplace_back(minSetOfParams());
                        param_stack.at(index).I1 = I1;
                        param_stack.at(index).I2 = I2;
                        param_stack.at(index).I3 = I3;
                        param_stack.at(index).A1 = static_cast<double>(1.0 / (2.0 * I1));
                        param_stack.at(index).A2 = static_cast<double>(1.0 / (2.0 * I2));
                        param_stack.at(index).A3 = static_cast<double>(1.0 / (2.0 * I3));
                        param_stack.at(index).theta = theta;
                        param_stack.at(index).RMS = currentChi;
                        index++;
                    }
                }
            }
        }
    }
    auto minIndex = std::distance(RMS_stack.begin(), std::min_element(RMS_stack.begin(), RMS_stack.end()));
    bestParams.I1 = param_stack.at(minIndex).I1;
    bestParams.I2 = param_stack.at(minIndex).I2;
    bestParams.I3 = param_stack.at(minIndex).I3;
    bestParams.A1 = param_stack.at(minIndex).A1;
    bestParams.A2 = param_stack.at(minIndex).A2;
    bestParams.A3 = param_stack.at(minIndex).A3;
    bestParams.theta = param_stack.at(minIndex).theta;
    bestParams.RMS = param_stack.at(minIndex).RMS;
}

void MinimalParameters::paramPrinter(minSetOfParams &params)
{
    std::string paramFile = "../output/params.dat";
    std::ofstream out(paramFile);
    std::cout << "I1= " << params.I1 << " I2= " << params.I2 << " I3= " << params.I3 << " theta= " << params.theta << "\n";
    std::cout << "E_RMS=" << params.RMS << "\n";
    out << "I1= " << params.I1 << " I2= " << params.I2 << " I3= " << params.I3 << " theta= " << params.theta << "\n";
    out << "E_RMS=" << params.RMS << "\n";
}