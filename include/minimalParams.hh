#ifndef MINIMALPARAMS_HH
#define MINIMALPARAMS_HH

#include <vector>
#include <iostream>
#include <utility>
#include <memory>
#include <string>
#include <cmath>
#include <chrono>
#include <ctime>
#include <fstream>

class MinimalParameters
{
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;

public:
    MinimalParameters();
    ~MinimalParameters();
    void measureTime();
    struct minSetOfParams
    {
        double I1, I2, I3;
        double A1, A2, A3;
        double theta;
        double RMS;
        minSetOfParams()
        {
            I1 = 0.0;
            I2 = 0.0;
            I3 = 0.0;
            A1 = 0.0;
            A2 = 0.0;
            A3 = 0.0;
            theta = 0.0;
            RMS = 123456789;
        }
        ~minSetOfParams()
        {
        }
    };
    struct paramLimits
    {
        const double I_left = 1.0;
        const double I_right = 130.0;
        const double I_step = 5;
        const double I1_left=120;
        const double I2_left=1;
        const double I3_left=15;
        const double I1_right=130;
        const double I2_right=10;
        const double I3_right=25;
        const double theta_left = -150;
        const double theta_right = 130;
        const double theta_step = 0.1;
    };

    static void searchMinimum(std::vector<double> &exp, minSetOfParams &bestParams);
    static void paramPrinter(minSetOfParams &params);
    static void searchMinimum_NULL_Theta(std::vector<double> &exp, minSetOfParams &bestParams);
};

#endif // MINIMALPARAMS_HH
