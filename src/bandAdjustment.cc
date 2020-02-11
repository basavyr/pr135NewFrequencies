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

void BandAdjuster::PlotMaker(const std::string &file, std::vector<double> &spins, std::vector<double> &band1, std::vector<double> &band2)
{
    std::ofstream plot(file);
    // stop if arrays have uneqeual sizes
    if (band1.size() != band2.size())
        return;
    for (int i = 0; i < spins.size(); ++i)
    {
        plot << spins.at(i) << " " << band1.at(i) << " " << band2.at(i) << "\n";
    }
}

void BandAdjuster::subtractQuantaFromContainer(std::vector<double> &source, int position, double subtractQuanta)
{
    source.at(position) = source.at(position) - subtractQuanta;
}

std::vector<double> BandAdjuster::mobileSubtractor(std::vector<double> &source, int startPosition, int endPosition, double adjustQuanta)
{
    auto results = source;
    for (int i = startPosition; i < endPosition; ++i)
    {
        results.at(i) = source.at(i) - adjustQuanta;
    }
    return results;
}