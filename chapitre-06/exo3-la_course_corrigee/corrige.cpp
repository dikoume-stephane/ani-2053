#include <NKThreading/NkThread.h>
#include <NKThreading/NkMutex.h>
#include <NKCore/NkAtomic.h>
#include <NKTime/NkChrono.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace nkentseu;
using namespace nkentseu::threading;

const int kNumThreads = 8;
const int kIncrements = 1000000;
volatile int g_unprotectedCounter = 0;

int RunUnprotected() {
    g_unprotectedCounter = 0;
    std::vector<NkThread> threads;
    threads.reserve(kNumThreads);

    for (int i = 0; i < kNumThreads; ++i) {
        threads.emplace_back([]() {
            for (int j = 0; j < kIncrements; ++j) {
                g_unprotectedCounter += 1;
            }
        });
    }

    for (auto& t : threads) {
        t.Join();
    }
    return g_unprotectedCounter;
}

int RunMutex() {
    int counter = 0;
    NkMutex mutex;
    std::vector<NkThread> threads;
    threads.reserve(kNumThreads);

    for (int i = 0; i < kNumThreads; ++i) {
        threads.emplace_back([&counter, &mutex]() {
            for (int j = 0; j < kIncrements; ++j) {
                NkScopedLock<NkMutex> lock(mutex);
                counter += 1;
            }
        });
    }

    for (auto& t : threads) {
        t.Join();
    }
    return counter;
}

int RunAtomic() {
    NkAtomicInt counter(0);
    std::vector<NkThread> threads;
    threads.reserve(kNumThreads);

    for (int i = 0; i < kNumThreads; ++i) {
        threads.emplace_back([&counter]() {
            for (int j = 0; j < kIncrements; ++j) {
                counter.FetchAdd(1);
            }
        });
    }

    for (auto& t : threads) {
        t.Join();
    }
    return counter.Load();
}

int RunLocal() {
    int localTotals[kNumThreads] = {0};
    std::vector<NkThread> threads;
    threads.reserve(kNumThreads);

    for (int i = 0; i < kNumThreads; ++i) {
        threads.emplace_back([&localTotals, i]() {
            int localCounter = 0;
            for (int j = 0; j < kIncrements; ++j) {
                localCounter += 1;
            }
            localTotals[i] = localCounter;
        });
    }

    // Attente impérative de la fin des threads avant de lire les résultats
    for (auto& t : threads) {
        t.Join();
    }

    int totalSum = 0;
    for (int i = 0; i < kNumThreads; ++i) {
        totalSum += localTotals[i];
    }
    return totalSum;
}

// Utilitaire de mesure (médiane de 3 exécutions)
double MeasureMedian(int (*func)(), int& outTotal) {
    double times[3];
    NkChrono chrono;

    for (int i = 0; i < 3; ++i) {
        chrono.Reset();
        outTotal = func();
        times[i] = chrono.Elapsed().milliseconds();
    }

    std::sort(times, times + 3);
    return times[1]; // Retourne la valeur médiane
}

int nkmain(const NkEntryState &state)
{
    int totalUnprotected = 0, totalMutex = 0, totalAtomic = 0, totalLocal = 0;

    double tUnprotected = MeasureMedian(RunUnprotected, totalUnprotected);
    double tMutex = MeasureMedian(RunMutex, totalMutex);
    double tAtomic = MeasureMedian(RunAtomic, totalAtomic);
    double tLocal = MeasureMedian(RunLocal, totalLocal);

    std::cout << "Sans protection : " << totalUnprotected << " " << tUnprotected << " ms" << std::endl;
    std::cout << "Mutex           : " << totalMutex << " " << tMutex << " ms" << std::endl;
    std::cout << "Atomique        : " << totalAtomic << " " << tAtomic << " ms" << std::endl;
    std::cout << "Local           : " << totalLocal << " " << tLocal << " ms" << std::endl;

    return 0;
}