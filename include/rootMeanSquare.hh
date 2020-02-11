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
    static std::vector<double> deltaArray(std::vector<double> &v1, std::vector<double> &v2);
    static double RMS_fromAdjustQuantas(double quanta1, double quanta2);
    static double rms_fromFitParameters(double a1, double a2, double a3, double theta);
};

#endif // ROOTMEANSQUARE_HH
