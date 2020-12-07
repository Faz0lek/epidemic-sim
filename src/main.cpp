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
#include <fstream>
#include "string.h"

bool raw = false;

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

    void printStats()
    {
        std::cout << "a = " << alpha << std::endl;
        std::cout << "b = " << beta << std::endl;
        std::cout << "c = " << gamma << std::endl;
        std::cout << "d = " << delta << std::endl;
        std::cout << "e = " << epsilon << std::endl;
        std::cout << "z = " << zeta << std::endl;
        std::cout << "L = " << lambda << std::endl;
        std::cout << "t = " << theta << std::endl;
        std::cout << "n = " << ny << std::endl;
        std::cout << "s = " << sigma << std::endl;
        std::cout << "u = " << tau << std::endl;
        std::cout << "w = " << eta << std::endl;
        std::cout << "r = " << ro << std::endl;
        std::cout << "m = " << my << std::endl;
        std::cout << "k = " << kappa << std::endl;
        std::cout << "i = " << ksi << std::endl;
    }
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

    size_t population;

    SIDARTHE();

    SIDARTHE(const size_t p,
             const double I0, const double D0,
             const double A0, const double R0,
             const double T0, const double H0,
             const double E0) : population(p), I(I0/p), D(D0/p), A(A0/p), R(R0/p), T(T0/p), H(H0/p)
    {
        S = 1 - I - D - A - R - T - H - E;
    }

    void predict(const Disease& d, const size_t start, const size_t end)
    {
        double S_prev = S,
               I_prev = I,
               D_prev = D,
               A_prev = A,
               R_prev = R,
               T_prev = T;

        std::ofstream file("data.txt", std::ofstream::app);
        for (size_t t = start; t <= end; t++)
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

            file << S << " " << I << " " << D << " " << A << " " << R << " " << T << " " << H << " " << E << std::endl;
        }
        file.close();
    }

    void printStats()
    {
        std::cout << std::fixed;
        std::cout << std::setprecision(4);
        std::cout << "----------------- RESULTS -----------------" << std::endl;
        std::cout << "S" << " = " << (S < 0.1 ? " " : "") << S * 100 << " % (" << (int)(S * population) << "/" << population << ")" << std::endl;
        std::cout << "I" << " = " << (I < 0.1 ? " " : "") << I * 100 << " % (" << (int)(I * population) << "/" << population << ")" << std::endl;
        std::cout << "D" << " = " << (D < 0.1 ? " " : "") << D * 100 << " % (" << (int)(D * population) << "/" << population << ")" << std::endl;
        std::cout << "A" << " = " << (A < 0.1 ? " " : "") << A * 100 << " % (" << (int)(A * population) << "/" << population << ")" << std::endl;
        std::cout << "R" << " = " << (R < 0.1 ? " " : "") << R * 100 << " % (" << (int)(R * population) << "/" << population << ")" << std::endl;
        std::cout << "T" << " = " << (T < 0.1 ? " " : "") << T * 100 << " % (" << (int)(T * population) << "/" << population << ")" << std::endl;
        std::cout << "H" << " = " << (H < 0.1 ? " " : "") << H * 100 << " % (" << (int)(H * population) << "/" << population << ")" << std::endl;
        std::cout << "E" << " = " << (E < 0.1 ? " " : "") << E * 100 << " % (" << (int)(E * population) << "/" << population << ")" << std::endl;
    }
};

void italy(int max)
{
    // day 1 - 4
    Disease it_0 = {0.57, 0.011, 0.456, 0.011, 0.171, 0.371, 0.125, 0.125, 0.017, 0.027, 0.01, 0.034, 0.017, 0.017, 0.034, 0.017};
    // day 5 - 12
    Disease it_1 = it_0;
    it_1.alpha = 0.422;
    it_1.beta = it_1.delta = 0.0057;
    it_1.gamma = 0.285;
    // day 13 - 22
    Disease it_2 = it_1;
    it_2.epsilon = 0.143;
    // day 23 - 28
    Disease it_3 = it_2;
    it_3.alpha = 0.360;
    it_3.beta = it_3.delta = 0.005;
    it_3.gamma = 0.2;
    it_3.zeta = it_3.eta = 0.034;
    it_3.my = 0.008;
    it_3.ny = 0.015;
    it_3.lambda = 0.08;
    it_3.ro = it_3.kappa = it_3.ksi = it_3.sigma = 0.017;
    // day 29 - 38
    Disease it_4 = it_3;
    it_4.alpha = 0.21;
    it_4.gamma = 0.11;
    // day 39 -
    Disease it_5 = it_4;
    it_5.epsilon = 0.2;
    it_5.ro = it_5.kappa = it_5.ksi = 0.02;
    it_5.sigma = 0.01;
    it_5.zeta = it_5.eta = 0.025;

    SIDARTHE Italy = {60000000, 200, 20, 1, 2, 0, 0, 0};

    Italy.predict(it_0, 0, 4);
    Italy.predict(it_1, 5, 12);
    Italy.predict(it_2, 13, 22);
    Italy.predict(it_3, 23, 29);
    Italy.predict(it_4, 30, 38);
    Italy.predict(it_5, 39, max);

    Italy.printStats();
}

void czech()
{
    // 01.-17.11. R 0.87058824
    // 18.-24.11. R 0.74285714
    // 25.-29.11. R 0.8
    // 30.-02.12. R 0.83333333
    // 03.-05.12. R 0.9

    // ke dni 5.12.2020
    Disease cz_0 = {0.57, 0.011, 0.456, 0.011, 0.171, 0.371, 0.125, 0.125, 0.017, 0.027, 0.01, 0.034, 0.017, 0.017, 0.034, 0.017};
    //SIDARTHE Czech = {10690000, 600000, 40201, 20000, 33436, 576, 476685, 8838};
    
    // https://onemocneni-aktualne.mzcr.cz/covid-19
    // ke dni 1.11.2020
    SIDARTHE Czech = {10690000, 100000, 29876, 25000, 80778, 1163, 226059, 3775};

    Czech.predict(cz_0, 1, 100);
}

int main(int argc, char* argv[])
{
    if(argc < 2){
        std::cout << "./ims-proj italy1|italy2|czech" << std::endl;
        return 1;
    }

    std::ofstream file("data.txt", std::ofstream::trunc);
    file.close();

    if(strcmp(argv[1], "italy1") == 0)
    {
        italy(50);
    }
    else if(strcmp(argv[1], "italy2") == 0)
    {
        italy(350);
    }
    else if(strcmp(argv[1], "czech") == 0)
    {
        czech();
    }


    return 0;
}