#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include "NKEvent/NkKeyboardEvent.h"
#include "NKEvent/NkWindowEvent.h"
#include <iostream>
#include <iomanip>

using namespace nkentseu;

void PrintScaleInfo(NkWindow& window) {
    float windowSizeH = window.GetConfig().height;
    float windowSizeW = window.GetConfig().width;
    math::NkVec2u renderSize = window.GetSize();
    float scale      = window.GetDpiScale();

    // Calcul de la taille physique réelle sur le GPU (Taille utile x DPI)
    uint32 gpuWidth  = static_cast<uint32>(renderSize.x * scale);
    uint32 gpuHeight = static_cast<uint32>(renderSize.y * scale);

    std::cout << "--------------------------------------------------\n"
              << "Taille Config (Demandee)    : " << windowSizeW << " x " << windowSizeH << " px\n"
              << "Taille Fenetre (Zone client): " << renderSize.x << " x " << renderSize.y << " px\n"
              << "Taille Cible Rendu (GPU)    : " << gpuWidth << " x " << gpuHeight << " px\n"
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
