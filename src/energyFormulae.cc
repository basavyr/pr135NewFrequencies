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

double EnergyFormulas::omegaPrime_New(double spin, double i1, double i2, double i3, double theta)
{
    double a1 = EnergyFormulas::inertiaFactor(i1);
    double a2 = EnergyFormulas::inertiaFactor(i2);
    double a3 = EnergyFormulas::inertiaFactor(i3);
    double j1 = EnergyFormulas::j_Component(1, theta);
    double j2 = EnergyFormulas::j_Component(2, theta);
    auto term1 = (2.0 * spin + 1.0) * (a2 - a1 - (a2 * j2) / spin) + 2.0 * a1 * j1;
    auto term2 = (2.0 * spin + 1.0) * (a3 - a1) + 2.0 * a1 * j1;
    auto term3 = (a3 - a1) * (a2 - a1 - (a2 * j2) / spin);
    auto result = static_cast<double>(sqrt(term1 * term2 - term3));
    if (isnan(result))
        return 6969;
    return result;
}

double EnergyFormulas::omega_New(double spin, double i1, double i2, double i3, double theta)
{
    double a1 = EnergyFormulas::inertiaFactor(i1);
    double a2 = EnergyFormulas::inertiaFactor(i2);
    double a3 = EnergyFormulas::inertiaFactor(i3);
    double j1 = EnergyFormulas::j_Component(1, theta);
    double j2 = EnergyFormulas::j_Component(2, theta);
    auto term1 = (2.0 * spin + 1.0) * (a2 - a1 - (a2 * j2) / spin) - 2.0 * a1 * j1;
    auto term2 = (2.0 * spin + 1.0) * (a3 - a1) - 2.0 * a1 * j1;
    auto term3 = (a3 - a1) * (a2 - a1 - (a2 * j2) / spin);
    auto result = static_cast<double>(sqrt(term1 * term2 - term3));
    if (isnan(result))
        return 6969;
    return result;
}

double EnergyFormulas::minimumHamiltonian(double spin, double i1, double i2, double i3, double theta)
{
    double a1 = EnergyFormulas::inertiaFactor(i1);
    double a2 = EnergyFormulas::inertiaFactor(i2);
    double a3 = EnergyFormulas::inertiaFactor(i3);
    double j1 = EnergyFormulas::j_Component(1, theta);
    double j2 = EnergyFormulas::j_Component(2, theta);
    auto squaredSum = [](auto x, auto y) {
        return static_cast<double>(x * pow(y, 2));
    };
    auto singleParticleSum = squaredSum(a1, j1) + squaredSum(a2, j2);
    auto term1 = a1 * spin * spin + (2.0 * spin + 1.0) * a1 * j1 - spin * a2 * j2;
    auto result = static_cast<double>(term1 + singleParticleSum);
    if (isnan(result))
        return 6969;
    return result;
}

double EnergyFormulas::energyExpression(int N, double spin, double i1, double i2, double i3, double theta)
{
    //dont compute energy if the wobbling frequency and the minimum hamiltonian are invalid numbers
    auto omega = [&](auto spinFake) {
        return omega_New(spinFake, i1, i2, i3, theta);
    };
    auto minHamiltonian = minimumHamiltonian(spin, i1, i2, i3, theta);
    auto e0 = 0.5 * omega(5.5) + minimumHamiltonian(5.5, i1, i2, i3, theta);
    if (omega(spin) == 6969 || minHamiltonian == 6969 || isnan(e0))
        return 6969;
    auto result = static_cast<double>(minHamiltonian + (N + 0.5) * omega(spin) - e0);
    return result;
}
