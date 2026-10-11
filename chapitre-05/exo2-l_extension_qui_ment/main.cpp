#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct FileIf {
    string name;
    long long size;
    string hexBytes;
};

vector<int> convertHex(const string& hexStr) {
    vector<int> bytes;
    if (hexStr == "-" || hexStr.empty()) return bytes;
    for (size_t i = 0; i + 1 < hexStr.length(); i += 2) {
        string byteString = hexStr.substr(i, 2);
        int byteVal = stoi(byteString, nullptr, 16);
        bytes.push_back(byteVal);
    }
    return bytes;
}

string getExtension(const string& filename) {
    size_t dotPos = filename.rfind('.');
    if (dotPos == string::npos) return "";
    string ext = filename.substr(dotPos + 1);
    for (char& c : ext) {
        if (c >= 'A' && c <= 'Z') {
            c += 32;
        }
    }
    return ext;
}

bool checkExtensionMatch(const string& format, const string& ext) {
    if (format == "PNG") return ext == "png";
    if (format == "JPEG") return ext == "jpg" || ext == "jpeg";
    if (format == "BMP") return ext == "bmp";
    if (format == "QOI") return ext == "qoi";
    if (format == "GIF") return ext == "gif";
    if (format == "ICO") return ext == "ico" || ext == "cur";
    if (format == "HDR") return ext == "hdr";
    if (format == "EXR") return ext == "exr";
    if (format == "PBM") return ext == "pbm";
    if (format == "PGM") return ext == "pgm";
    if (format == "PPM") return ext == "ppm";
    if (format == "TGA") return ext == "tga";
    if (format == "SVG") return ext == "svg";
    return false;
}

string detectFormat(long long size, const vector<int>& b) {
    if (size < 4) return "REFUSE";

    auto getByte = [&](size_t idx) -> int {
        if (idx < b.size()) return b[idx];
        return -1;
    };

    if (size >= 8 && getByte(0) == 0x89 && getByte(1) == 0x50 && getByte(2) == 0x4E && getByte(3) == 0x47) {
        return "PNG";
    }
    
    if (getByte(0) == 0xFF && getByte(1) == 0xD8 && getByte(2) == 0xFF) {
        return "JPEG";
    }

    if (getByte(0) == 0x42 && getByte(1) == 0x4D) {
        return "BMP";
    }

    if (getByte(0) == 0x71 && getByte(1) == 0x6F && getByte(2) == 0x69 && getByte(3) == 0x66) {
        return "QOI";
    }

    if (getByte(0) == 0x47 && getByte(1) == 0x49 && getByte(2) == 0x46 && getByte(3) == 0x38) {
        return "GIF";
    }

    if (getByte(0) == 0x00 && getByte(1) == 0x00 && (getByte(2) == 0x01 || getByte(2) == 0x02) && getByte(3) == 0x00) {
        return "ICO";
    }

    if (size >= 10 && getByte(0) == 0x23 && getByte(1) == 0x3F) {
        return "HDR";
    }

    if (getByte(0) == 0x76 && getByte(1) == 0x2F && getByte(2) == 0x31 && getByte(3) == 0x01) {
        return "EXR";
    }

    if (getByte(0) == 0x50 && getByte(1) >= 0x31 && getByte(1) <= 0x36) {
        char digit = getByte(1);
        if (digit == '1' || digit == '4') return "PBM";
        if (digit == '2' || digit == '5') return "PGM";
        if (digit == '3' || digit == '6') return "PPM";
    }

    if (size >= 18) {
        int b2 = getByte(2);
        if (b2 == 0x00 || b2 == 0x01 || b2 == 0x02 || b2 == 0x03 || b2 == 0x09 || b2 == 0x0A || b2 == 0x0B) {
            return "TGA";
        }
    }


    {
        vector<int> stream = b;
        size_t idx = 0;
        if (stream.size() >= 3 && stream[0] == 0xEF && stream[1] == 0xBB && stream[2] == 0xBF) {
            idx += 3;
        }
        while (idx < stream.size()) {
            int val = stream[idx];
            if (val == 0x20 || val == 0x09 || val == 0x0A || val == 0x0D) {
                idx++;
            } else {
                break;
            }
        }
        auto matchSub = [&](const vector<int>& pattern) {
            if (idx + pattern.size() > stream.size()) return false;
            for (size_t p = 0; p < pattern.size(); ++p) {
                if (stream[idx + p] != pattern[p]) return false;
            }
            return true;
        };

        vector<int> xmlPattern = {0x3C, 0x3F, 0x78, 0x6D, 0x6C};
        vector<int> svgPattern = {0x3C, 0x73, 0x76, 0x67};

        if (matchSub(xmlPattern) || matchSub(svgPattern)) {
            return "SVG";
        }
    }

    return "REFUSE";
}

int main() {
    
    int n;
    if (!(cin >> n)) return 0;

    vector<FileIf> files(n);
    for (int i = 0; i < n; ++i) {
        cin >> files[i].name >> files[i].size >> files[i].hexBytes;
    }

    int lusCount = 0;
    int mensongesCount = 0;
    int refusesCount = 0;

    for (int i = 0; i < n; ++i) {
        vector<int> bytes = convertHex(files[i].hexBytes);
        string format = detectFormat(files[i].size, bytes);
        string ext = getExtension(files[i].name);

        if (format == "REFUSE") {
            cout << files[i].name << " REFUSE\n";
            refusesCount++;
        } else {
            lusCount++;
            if (checkExtensionMatch(format, ext)) {
                cout << files[i].name << " " << format << " OK\n";
            } else {
                cout << files[i].name << " " << format << " MENT\n";
                mensongesCount++;
            }
        }
    }

    cout << "LUS " << lusCount << "\n";
    cout << "MENSONGES " << mensongesCount << "\n";
    cout << "REFUSES " << refusesCount << "\n";

    return 0;
}