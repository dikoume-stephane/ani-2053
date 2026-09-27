#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include "NKEvent/NkWindowEvent.h"
#include <iostream>

using namespace nkentseu;

int nkmain(const NkEntryState& state) {
    // Configuration de la premiere fenetre
    NkWindowConfig cfg1;
    cfg1.title  = "Exo11 - Fenetre 1";
    cfg1.width  = 400;
    cfg1.height = 300;
    cfg1.x      = 100;
    cfg1.y      = 200;

    // Configuration de la deuxieme fenetre
    NkWindowConfig cfg2;
    cfg2.title  = "Exo11 - Fenetre 2";
    cfg2.width  = 400;
    cfg2.height = 300;
    cfg2.x      = 550;
    cfg2.y      = 200;

    NkWindow win1(cfg1);
    NkWindow win2(cfg2);

    if (!win1.IsOpen() || !win2.IsOpen()) {
        return -1;
    }

    while (win1.IsOpen() || win2.IsOpen()) {
        while (NkEvent* ev = NkEvents().PollEvent()) {
            // Traitement de la fermeture individuelle des fenetres
            if (ev->Is<NkWindowCloseEvent>()) {
                if (ev->GetWindowId() == win1.GetId()) {
                    std::cout << "\n[Fermeture] fenetre 1 fermee.";
                    win1.Close();
                }
                else if (ev->GetWindowId() == win2.GetId()) {
                    std::cout << "\n[Fermeture] fenetre 2 fermee.";
                    win2.Close();
                }
            }
            // Fermeture des deux avec la touche Echap
            else if (auto* kp = ev->As<NkKeyPressEvent>()) {
                if (kp->GetKey() == NkKey::NK_ESCAPE) {
                    win1.Close();
                    win2.Close();
                }
            }
            // Identification de la fenetre quirecoit le clic
            else if (auto* mp = ev->As<NkMouseButtonPressEvent>()) {
                if (ev->GetWindowId() == win1.GetId()) {
                    std::cout << "\n[CLIC] Recu par FENETRE 1 (bouton: " 
                              << static_cast<int>(mp->GetButton()) 
                              << ", X: " << mp->GetX() << ", Y: " << mp->GetY() << ")";
                }
                else if (ev->GetWindowId() == win2.GetId()) {
                    std::cout << "\n[CLIC] Recu par FENETRE 2 (bouton: " 
                              << static_cast<int>(mp->GetButton()) 
                              << ", X: " << mp->GetX() << ", Y: " << mp->GetY() << ")";
                }
            }
        }
    }

    return 0;
}
