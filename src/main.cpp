#include <iostream>

#include "../include/minimalParams.hh"
#include "../include/energyFormulae.hh"
#include "../include/rootMeanSquare.hh"
#include "../include/experimentalData.hh"
#include "../include/bandAdjustment.hh"

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

int main()
{
    auto dataExp = std::make_unique<ExpData_ENSDF>();
    testSubtract(dataExp);
    // std::cout<<ExpData_ENSDF::spin1.at(1);
}