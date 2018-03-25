//
// Created by Daniel Ghandahari on 2017-09-25.
//

#pragma once

#include <vector>


class DefiniteIntegrator {

private:
    int threads;
    int trapezes;


public:
    DefiniteIntegrator(int threads, long trapezes) {
        this->threads = threads;
        this->trapezes = trapezes;
    }


    std::vector<long> loadBalanceAlgorithm(int amountOfThreads, long amountOfTrapezes);
    static void sumOfTrapezes(long amountOfTrapezes, float xCoordinate, float deltaX);
    static float mathFuncToBeCalculated(float x);
    static float calculateTrapezeArea(float x, float deltaX);


};


