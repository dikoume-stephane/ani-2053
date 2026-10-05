#include <iostream>
#include <string>

int main() {
    
    long long v = 0;
    int N = 0;

    if (!(std::cin >> v >> N)) {
        return 0;
    }

    bool spacePressed = false;
    bool leftPressed = false;
    bool rightPressed = false;

    long long xe = 0; // Mode événement
    long long xi = 0; // Mode interrogation

    long long sautsEvenements = 0;
    long long sautsInterrogation = 0;
    long long manques = 0;

    for (int i = 1; i <= N; ++i) {
        int k = 0;
        std::cin >> k;

        int spaceEventsInFrame = 0;

        for (int j = 0; j < k; ++j) {
            std::string eventStr;
            std::cin >> eventStr;

            if (eventStr.empty()) continue;

            char type = eventStr[0];
            std::string name = eventStr.substr(1);

            if (type == '+') {
                if (name == "SPACE") {
                    spacePressed = true;
                    sautsEvenements++;
                    spaceEventsInFrame++;
                } else if (name == "RIGHT") {
                    rightPressed = true;
                    xe += v;
                } else if (name == "LEFT") {
                    leftPressed = true;
                    xe -= v;
                }
            } else if (type == '-') {
                if (name == "SPACE") {
                    spacePressed = false;
                } else if (name == "RIGHT") {
                    rightPressed = false;
                } else if (name == "LEFT") {
                    leftPressed = false;
                }
            }
        }

        if (spacePressed) {
            sautsInterrogation++;
        }
        if (rightPressed) {
            xi += v;
        }
        if (leftPressed) {
            xi -= v;
        }

        if (spaceEventsInFrame > 0 && !spacePressed) {
            manques += spaceEventsInFrame;
        }
        std::cout << i << " " << xe << " " << xi << "\n";
    }

    std::cout << "SAUTS EVENEMENTS " << sautsEvenements << "\n";
    std::cout << "SAUTS INTERROGATION " << sautsInterrogation << "\n";
    std::cout << "MANQUES " << manques << "\n";

    return 0;
}