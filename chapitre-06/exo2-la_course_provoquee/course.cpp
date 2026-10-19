#include <NKThreading/NkThread.h>
#include <iostream>
#include <vector>

int main()
{
    const int numThreads = 8;
    const int incrementsPerThread = 1000000;
    int counter = 0;

    std::vector<nkentseu::threading::NkThread> threads;
    threads.reserve(numThreads);

    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back([&counter, incrementsPerThread]() {
            for (int j = 0; j < incrementsPerThread; ++j) {
                counter += 1;
            }
        });
    }
    
    for (auto& t : threads) {
        t.Join();
    }

    std::cout << "Total obtenu : " << counter << std::endl;
    std::cout << "Total attendu : " << (numThreads * incrementsPerThread) << std::endl;

    return 0;
}