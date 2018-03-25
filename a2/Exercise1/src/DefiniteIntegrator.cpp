//
// Created by Daniel Ghandahari on 2017-09-25.
//

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <cstring>
#include <functional>
#include "DefiniteIntegrator.h"



float trapezeSumArea = 0;

std::vector<long> DefiniteIntegrator::loadBalanceAlgorithm(int amountOfThreads, long amountOfTrapezes){
    std::vector<long> returnVec = std::vector<long>();

    long trapezes = amountOfTrapezes;
    int threads = amountOfThreads;

    for (int i = 0; i < amountOfThreads; ++i) {
        long trapezesPerThread = trapezes/(long)threads;
        returnVec.push_back(trapezesPerThread);

        trapezes -= trapezesPerThread;
        threads--;
    }

    return returnVec;

}

std::mutex lock;

void DefiniteIntegrator::sumOfTrapezes(long amountOfTrapezes, float xCoordinate, float deltaX){

    float sum;
    float x = xCoordinate;

    for (long i = 0; i < amountOfTrapezes; ++i) {
        sum += calculateTrapezeArea(x, deltaX);
        x += deltaX;
    }

    lock.lock();
    trapezeSumArea += sum;
    lock.unlock();
}

float DefiniteIntegrator::calculateTrapezeArea(float x, float deltaX){
    return ((mathFuncToBeCalculated(x) + mathFuncToBeCalculated(x+deltaX)) / 2) * deltaX;
}

float DefiniteIntegrator::mathFuncToBeCalculated(float x){
    float xPowerToTwo = x*x;
    float denominator = 1.0000 + xPowerToTwo;

    float ret = 4.0000 / denominator;
    return ret;
}



int main(int argc, char** argv) {

    if(!std::strcmp(argv[1], "-h") && argc == 2) {
        std::cout << "Run the program by typing ./LabAssignment2 [Amount of Threads] [Amount of Trapezes]" << std::endl;
        std::cout << std::endl;
        std::cout << "To compile the program, type \"make\" (in this directory, where you are standing)" << std::endl;
        exit(0);
    }

    if(argc != 3){
        std::cout << "Incorrect amount of arguments given" << std::endl;
        exit(-1);
    }
    int threadsArg = 0;
    long trapezeArg = 0;
    try {
        threadsArg = std::stoi(argv[1]);
        trapezeArg = std::stol(argv[2]);
    } catch(std::invalid_argument e) {
        std::cout << "Give an integer as argument!" << std::endl;
        exit(-1);
    }



    DefiniteIntegrator definiteIntegrator = DefiniteIntegrator(threadsArg, trapezeArg);

    std::vector<long> loadBalance = definiteIntegrator.loadBalanceAlgorithm(threadsArg, trapezeArg);

    printf("Amount of threads: %d\nAmount of trapezes: %ld \n\n", threadsArg, trapezeArg);
    for (int i = 0; i < loadBalance.size(); ++i) {
        printf("Thread %d computes %ld trapezes.\n", i, loadBalance[i]);
    }

    auto startTime = std::chrono::system_clock::now();

    std::vector<std::thread> processes = std::vector<std::thread>();

    float xCoordinate = 0.0000;
    float deltaX = 1.0000/trapezeArg;
    for(long trapezesPerThread : loadBalance) {

      processes.push_back(std::thread(&(definiteIntegrator.sumOfTrapezes), trapezesPerThread, xCoordinate, deltaX));
        xCoordinate += deltaX * trapezesPerThread;
    }

    for (int i = 0; i < processes.size(); ++i) {
        printf("Thread with thread id: %d finished!\n", processes[i].get_id());
        processes[i].join();
    }

    std::chrono::duration<double> runtime = (std::chrono::system_clock::now() - startTime);

    printf("\nThe final sum: %f\nThe measured runtime: %f", trapezeSumArea, runtime);

    return 0;
}
