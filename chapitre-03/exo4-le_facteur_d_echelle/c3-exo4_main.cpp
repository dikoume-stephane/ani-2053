#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include "NKEvent/NkKeyboardEvent.h"
#include "NKEvent/NkWindowEvent.h"
#include <iostream>
#include <iomanip>

using namespace nkentseu;

void PrintScaleInfo(NkWindow& window) {
    math::NkVec2u windowSize = window.GetSize();
    float renderSizeW = window.GetSurfaceDesc().width;
    float renderSizeH = window.GetSurfaceDesc().height;
    float scale      = window.GetDpiScale();

    std::cout << "--------------------------------------------------\n"
              << "Taille Config (Demandee)    : " << windowSize.x << " x " << windowSize.y << " px\n"
              << "Taille Cible Rendu (GPU)    : " << renderSizeW << " x " << renderSizeH << " px\n"
              << "Facteur d'Echelle (DPI)     : " << std::fixed << std::setprecision(2) << scale << "\n"
              << "--------------------------------------------------" << std::endl;
}

int nkmain(const NkEntryState& state) {
    NkWindowConfig cfg;
    cfg.title  = "Exo4 - Le facteur d'echelle";
    cfg.width  = 800;
    cfg.height = 600;

    NkWindow window(cfg);
    if (!window.IsOpen()) {
        return -1;
    }

    // Affichage des informations au démarrage
    std::cout << "\n=== INFORMATIONS D'ÉCHELLE AU DÉMARRAGE ===" << std::endl;
    PrintScaleInfo(window);

    while (window.IsOpen()) {
        while (NkEvent* ev = NkEvents().PollEvent()) {
            if (ev->Is<NkWindowCloseEvent>()) {
                window.Close();
            }
            else if (auto* kp = ev->As<NkKeyPressEvent>()) {
                if (kp->GetKey() == NkKey::NK_ESCAPE) {
                    window.Close();
                }
            }
        }
    }

    return 0;
}
