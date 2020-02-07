#include "../include/energyFormulae.hh"

double EnergyFormulas::j_Component(int k, double theta)
{
    if (k == 1)
        return j_Oddspin * cos(theta * PI / 180.0);
    return j_Oddspin * sin(theta * PI / 180.0);
}

double EnergyFormulas::inertiaFactor(double momentOfInertia)
{
    if (momentOfInertia)
        return static_cast<double>(1.0 / (2.0 * momentOfInertia));
    return 0;
}