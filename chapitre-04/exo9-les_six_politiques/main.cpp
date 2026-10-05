#include <iostream>
#include <string>

long long arrondir(long long a, long long b) {
    return (2 * a + b) / (2 * b);
}

int main() {
   
    long long RW = 0, RH = 0, AW = 0, AH = 0, W = 0, H = 0;
    if (!(std::cin >> RW >> RH >> AW >> AH >> W >> H)) {
        return 0;
    }

    bool no_ref = (RW == 0 || RH == 0);

    long long vx[6], vy[6], vw[6], vh[6], mw[6], mh[6];
    std::string names[6] = {
        "FOLLOW_WINDOW", "STRETCH", "FIT_LETTERBOX",
        "INTEGER_SCALE", "FIT_CROP", "MANUAL"
    };

    //FOLLOW_WINDOW
    vx[0] = 0; vy[0] = 0; vw[0] = W; vh[0] = H;
    mw[0] = W; mh[0] = H;

    //STRETCH
    if (no_ref) {
        vx[1] = 0; vy[1] = 0; vw[1] = W; vh[1] = H;
        mw[1] = W; mh[1] = H;
    } else {
        vx[1] = 0; vy[1] = 0; vw[1] = W; vh[1] = H;
        mw[1] = RW; mh[1] = RH;
    }

    // FIT_LETTERBOX
    if (no_ref) {
        vx[2] = 0; vy[2] = 0; vw[2] = W; vh[2] = H;
        mw[2] = W; mh[2] = H;
    } else {
        if (W * RH <= H * RW) {
            vw[2] = W;
            vh[2] = arrondir(RH * W, RW);
        } else {
            vh[2] = H;
            vw[2] = arrondir(RW * H, RH);
        }
        vx[2] = (W - vw[2]) / 2;
        vy[2] = (H - vh[2]) / 2;
        mw[2] = RW;
        mh[2] = RH;
    }

    //INTEGER_SCALE
    if (no_ref) {
        vx[3] = 0; vy[3] = 0; vw[3] = W; vh[3] = H;
        mw[3] = W; mh[3] = H;
    } else {
        if (W >= RW && H >= RH) {
            long long k_w = W / RW;
            long long k_h = H / RH;
            long long k = (k_w < k_h) ? k_w : k_h;

            vw[3] = RW * k;
            vh[3] = RH * k;
            vx[3] = (W - vw[3]) / 2;
            vy[3] = (H - vh[3]) / 2;
            mw[3] = RW;
            mh[3] = RH;
        } else {
            // Même comportement que FIT_LETTERBOX
            vx[3] = vx[2]; vy[3] = vy[2]; vw[3] = vw[2]; vh[3] = vh[2];
            mw[3] = mw[2]; mh[3] = mh[2];
        }
    }

    //FIT_CROP
    if (no_ref) {
        vx[4] = 0; vy[4] = 0; vw[4] = W; vh[4] = H;
        mw[4] = W; mh[4] = H;
    } else {
        vx[4] = 0; vy[4] = 0; vw[4] = W; vh[4] = H;
        if (W * RH > H * RW) {
            mw[4] = RW;
            mh[4] = arrondir(RW * H, W);
        } else {
            mw[4] = arrondir(RH * W, H);
            mh[4] = RH;
        }
    }

    // MANUAL
    vx[5] = 0; vy[5] = 0; vw[5] = AW; vh[5] = AH;
    mw[5] = AW; mh[5] = AH;

    // Affichage des 6 politiques
    for (int i = 0; i < 6; ++i) {
        std::cout << names[i] << " "
                  << vx[i] << " " << vy[i] << " "
                  << vw[i] << " " << vh[i] << " "
                  << mw[i] << " " << mh[i] << "\n";
    }

    // Calcul des bandes
    int bandes = 0;
    for (int i = 0; i < 6; ++i) {
        if (vw[i] < W || vh[i] < H) {
            bandes++;
        }
    }

    bool deformation = (!no_ref) && (W * RH != H * RW);

    std::cout << "BANDES " << bandes << "\n";
    std::cout << "DEFORMATION " << (deformation ? "OUI" : "NON") << "\n";

    return 0;
}