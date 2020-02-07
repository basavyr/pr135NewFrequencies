#include "../include/bandAdjustment.hh"


void BandAdjuster::subtractFromData(std::vector<double> &source, std::string &side, double subtractQuanta)
{
    if (side == "left")
        subtractDataLeft(source, subtractQuanta);
    if (side == "right")
    {
        subtractDataRight(source, subtractQuanta);
    }
    else
    {
        return;
    }
}

void BandAdjuster::subtractDataLeft(std::vector<double> &source, double subtractQuanta)
{
    //only work if array is non-EMPTY
    if (source.size())
    {
        auto halfsize = static_cast<size_t>(source.size() / 2);
        for (int i = 0; i < halfsize; ++i)
        {
            source.at(i) = source.at(i) - subtractQuanta;
        }
    }
    else
    {
        return;
    }
}
void BandAdjuster::subtractDataRight(std::vector<double> &source, double subtractQuanta)
{
    //only work if array is non-EMPTY
    if (source.size())
    {
        auto halfsize = static_cast<size_t>(source.size() / 2);
        for (int i = halfsize; i < source.size(); ++i)
        {
            source.at(i) = source.at(i) - subtractQuanta;
        }
    }
    else
    {
        return;
    }
}