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
        const double I_step = 10;
        const double theta_left = -180;
        const double theta_right = 180;
        const double theta_step = 10;
    };

    static void searchMinimum(std::vector<double> &exp, minSetOfParams &bestParams);
    void paramPrinter(minSetOfParams &params);
};

#endif // MINIMALPARAMS_HH
