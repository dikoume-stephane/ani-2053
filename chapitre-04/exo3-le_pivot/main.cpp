#include <iostream>
#include <string>
#include <algorithm>

// Fonction pour normaliser l'angle dans l'intervalle [0, 360[
long long normalizeA(long long angle) {
    long long mod = angle % 360;
    if (mod < 0) {
        mod += 360;
    }
    return mod;
}

int main() {
   
    int n = 0;
    if (!(std::cin >> n)) {
        return 0;
    }

    int totalRefuses = 0;

    for (int i = 0; i < n; ++i) {
        std::string nom;
        long long w = 0, h = 0;
        long long px = 0, py = 0;
        long long ox = 0, oy = 0;
        long long sx = 0, sy = 0;
        long long angleI = 0;

        std::cin >> nom >> w >> h >> px >> py >> ox >> oy >> sx >> sy >> angleI;

        long long normAngle = normalizeA(angleI);

        // Vérification si l'angle est un multiple de 90
        if (normAngle % 90 != 0) {
            std::cout << nom << " ANGLE REFUSE\n";
            totalRefuses++;
            continue;
        }

        // valeurs de c et s
        long long c = 0, s = 0;
        if (normAngle == 0) {
            c = 1; s = 0;
        } else if (normAngle == 90) {
            c = 0; s = 1;
        } else if (normAngle == 180) {
            c = -1; s = 0;
        } else if (normAngle == 270) {
            c = 0; s = -1;
        }

        // Définition des 4 coins locaux
        long long localX[4] = {0, w, w, 0};
        long long localY[4] = {0, 0, h, h};

        long long worldX[4];
        long long worldY[4];

        for (int k = 0; k < 4; ++k) {
            // Soustraction de l'origine et application de l'échelle
            long long ax = (localX[k] - ox) * sx;
            long long ay = (localY[k] - oy) * sy;

            // Rotation
            long long rx = ax * c - ay * s;
            long long ry = ax * s + ay * c;

            // convertion dans le monde
            worldX[k] = px + rx;
            worldY[k] = py + ry;
        }

        // Affichage des 4 coins
        std::cout << nom << " COINS "
                  << worldX[0] << " " << worldY[0] << " "
                  << worldX[1] << " " << worldY[1] << " "
                  << worldX[2] << " " << worldY[2] << " "
                  << worldX[3] << " " << worldY[3] << "\n";

        // Calcul de la boîte englobante
        long long minX = std::min({worldX[0], worldX[1], worldX[2], worldX[3]});
        long long maxX = std::max({worldX[0], worldX[1], worldX[2], worldX[3]});
        long long minY = std::min({worldY[0], worldY[1], worldY[2], worldY[3]});
        long long maxY = std::max({worldY[0], worldY[1], worldY[2], worldY[3]});

        std::cout << nom << " BOITE " << minX << " " << minY << " " << maxX << " " << maxY << "\n";
    }

    std::cout << "REFUSES " << totalRefuses << "\n";

    return 0;
}
