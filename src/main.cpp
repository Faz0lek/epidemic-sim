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

struct State
{
    double S; // susceptible
    double I; // infected
    double D; // diagnosed
    double A; // ailing - symptomatic, infected, undetected
    double R; // recognized - detected
    double T; // threatened - acutely symptomatic
    double H; // healed
    double E; // extinct
};

struct Parameters
{
    // transmission rates
    double alf;
    double bet;
    double gam;
    double del;
    
    // probability rate of detection
    double eps;
    double the;

    // probability rate of infected subject developing clinically relevat symptoms
    // comparable in absence of specific treatment
    double zet;
    double eta;

    // rate of infected subject developing life-threatening symptoms
    // comparable
    double my;
    double ny;

    // mortality rate
    double tau;

    // rate of recovery
    double lam;
    double kap;
    double ksi;
    double ro;
    double sig;
};

// c - current state
// p - parameters
// n - next state
void sidarthe(State c, Parameters p, State* n)
{
    n->S = c.S - c.S * ( p.alf * c.I + p.bet * c.D + p.gam * c.A + p.del * c.R);
    n->I = c.I + c.S * ( p.alf * c.I + p.bet * c.D + p.gam * c.A + p.del * c.R) - ( p.eps + p.zet + p.lam) * c.I;
    n->D = c.D + p.eps * c.I - ( p.eta + p.ro ) * c.D;
    n->A = c.A + p.zet * c.I - ( p.the + p.my + p.kap) * c.A;
    n->R = c.R + p.eta * c.D + p.the * c.A - ( p.ny + p.ksi ) * c.R;
    n->T = c.T + p.my * c.A + p.ny * c.R - ( p.sig + p.tau ) * c.T;
    n->H = c.H + p.lam * c.I + p.ro * c.D + p.kap * c.A + p.ksi * c.R + p.sig * c.T;
    n->E = c.E + p.tau * c.T;
}


int main(int argc, char* argv[])
{

    State it0;
    it0.I = 200/(60e6);
    it0.D = 20/(60e6);
    it0.A = 1/(60e6);
    it0.R = 2/(60e6);
    it0.T = 0;
    it0.H = 0;
    it0.E = 0;
    it0.S = 1 - it0.I - it0.D - it0.A - it0.R - it0.T - it0.H - it0.E;

    Parameters ip;
    ip.alf = 0.570;
    ip.bet = ip.del = 0.011;
    ip.gam = 0.456;
    ip.eps = 0.171;
    ip.the = 0.371;
    ip.zet = ip.eta = 0.125;
    ip.my = 0.017;
    ip.ny = 0.027;
    ip.tau = 0.01;
    ip.lam = ip.ro = 0.034;
    ip.kap = ip.ksi = ip.sig = 0.017;

    State it1;

    std::cout << "S" << " = " << it0.S << std::endl;
    std::cout << "I" << " = " << it0.I << std::endl;

    for(int i = 0; i <= 100; i++)
    {
        sidarthe(it0, ip, &it1);

        std::cout << "----------- ITERACE " << i << " -----------" << std::endl;
        std::cout << "soucet" << " = " << it1.S + it1.I + it1.D + it1.A + it1.R + it1.T + it1.H + it1.E << std::endl;
        std::cout << "S" << " = " << it1.S << std::endl;
        std::cout << "I" << " = " << it1.I << std::endl;
        std::cout << "D" << " = " << it1.D << std::endl;
        std::cout << "A" << " = " << it1.A << std::endl;
        std::cout << "R" << " = " << it1.R << std::endl;
        std::cout << "T" << " = " << it1.T << std::endl;
        std::cout << "H" << " = " << it1.H << std::endl;
        std::cout << "E" << " = " << it1.E << std::endl;

        it0 = it1;
        /*s_n = s_prev - (r * s_prev * i_prev * delta);
        i_n = i_prev + (((r * s_prev * i_prev) - (a * i_prev)) * delta);
        r_n = r_prev + (a * i_prev * delta);

        std::cout << "----------- ITERACE " << i << " -----------" << std::endl;
        std::cout << "s" << " = " << s_n << std::endl;
        std::cout << "i" << " = " << i_n << std::endl;
        std::cout << "r" << " = " << r_n << std::endl;

        s_prev = s_n;
        i_prev = i_n;
        r_prev = r_n;
        */
    }

    return 0;
}