#include "NKThreading/NKThreading.h"
#include "NKTime/NkChrono.h"
#include "NKWindow/NKMain.h"
#include <iostream>
#include <vector>

volatile int g_dummy = 0;

void ExecuteTask(int iterations) {
    int sum = 0;
    for (int i = 0; i < iterations; ++i) {
        sum += i;
    }
    g_dummy += sum;
}

int nkmain(const nkentseu::NkEntryState &state)
{
    const int numTasks = 200;
    const int shortIterations = 1000;
    const int longIterations = 100000;

    nkentseu::threading::NkThreadPool pool;
    nkentseu::NkChrono chrono;

    // Mesure 1
    chrono.Reset();
    for (int i = 0; i < numTasks; ++i) {
        pool.Enqueue([shortIterations]() { ExecuteTask(shortIterations); });
    }
    pool.Join();
    double poolShort1 = chrono.Elapsed().milliseconds();

    // Mesure 2
    chrono.Reset();
    for (int i = 0; i < numTasks; ++i) {
        pool.Enqueue([shortIterations]() { ExecuteTask(shortIterations); });
    }
    pool.Join();
    double poolShort2 = chrono.Elapsed().milliseconds();

    // Mesure 3
    chrono.Reset();
    for (int i = 0; i < numTasks; ++i) {
        pool.Enqueue([shortIterations]() { ExecuteTask(shortIterations); });
    }
    pool.Join();
    double poolShort3 = chrono.Elapsed().milliseconds();

    int numWorkers = pool.GetNumWorkers();

    // Version Fils (NkThread) avec une Tâche courte
    auto runThreadsShort = [numTasks, shortIterations]() {
        std::vector<NkThread> threads;
        threads.reserve(numTasks);
        for (int i = 0; i < numTasks; ++i) {
            threads.emplace_back([shortIterations]() { ExecuteTask(shortIterations); });
        }
        for (auto& t : threads) {
            t.Join();
        }
    };

    // Mesure 1
    chrono.Reset();
    runThreadsShort();
    double threadShort1 = chrono.Elapsed().milliseconds();

    // Mesure 2
    chrono.Reset();
    runThreadsShort();
    double threadShort2 = chrono.Elapsed().milliseconds();

    // Mesure 3
    chrono.Reset();
    runThreadsShort();
    double threadShort3 = chrono.Elapsed().milliseconds();

    //  Tâche Longue 
    // Réserve
    chrono.Reset();
    for (int i = 0; i < numTasks; ++i) {
        pool.Enqueue([longIterations]() { ExecuteTask(longIterations); });
    }
    pool.Join();
    double poolLong = chrono.Elapsed().milliseconds();

    // Fils
    chrono.Reset();
    {
        std::vector<NkThread> threads;
        threads.reserve(numTasks);
        for (int i = 0; i < numTasks; ++i) {
            threads.emplace_back([longIterations]() { ExecuteTask(longIterations); });
        }
        for (auto& t : threads) {
            t.Join();
        }
    }
    double threadLong = chrono.Elapsed().milliseconds();

    // Affichage synthétique des résultats
    std::cout << "Ouvriers : " << numWorkers << std::endl;
    std::cout << "Réserve (court) : " << poolShort1 << " " << poolShort2 << " " << poolShort3 << std::endl;
    std::cout << "Fils (court)    : " << threadShort1 << " " << threadShort2 << " " << threadShort3 << std::endl;
    std::cout << "Tâche longue    : Réserve = " << poolLong << " | Fils = " << threadLong << std::endl;

    return 0;
}