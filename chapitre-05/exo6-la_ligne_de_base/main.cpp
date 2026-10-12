#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Glyph {
    char c;
    int avance;
    int x0, y0, x1, y1;
    bool valid;
};

// Structure pour stocker le crénage
struct KerningPair {
    char c1;
    char c2;
    int value;
};

int main() {

    int G;
    if (!(cin >> G)) return 0;

    vector<Glyph> glyphs(G);
    for (int i = 0; i < G; ++i) {
        cin >> glyphs[i].c >> glyphs[i].avance >> glyphs[i].x0 >> glyphs[i].y0 >> glyphs[i].x1 >> glyphs[i].y1;
        glyphs[i].valid = true;
    }

    int K;
    if (!(cin >> K)) return 0;

    vector<KerningPair> kernings(K);
    for (int i = 0; i < K; ++i) {
        string pairStr;
        int k;
        cin >> pairStr >> k;
        if (pairStr.length() >= 2) {
            kernings[i] = {pairStr[0], pairStr[1], k};
        }
    }

    string text;
    long long ox, oy;
    cin >> text >> ox >> oy;

    long long currentX = ox;
    int absentsCount = 0;
    bool hasDrawn = false;

    long long minx = 0, miny = 0, maxx = 0, maxy = 0;

    for (size_t i = 0; i < text.length(); ++i) {
        char c = text[i];

        bool found = false;
        Glyph currentGlyph;
        for (int j = 0; j < G; ++j) {
            if (glyphs[j].c == c) {
                currentGlyph = glyphs[j];
                found = true;
                break;
            }
        }

        if (!found) {
            cout << c << " ABSENT\n";
            absentsCount++;
            continue;
        }

        cout << c << " " << currentX << "\n";

        bool isDrawable = (currentGlyph.x1 > currentGlyph.x0 && currentGlyph.y1 > currentGlyph.y0);
        if (isDrawable) {
            long long rx0 = currentX + currentGlyph.x0;
            long long ry0 = oy + currentGlyph.y0;
            long long rx1 = currentX + currentGlyph.x1;
            long long ry1 = oy + currentGlyph.y1;

            if (!hasDrawn) {
                minx = rx0;
                miny = ry0;
                maxx = rx1;
                maxy = ry1;
                hasDrawn = true;
            } else {
                if (rx0 < minx) minx = rx0;
                if (ry0 < miny) miny = ry0;
                if (rx1 > maxx) maxx = rx1;
                if (ry1 > maxy) maxy = ry1;
            }
        }

        long long nextAdvance = currentGlyph.avance;
        if (i + 1 < text.length()) {
            char nextC = text[i + 1];
            for (int k = 0; k < K; ++k) {
                if (kernings[k].c1 == c && kernings[k].c2 == nextC) {
                    nextAdvance += kernings[k].value;
                    break;
                }
            }
        }
        currentX += nextAdvance;
    }

    cout << "CURSEUR " << currentX << "\n";

    if (!hasDrawn) {
        cout << "BOITE AUCUNE\n";
        cout << "MONTE 0\n";
        cout << "DESCEND 0\n";
        cout << "ECRAN RIEN\n";
    } else {
        cout << "BOITE " << minx << " " << miny << " " << maxx << " " << maxy << "\n";

        long long monte = (miny < oy) ? (oy - miny) : 0;
        long long descend = (maxy > oy) ? (maxy - oy) : 0;

        cout << "MONTE " << monte << "\n";
        cout << "DESCEND " << descend << "\n";
        string ecran = "VISIBLE";
        if (maxy <= 0) {
            ecran = "HORS";
        } else if (miny < 0) {
            ecran = "COUPE";
        }
        cout << "ECRAN " << ecran << "\n";
    }

    cout << "ABSENTS " << absentsCount << "\n";
    return 0;
}