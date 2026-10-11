#include <iostream>
#include <string>

using namespace std;

struct Format {
    string name;
    long long bpp;
    bool color;
    bool alpha;
    bool floatType;
};

Format getFormat(const string& name) {
    if (name == "GRAY8")    return {name, 1, false, false, false};
    if (name == "GRAY_A16") return {name, 2, false, true,  false};
    if (name == "RGB24")    return {name, 3, true,  false, false};
    if (name == "RGBA32")   return {name, 4, true,  true,  false};
    if (name == "RGB96F")   return {name, 12, true,  false, true};
    if (name == "RGBA128F") return {name, 16, true,  true,  true};
    return {"UNKNOWN", 0, false, false, false};
}

int main() {
    
    long long w, h;
    if (!(cin >> w >> h)) return 0;

    int n;
    if (!(cin >> n)) return 0;

    long long totalBytes = 0;
    int sansPerteCount = 0;
    int refusesCount = 0;

    for (int i = 0; i < n; ++i) {
        string srcName, tgtName;
        cin >> srcName >> tgtName;

        Format src = getFormat(srcName);
        Format tgt = getFormat(tgtName);

        if (src.name == "UNKNOWN" || tgt.name == "UNKNOWN") {
            cout << srcName << " " << tgtName << " REFUSE\n";
            refusesCount++;
            continue;
        }

        long long srcBytes = w * h * src.bpp;
        long long tgtBytes = w * h * tgt.bpp;

        bool lossTrans = src.alpha && !tgt.alpha;
        bool lossColor = src.color && !tgt.color;
        bool lossFloat = src.floatType && !tgt.floatType;

        string loss = "";
        if (lossTrans) loss += "TRANSPARENCE";
        if (lossColor) {
            if (!loss.empty()) loss += "+";
            loss += "COULEUR";
        }
        if (lossFloat) {
            if (!loss.empty()) loss += "+";
            loss += "ETENDUE";
        }

        if (loss.empty()) {
            loss = "AUCUNE";
            sansPerteCount++;
        }

        cout << srcName << " " << tgtName << " " << srcBytes << " " << tgtBytes << " " << loss << "\n";
        totalBytes += tgtBytes;
    }

    cout << "TOTAL " << totalBytes << "\n";
    cout << "SANS_PERTE " << sansPerteCount << "\n";
    cout << "REFUSES " << refusesCount << "\n";

    return 0;
}