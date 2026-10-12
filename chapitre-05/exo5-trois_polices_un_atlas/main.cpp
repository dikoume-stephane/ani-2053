#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Group {
    string name;
    int count;
    long long w;
    long long h;
};

int main() {
    
    long long P, L;
    if (!(cin >> P >> L)) return 0;

    int G;
    if (!(cin >> G)) return 0;

    vector<Group> groups(G);
    long long totalOccupe = 0;
    long long totalBesoin = 0;

    for (int i = 0; i < G; ++i) {
        cin >> groups[i].name >> groups[i].count >> groups[i].w >> groups[i].h;
        totalOccupe += (long long)groups[i].count * groups[i].w * groups[i].h;
        totalBesoin += (long long)groups[i].count * (groups[i].w + P) * (groups[i].h + P);
    }
    if (G == 0) {
        cout << "AUCUN\n";
        return 0;
    }

    long long W = L;
    if (W == 0) {
        W = 512;
        while (W * W < 2 * totalBesoin && W < 4096) {
            W *= 2;
        }
    }

    long long H = W;
    int essaiReussi = 0;
    bool success = false;

    struct ResultG {
        string name;
        long long x1, y1, x2, y2;
    };
    vector<ResultG> finalResults;

    for (int essai = 1; essai <= 8; ++essai) {
        long long x = P;
        long long y = P;
        long long e = 0;
        bool essaiEchoue = false;

        vector<ResultG> currentResults;

        for (int i = 0; i < G; ++i) {
            long long rw = groups[i].w + P;
            long long rh = groups[i].h + P;
            long long firstX = -1, firstY = -1;
            long long lastX = -1, lastY = -1;

            for (int k = 0; k < groups[i].count; ++k) {
                if (x + rw > W - P) {
                    x = P;
                    y = y + e + P;
                    e = 0;
                    if (x + rw > W - P) {
                        essaiEchoue = true;
                        break;
                    }
                }
                
                if (y + rh > H - P) {
                    essaiEchoue = true;
                    break;
                }

                long long gx = x;
                long long gy = y;

                if (k == 0) {
                    firstX = gx;
                    firstY = gy;
                }
                if (k == groups[i].count - 1) {
                    lastX = gx;
                    lastY = gy;
                }

                x = x + rw;
                if (rh > e) {
                    e = rh;
                }
            }

            if (essaiEchoue) break;
            currentResults.push_back({groups[i].name, firstX, firstY, lastX, lastY});
        }

        if (!essaiEchoue) 
        {
            essaiReussi = essai;
            finalResults = currentResults;
            success = true;
            break;
        } else {

            if (W == H)
             {
                W *= 2;
            } else {
                H = W;
            }
        }
    }

    if (!success) {
        cout << "ESSAIS 8\n";
        cout << "ECHEC\n";
    } else {
        cout << "ESSAIS " << essaiReussi << "\n";
        cout << "TEXTURE " << W << " " << H << "\n";
        for (const auto& res : finalResults) {
            cout << res.name << " " << res.x1 << " " << res.y1 << " " << res.x2 << " " << res.y2 << "\n";
        }
        cout << "OCCUPE " << totalOccupe << "\n";
        
        long long area = W * H;
        long long perdu = (area - totalOccupe) * 100 / area;
        cout << "PERDU " << perdu << "\n";
    }

    return 0;
}