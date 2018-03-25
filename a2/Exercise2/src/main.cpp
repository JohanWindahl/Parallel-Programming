#include <iostream>
#include <math.h>
#include <vector>
#include <mutex>
#include <cstring>
#include <thread>


struct number_t {
    long number;
    bool isMarked = false;
};




/*
 * Depending on amountOfThreads, the numbers in vec are equally
 * divided in chunks with the loadBalanceAlgorithm (from Exercise 1).
 * */
std::vector<std::vector<number_t>> createChunks(int amountOfThreads, std::vector<number_t> vec){

    std::vector<std::vector<number_t>> returnVec = std::vector<std::vector<number_t>>();
    long vecSize = vec.size();
    int threads = amountOfThreads;

    for (int i = 0; i < amountOfThreads; ++i) {
        long numbersPerThread = vecSize/(long)threads;

        // storing numbers for a thread
        std::vector<number_t> tempVec = std::vector<number_t>();
        for (int j = 0; j < numbersPerThread; ++j) {

            tempVec.push_back(vec[vecSize-1-j]);
        }

        returnVec.push_back(tempVec);

        vecSize -= numbersPerThread;
        threads--;
    }

    return returnVec;

}

std::vector<number_t> getSeeds(long max) {

    number_t firstPrime = number_t();
    firstPrime.number = 2;

    std::vector<number_t> seedVec = std::vector<number_t>();

    //Initializing seed vector
    for (long l = firstPrime.number; l <= sqrtl(max); ++l) {

        number_t numberToBeAdded = number_t();
        numberToBeAdded.number = l;

        seedVec.push_back(numberToBeAdded);
    }

    //marking non-primes
    long l = 0;
    while(l < seedVec.size()) {

        if(seedVec[l].isMarked) {
            l++;
            continue;
        }

        long lPowerToTwo = seedVec[l].number * seedVec[l].number;
        for (long j = l; j < seedVec.size(); ++j) {

            if(seedVec[j].number < lPowerToTwo) continue;

            bool isDivisible = seedVec[j].number % seedVec[l].number == 0;
            if(isDivisible && (!seedVec[j].isMarked)) seedVec[j].isMarked = true;
        }

        l++;
    }

    return seedVec;

}

void printPrimesInVec(std::vector<number_t> vec) {

    for(const number_t &e : vec) {
        if(!e.isMarked) {
            std::cout << e.number << std::endl;
        }

    }

}


std::mutex lock;

void calculateRange(std::vector<number_t> seeds, std::vector<number_t> range) {

    std::vector<number_t> rangeToBeModified = range;

    // marking non-primes
    for(const number_t &seed : seeds) {

        for (long l = 0; l < rangeToBeModified.size(); ++l) {

            if(rangeToBeModified[l].number % seed.number == 0) rangeToBeModified[l].isMarked = true;
        }
    }

    lock.lock();

    std::cout << "########### Primes obtained from thread with thread id: " << std::this_thread::get_id() << " ##############" << std::endl;
    printPrimesInVec(rangeToBeModified);
    std::cout << "#####################################################################################" << std::endl;

    lock.unlock();
}


int main(int argc, char** argv) {

    if((!std::strcmp(argv[1], "-h")) && argc == 2) {
        std::cout << "Run the program by typing ./Exercise2 [Amount of threads] [Maximum value in range]" << std::endl;
        std::cout << std::endl;
        std::cout << "To compile the program, type \"make\" (in this directory, where you are standing)" << std::endl;
        exit(0);
    }

    long max;
    int threads;

    try {
        threads = std::stoi(argv[1]);
        max = std::stol(argv[2]);

    } catch(std::invalid_argument e) {
        std::cout << "Give a number as argument!" << std::endl;
        exit(-1);
    }

    // obtained sequentially
    std::vector<number_t> seeds = getSeeds(max);

    // initialize range sqrt(max) + 1 to max
    number_t sqrtMaxPlusOne = number_t();
    sqrtMaxPlusOne.number = sqrtl(max) + 1;

    std::vector<number_t> primeVec = std::vector<number_t>();

    for (long l = sqrtMaxPlusOne.number; l <= max; ++l) {

        number_t numberToBeAdded = number_t();
        numberToBeAdded.number = l;

        primeVec.push_back(numberToBeAdded);
    }

    // divide range in chunks
    std::vector<std::vector<number_t>> loadBalancedVec = createChunks(threads, primeVec);
    std::vector<std::thread> processes = std::vector<std::thread>();

    auto startTime = std::chrono::system_clock::now();

    // spawning threads
    for (int i = 0; i < loadBalancedVec.size(); ++i) {

        processes.push_back(std::thread(calculateRange, seeds, loadBalancedVec[i]));
    }

    // joining threads
    for (int i = 0; i < processes.size(); ++i) {

        auto id = processes[i].get_id();
        processes[i].join();
        std::cout << "Thread with thread id " << id << " finished" << std::endl;
    }


    std::chrono::duration<double> runtime = (std::chrono::system_clock::now() - startTime);
    printf("The measured runtime: %f", runtime);

    return 0;
}
