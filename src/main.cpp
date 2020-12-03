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

int main(int argc, char* argv[])
{
    double delta = 0.14;
    double r = 0.03; 
    double a = 0.07; 
    double s0 = 100; // sensitive
    double i0 = 0.5; // infected
    double r0 = 0; // recovered
    int max_days = 10;
    double s_n, i_n, r_n;

    double s_prev = s0;
    double i_prev = i0;
    double r_prev = r0;


    for(int i = 0; i <= max_days/delta; i++)
    {
        s_n = s_prev - (r * s_prev * i_prev * delta);
        i_n = i_prev + (((r * s_prev * i_prev) - (a * i_prev)) * delta);
        r_n = r_prev + (a * i_prev * delta);

        std::cout << "----------- ITERACE " << i << " -----------" << std::endl;
        std::cout << "s" << " = " << s_n << std::endl;
        std::cout << "i" << " = " << i_n << std::endl;
        std::cout << "r" << " = " << r_n << std::endl;

        s_prev = s_n;
        i_prev = i_n;
        r_prev = r_n;

    }

    return 0;
}