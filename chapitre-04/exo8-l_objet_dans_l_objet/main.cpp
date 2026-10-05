#include <iostream>
#include <string>
#include <vector>

struct Objet {
    std::string nom;
    long long x_monde;
    long long y_monde;
    long long angle_monde;
    long long echelle_monde;
    int niveau;
};

// Fonction pour ramener un angle dans l'intervalle [0, 270]
long long normaliser_angle(long long angle) {
    angle = angle % 360;
    if (angle < 0) {
        angle += 360;
    }
    return angle;
}

int main() {
   
    int N = 0;
    if (!(std::cin >> N)) {
        return 0;
    }

    std::vector<Objet> objets;
    objets.reserve(N);

    int max_profondeur = 0;

    for (int i = 0; i < N; ++i) {
        std::string nom, parent;
        long long tx, ty, angle_propre, echelle_propre;
        std::cin >> nom >> parent >> tx >> ty >> angle_propre >> echelle_propre;

        Objet obj;
        obj.nom = nom;

        if (parent == "-") {
            
            obj.x_monde = tx;
            obj.y_monde = ty;
            obj.angle_monde = normaliser_angle(angle_propre);
            obj.echelle_monde = echelle_propre;
            obj.niveau = 1;
        } else {
            
            const Objet* p = nullptr;
            for (const auto& o : objets) {
                if (o.nom == parent) {
                    p = &o;
                    break;
                }
            }

            long long ax = tx * p->echelle_monde;
            long long ay = ty * p->echelle_monde;

            long long c = 0, s = 0;
            long long angle_p = p->angle_monde;

            if (angle_p == 0) {
                c = 1; s = 0;
            } else if (angle_p == 90) {
                c = 0; s = 1;
            } else if (angle_p == 180) {
                c = -1; s = 0;
            } else if (angle_p == 270) {
                c = 0; s = -1;
            }

            long long rx = ax * c - ay * s;
            long long ry = ax * s + ay * c;

            obj.x_monde = p->x_monde + rx;
            obj.y_monde = p->y_monde + ry;

            obj.angle_monde = normaliser_angle(p->angle_monde + angle_propre);
            obj.echelle_monde = p->echelle_monde * echelle_propre;
            obj.niveau = p->niveau + 1;
        }

        if (obj.niveau > max_profondeur) {
            max_profondeur = obj.niveau;
        }

        objets.push_back(obj);
    }

    for (const auto& obj : objets) {
        std::cout << obj.nom << " "
                  << obj.x_monde << " "
                  << obj.y_monde << " "
                  << obj.angle_monde << " "
                  << obj.echelle_monde << "\n";
    }

    std::cout << "PROFONDEUR " << max_profondeur << "\n";

    return 0;
}