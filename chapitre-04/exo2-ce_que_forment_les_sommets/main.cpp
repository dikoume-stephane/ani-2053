#include <iostream>
#include <string>

int main() {

    int n = 0;
    if (!(std::cin >> n)) {
        return 0;
    }

    long long totalPoints = 0;
    long long totalSegments = 0;
    long long totalTriangles = 0;
    long long totalRefuses = 0;

    for (int i = 0; i < n; ++i) {
        std::string type;
        long long s = 0;
        std::cin >> type >> s;

        if (s < 0) {
            s = 0;
        }

        if (type == "POINTS") {
            long long count = s;
            long long res = 0;
            std::cout << type << " " << s << " " << count << " POINTS " << res << "\n";
            totalPoints += count;
        } else if (type == "LINES") {
            long long count = s / 2;
            long long res = s % 2;
            std::cout << type << " " << s << " " << count << " SEGMENTS " << res << "\n";
            totalSegments += count;
        } else if (type == "LINE_STRIP") {
            long long count = (s >= 2) ? (s - 1) : 0;
            long long res = (s >= 2) ? 0 : s;
            std::cout << type << " " << s << " " << count << " SEGMENTS " << res << "\n";
            totalSegments += count;
        } else if (type == "TRIANGLES") {
            long long count = s / 3;
            long long res = s % 3;
            std::cout << type << " " << s << " " << count << " TRIANGLES " << res << "\n";
            totalTriangles += count;
        } else if (type == "TRIANGLE_STRIP" || type == "TRIANGLE_FAN") {
            long long count = (s >= 3) ? (s - 2) : 0;
            long long res = (s >= 3) ? 0 : s;
            std::cout << type << " " << s << " " << count << " TRIANGLES " << res << "\n";
            totalTriangles += count;
        } else {
            std::cout << type << " " << s << " REFUSE\n";
            totalRefuses++;
        }
    }

    std::cout << "POINTS " << totalPoints << "\n";
    std::cout << "SEGMENTS " << totalSegments << "\n";
    std::cout << "TRIANGLES " << totalTriangles << "\n";
    std::cout << "REFUSES " << totalRefuses << "\n";

    return 0;
}
