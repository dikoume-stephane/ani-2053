#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Track {
    string type;
    string code;
};

struct MediaFile {
    string name;
    string hexBytes;
    int pisteCount;
    vector<Track> tracks;
};

vector<int> parseHex(const string& hexStr) {
    vector<int> bytes;
    if (hexStr == "-" || hexStr.empty()) return bytes;
    for (size_t i = 0; i + 1 < hexStr.length(); i += 2) {
        string byteString = hexStr.substr(i, 2);
        int byteVal = stoi(byteString, nullptr, 16);
        bytes.push_back(byteVal);
    }
    return bytes;
}

string translateCodec(const string& code) {
    if (code == "mp4a") return "aac";
    if (code == "Opus" || code == "opus") return "opus";
    if (code == "avc1" || code == "avc3") return "h264";
    if (code == "hvc1" || code == "hev1") return "h265";
    if (code == "vp08") return "vp8";
    if (code == "vp09") return "vp9";
    if (code == "mp4v") return "mpeg4";
    if (code == ".mp3") return "mp3";
    if (code == "twos" || code == "sowt" || code == "lpcm") return "pcm";
    return code;
}

int main() {
   
    int N;
    if (!(cin >> N)) return 0;

    vector<MediaFile> files(N);
    for (int i = 0; i < N; ++i) {
        cin >> files[i].name >> files[i].hexBytes >> files[i].pisteCount;
        for (int j = 0; j < files[i].pisteCount; ++j) {
            Track t;
            cin >> t.type >> t.code;
            files[i].tracks.push_back(t);
        }
    }

    int mp4Count = 0;
    int lisiblesCount = 0;
    int inconnusCount = 0;

    for (int i = 0; i < N; ++i) {
        vector<int> b = parseHex(files[i].hexBytes);
        size_t n = b.size();

        string container = "INCONNU";

        if (n >= 8 && b[4] == 0x66 && b[5] == 0x74 && b[6] == 0x79 && b[7] == 0x70) {
            container = "MP4";
        }
        else if (n >= 4 && b[0] == 0x1A && b[1] == 0x45 && b[2] == 0xDF && b[3] == 0xA3) {
            container = "WEBM";
        }
        else if (n >= 12 && b[0] == 0x52 && b[1] == 0x49 && b[2] == 0x46 && b[3] == 0x46 &&
                 b[8] == 0x57 && b[9] == 0x41 && b[10] == 0x56 && b[11] == 0x45) {
            container = "WAV";
        }
        else if (n >= 4 && b[0] == 0x4F && b[1] == 0x67 && b[2] == 0x67 && b[3] == 0x53) {
            container = "OGG";
        }
        else if (n >= 4 && b[0] == 0x66 && b[1] == 0x4C && b[2] == 0x61 && b[3] == 0x43) {
            container = "FLAC";
        }
        else if (n >= 3 && b[0] == 0x49 && b[1] == 0x44 && b[2] == 0x33) {
            container = "MP3";
        }
        else if (n >= 2 && b[0] == 0xFF && b[1] >= 0xE0) {
            container = "MP3";
        }

        cout << files[i].name << " " << container << "\n";

        if (container == "MP4") {
            mp4Count++;

            for (size_t j = 0; j < files[i].tracks.size(); ++j) {
                string trackType = (files[i].tracks[j].type == "vide") ? "VIDEO" : "AUDIO";
                string translatedCodec = translateCodec(files[i].tracks[j].code);
                cout << files[i].name << " PISTE " << (j + 1) << " " << trackType << " " << translatedCodec << "\n";
            }

            string verdict = "SANS_IMAGE";
            bool foundVideo = false;
            for (const auto& t : files[i].tracks) {
                if (t.type == "vide") {
                    foundVideo = true;
                    if (t.code == "mjpa" || t.code == "jpeg" || t.code == "MJPG" ||
                        t.code == "avc1" || t.code == "avc3" || t.code == "hvc1" ||
                        t.code == "hev1" || t.code == "av01") {
                        verdict = "LISIBLE";
                    } else {
                        verdict = "ECHEC";
                    }
                    break;
                }
            }

            cout << files[i].name << " LECTEUR " << verdict << "\n";
            if (verdict == "LISIBLE") {
                lisiblesCount++;
            }
        } else {
            if (container == "INCONNU") {
                inconnusCount++;
            }
        }
    }

    cout << "MP4 " << mp4Count << "\n";
    cout << "LISIBLES " << lisiblesCount << "\n";
    cout << "INCONNUS " << inconnusCount << "\n";

    return 0;
}