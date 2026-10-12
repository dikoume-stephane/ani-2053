#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    
    long long D, C;
    if (!(cin >> D >> C)) return 0;

    int N;
    if (!(cin >> N)) return 0;

    vector<long long> t(N);
    for (int i = 0; i < N; ++i) {
        cin >> t[i];
    }

    if (N == 0) {
        cout << "VOIX_MAX 0\n";
        cout << "RETARD_MAX 0\n";
        cout << "COUPES 0\n";
        return 0;
    }

    long long prev_load_end = 0;
    long long voix_max = 0;
    long long retard_max = 0;
    int coupes_count = 0;

    for (int i = 0; i < N; ++i) {
        
        long long active_voices = 0;
        for (int j = 0; j <= i; ++j) {
            if (t[j] <= t[i] && t[j] + D > t[i]) {
                active_voices++;
            }
        }
        if (active_voices > voix_max) {
            voix_max = active_voices;
        }

        long long load_start = t[i];
        if (i > 0 && prev_load_end > load_start) {
            load_start = prev_load_end;
        }
        long long load_end = load_start + C;
        long long retard = load_end - t[i];
        prev_load_end = load_end;

        if (retard > retard_max) {
            retard_max = retard;
        }

        string etat = "ENTIER";
        if (i + 1 < N && t[i + 1] < t[i] + D) {
            etat = "COUPE";
            coupes_count++;
        }

        cout << t[i] << " " << active_voices << " " << retard << " " << etat << "\n";
    }

    cout << "VOIX_MAX " << voix_max << "\n";
    cout << "RETARD_MAX " << retard_max << "\n";
    cout << "COUPES " << coupes_count << "\n";

    return 0;
}