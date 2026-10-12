#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Sound {
    string name;
    long long freq;
    long long channels;
    long long bits;
    long long duration;
    long long fileSize;
};

int main() {
    
    long long threshold;
    if (!(cin >> threshold)) return 0;

    int n;
    if (!(cin >> n)) return 0;

    vector<Sound> sounds(n);
    for (int i = 0; i < n; ++i) {
        cin >> sounds[i].name >> sounds[i].freq >> sounds[i].channels >> sounds[i].bits >> sounds[i].duration >> sounds[i].fileSize;
    }

    long long totalMemoryBytes = 0;
    int fluxCount = 0;
    int refusesCount = 0;

    for (int i = 0; i < n; ++i) {
        // Vérification des profondeurs acceptées : 8, 16, 24, 32 bits
        if (sounds[i].bits != 8 && sounds[i].bits != 16 && sounds[i].bits != 24 && sounds[i].bits != 32) {
            cout << sounds[i].name << " REFUSE\n";
            refusesCount++;
            continue;
        }

        long long rawSize = (sounds[i].freq * sounds[i].channels * (sounds[i].bits / 8) * sounds[i].duration) / 1000;

        long long percent = (rawSize > 0) ? (sounds[i].fileSize * 100) / rawSize : 0;

        string mode = "";
        if (rawSize > threshold) {
            mode = "FLUX";
            fluxCount++;
        } else {
            mode = "MEMOIRE";
            totalMemoryBytes += rawSize;
        }

        cout << sounds[i].name << " " << rawSize << " " << percent << " " << mode << "\n";
    }

    cout << "MEMOIRE " << totalMemoryBytes << "\n";
    cout << "FLUX " << fluxCount << "\n";
    cout << "REFUSES " << refusesCount << "\n";

    return 0;
}