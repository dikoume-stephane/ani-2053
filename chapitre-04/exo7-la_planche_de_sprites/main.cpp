#include <iostream>

int main() {
   
    long long C = 0, R = 0;
    long long W = 0, H = 0;
    long long F = 0, D = 0, P = 0;

    if (!(std::cin >> C >> R >> W >> H >> F >> D >> P)) {
        return 0;
    }

    int N = 0;
    if (!(std::cin >> N)) {
       
        std::cout << "AVANCES 0\n";
        std::cout << "PLAFONNES 0\n";
        return 0;
    }

    long long currentFrame = 0;
    long long accumulatedTime = 0;

    long long avancesCount = 0;
    long long plafonnesCount = 0;

    for (int i = 0; i < N; ++i) {
        long long dt = 0;
        std::cin >> dt;

        if (dt > P) {
            dt = P;
            plafonnesCount++;
        }

        accumulatedTime += dt;

        while (accumulatedTime >= D) {
            accumulatedTime -= D; 
            currentFrame = (currentFrame + 1) % F;
            avancesCount++;
        }

        long long col = currentFrame % C;
        long long row = currentFrame / C;

        long long x = col * W;
        long long y = row * H;

        std::cout << currentFrame << " " << x << " " << y << " " << W << " " << H << "\n";
    }

    std::cout << "AVANCES " << avancesCount << "\n";
    std::cout << "PLAFONNES " << plafonnesCount << "\n";

    return 0;
}