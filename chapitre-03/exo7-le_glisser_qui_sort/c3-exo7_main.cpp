#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include "NKEvent/NkKeyboardEvent.h"
#include "NKEvent/NkWindowEvent.h"
#include <iostream>

using namespace nkentseu;

int nkmain(const NkEntryState& state) {
    NkWindowConfig cfg;
    cfg.title  = "Exo7 - Le glisser qui sort";
    cfg.width  = 800;
    cfg.height = 600;

    NkWindow window(cfg);
    if (!window.IsOpen()) {
        return -1;
    }

    bool isDragging = false;
    bool useCapture = true;

    std::cout << "Mode Capture : " << (useCapture ? "ACTIVE" : "DESACTIVE");
    std::cout << "\nAppuyez sur 'C' pour activer/desactiver window.CaptureMouse()";

    while (window.IsOpen()) {
        while (NkEvent* ev = NkEvents().PollEvent()) {
            if (ev->Is<NkWindowCloseEvent>()) {
                window.Close();
            }
            else if (auto* kp = ev->As<NkKeyPressEvent>()) {
                if (kp->GetKey() == NkKey::NK_ESCAPE) {
                    window.Close();
                }
                else if (kp->GetKey() == NkKey::NK_C) {
                    useCapture = !useCapture;
                    std::cout << "\n-> Mode Capture : " << (useCapture ? "ACTIVE" : "DESACTIVE");
                }
            }
            
            else if (auto* mp = ev->As<NkMouseButtonPressEvent>()) {
                if (mp->GetButton() == NkMouseButton::NK_MB_LEFT) {
                    isDragging = true;
                    if (useCapture) {
                        window.CaptureMouse(true);
                    }
                    std::cout << "\n[debut du glisse] (X: " << mp->GetX() << ", Y: " << mp->GetY() << ")";
                }
            }
            
            else if (auto* mr = ev->As<NkMouseButtonReleaseEvent>()) {
                if (mr->GetButton() == NkMouseButton::NK_MB_LEFT && isDragging) {
                    isDragging = false;
                    if (useCapture) {
                        window.CaptureMouse(false);
                    }
                    std::cout << "\n[fin du gilsse] (X: " << mr->GetX() << ", Y: " << mr->GetY() << ")";
                }
            }
            
            else if (auto* mm = ev->As<NkMouseMoveEvent>()) {
                if (isDragging) {
                    std::cout << "\nGlisser... Position (X: " << mm->GetX() << ", Y: " << mm->GetY() << ")";
                }
            }
        }
    }

    return 0;
}