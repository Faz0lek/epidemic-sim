/**
 * @file main.cpp
 * @author Martin Kostelník (xkoste12), Radek Švec (xsvecr01)
 * @brief IMS 2020 Project main file
 * @date 2020-12-07
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <iostream>
#include <iomanip>

/**
 * @brief Disease contains data about a specific disease in a specific country
 * 
 */
struct Disease
{
    // Transmission rates (probability of disease transmission in a single contact
    // multiplied by the average number of contacts per person per day)
    double alpha;   // Between S and I
    double beta;    // Between S and D
    double gamma;   // Between S and A
    double delta;   // Between S and R
    
    // Probability rate of detection
    double epsilon; // For asymptomatic
    double theta;   // For symptomatic

    // Probability rate of infected subject developing clinically relevat symptoms
    // Comparable in absence of specific treatment
    double zeta;    // Not aware of being infected
    double eta;     // Aware of being infected

    // Rate of infected subject developing life-threatening symptoms
    // Comparable in absence of specific treatment
    double my;  // Undetected
    double ny;  // Detected

    // Mortality rate
    double tau;

    // Rate of recovery
    double lambda;  // Infected
    double kappa;   // Diagnosed
    double ksi;     // Ailing
    double ro;      // Recognized
    double sigma;   // Threatened
};

/**
 * @brief This struct describes used model for simulations
 * 
 */
struct SIDARTHE
{
    double S; // Susceptible
    double I; // Infected   (asymptomatic,  infected,   undetected)
    double D; // Diagnosed  (asymptomatic,  infected,   detected)
    double A; // Ailing     (symptomatic,   infected,   undetected)
    double R; // Recognized (symptomatic,   infected,   detected)
    double T; // Threatened (acutely symptomatic, infected, detected)
    double H; // Healed
    double E; // Extinct

    SIDARTHE();

    SIDARTHE(const double I0,
             const double D0, const double A0,
             const double R0, const double T0,
             const double H0, const double E0) : I(I0), D(D0), A(A0), R(R0), T(T0), H(H0), E(E0)
    {
        S = 1 - I - D - A - R - T - H - E;

        std::cout << std::fixed;
        std::cout << std::setprecision(2);
    }

    void predict(const Disease& d, const size_t days)
    {
        double S_prev = S,
               I_prev = I,
               D_prev = D,
               A_prev = A,
               R_prev = R,
               T_prev = T;

        for (size_t t = 1; t <= days; t++)
        {
            S_prev = S;
            I_prev = I;
            D_prev = D;
            A_prev = A;
            R_prev = R;
            T_prev = T;

            S += -S_prev * ( d.alpha * I_prev + d.beta * D_prev + d.gamma * A_prev + d.delta * R_prev);
            I += S_prev * ( d.alpha * I_prev + d.beta * D_prev + d.gamma * A_prev + d.delta * R_prev)
                 - (d.epsilon + d.zeta + d.lambda) * I_prev;
            D += d.epsilon * I_prev - (d.eta + d.ro) * D_prev;
            A += d.zeta * I_prev - (d.theta + d.my + d.kappa) * A_prev;
            R += d.eta * D_prev + d.theta * A_prev - (d.ny + d.ksi) * R_prev;
            T += d.my * A_prev + d.ny * R_prev - ( d.sigma + d.tau ) * T_prev;
            H += d.lambda * I_prev + d.ro * D_prev + d.kappa * A_prev + d.ksi * R_prev + d.sigma * T_prev;
            E += d.tau * T_prev;

            printStats(t);
        }
    }

    void printStats(const size_t day) const 
    {
        std::cout << "----------- DAY " << day << " -----------" << std::endl;
        std::cout << "S" << " = " << (S < 0.1 ? " " : "") << S * 100 << " %" << std::endl;
        std::cout << "I" << " = " << (I < 0.1 ? " " : "") << I * 100 << " %" << std::endl;
        std::cout << "D" << " = " << (D < 0.1 ? " " : "") << D * 100 << " %" << std::endl;
        std::cout << "A" << " = " << (A < 0.1 ? " " : "") << A * 100 << " %" << std::endl;
        std::cout << "R" << " = " << (R < 0.1 ? " " : "") << R * 100 << " %" << std::endl;
        std::cout << "T" << " = " << (T < 0.1 ? " " : "") << T * 100 << " %" << std::endl;
        std::cout << "H" << " = " << (H < 0.1 ? " " : "") << H * 100 << " %" << std::endl;
        std::cout << "E" << " = " << (E < 0.1 ? " " : "") << E * 100 << " %" << std::endl;
    }
};

int main(int argc, char* argv[])
{
    Disease COVID = {0.57, 0.011, 0.456, 0.011, 0.171, 0.371, 0.125, 0.125, 0.017, 0.027, 0.01, 0.034, 0.017, 0.017, 0.034, 0.017};
    SIDARTHE Italy = {200/(60e6), 20/(60e6), 1/(60e6), 2/(60e6), 0, 0, 0};

    const size_t DAYS = 350;

    Italy.predict(COVID, DAYS);

    return 0;
}