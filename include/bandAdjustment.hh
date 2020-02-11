#ifndef BAND_ADJUSTMENT_HH
#define BAND_ADJUSTMENT_HH

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <utility>

class BandAdjuster
{
public:
    //generate a single data set from two subsets (data )
    static void generateDataSet(std::vector<double> &set1, std::vector<double> &set2, std::vector<double> &destination);

    //generate a new energy container with experimental data
    //container is created by subtracting a constant value from any portion of the set
    //for addition of value, the quanta can be negative
    static void subtractFromData(std::vector<double> &source, std::string &side, double subtractQuanta);
    static void subtractDataLeft(std::vector<double> &source, double subtractQuanta);
    static void subtractDataRight(std::vector<double> &source, double subtractQuanta);
    static void PlotMaker(const std::string &name, std::vector<double> &spins, std::vector<double> &band1, std::vector<double> &band2);
    static void subtractQuantaFromContainer(std::vector<double> &source, int position, double subtractQuanta);
    static std::vector<double> mobileSubtractor(std::vector<double> &source, int startPosition, int endPosition, double adjustQuanta);
};

#endif // BAND_ADJUSTMENT_HH
