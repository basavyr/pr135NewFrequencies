#ifndef ROOTMEANSQUARE_HH
#define ROOTMEANSQUARE_HH

#include <vector>
#include <cmath>

class RootMeanSquare
{
public:
    static double RMS_calculation(std::vector<double> &exp, std::vector<double> &th);
    static std::vector<double> generateTheoreticalData(double I1, double I2, double I3, double theta);
    static void generateSubsets(std::vector<double> &source, std::vector<double> &set1, std::vector<double> &set2);
};

#endif // ROOTMEANSQUARE_HH
