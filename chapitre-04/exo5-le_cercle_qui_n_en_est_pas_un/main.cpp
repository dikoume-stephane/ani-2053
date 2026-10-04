#include <iostream>
#include <cmath>

int main() {
    
    int N = 0;
    if (!(std::cin >> N)) {
        return 0;
    }

    const double PI = 3.141592653589793;
    int visiblesCount = 0;
    int refusesCount = 0;

    for (int i = 0; i < N; ++i) {
        long long r = 0;
        long long n = 0;
        std::cin >> r >> n;

        if (n < 3) {
            std::cout << r << " " << n << " REFUSE\n";
            refusesCount++;
            continue;
        }

        // Calcul de l'écart g 
        double g = (double)r * (1.0 - std::cos(PI / (double)n));

        long long ecart = static_cast<long long>(std::floor(g * 1000.0));

        if (g == 0.0) {
            std::cout << r << " " << n << " " << ecart << " JAMAIS\n";
            continue;
        }

        long long zoom = static_cast<long long>(std::ceil(100.0 / g));

        if (zoom <= 100) {
            std::cout << r << " " << n << " " << ecart << " " << zoom << " VISIBLE\n";
            visiblesCount++;
        } else {
            std::cout << r << " " << n << " " << ecart << " " << zoom << " INVISIBLE\n";
        }
    }

    std::cout << "VISIBLES " << visiblesCount << "\n";
    std::cout << "REFUSES " << refusesCount << "\n";

    return 0;
}
