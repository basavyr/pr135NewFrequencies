#ifndef ENERGYFORMULAE_HH
#define ENERGYFORMULAE_HH

#include <cmath>
#include <vector>
#include <iostream>

class EnergyFormulas
{
public:
    EnergyFormulas();
    ~EnergyFormulas();

public:
    static constexpr double j_Oddspin = 5.5;
    static constexpr double PI = 3.14159265358979;
    static double j_Component(int k, double theta);
    static double inertiaFactor(double momentOfInertia);
    static double omega_New(double spin, double i1, double i2, double i3, double theta);
    static double omegaPrime_New(double spin, double i1, double i2, double i3, double theta);
    static double energyExpression(int N, double spin, double i1, double i2, double i3, double theta);
    static double minimumHamiltonian(double spin, double i1, double i2, double i3, double theta);
};

#endif // ENERGYFORMULAE_HH
