# Chapitre 03 — Exercice 7 : Le glisser qui sort

## 1. Code source ([`c3-exo7_main.cpp`](c3-exo7_main.cpp))

```cpp
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

```
---
## sorties du terminal
```powershell
 jenga run

╔══════════════════════════════════════════════════════════════════╗
║                                                                  ║
║                ██╗███████╗███╗   ██╗ ██████╗  █████╗             ║
║                ██║██╔════╝████╗  ██║██╔════╝ ██╔══██╗            ║
║                ██║█████╗  ██╔██╗ ██║██║  ███╗███████║            ║
║           ██   ██║██╔══╝  ██║╚██╗██║██║   ██║██╔══██║            ║
║           ╚█████╔╝███████╗██║ ╚████║╚██████╔╝██║  ██║            ║
║            ╚════╝ ╚══════╝╚═╝  ╚═══╝ ╚═════╝ ╚═╝  ╚═╝            ║
║                                                                  ║
║             Multi-platform C/C++ Build System v2.8.0             ║
║                                                                  ║
╚══════════════════════════════════════════════════════════════════╝


━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ▶  EXECUTION  —  window.exe
     D:\2DS\projet\programmation_cpp\Firt_window\Firtwindow\Build\Bin\Debug-Windows\window\window.exe
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

Mode Capture : ACTIVE
Appuyez sur 'C' pour activer/desactiver window.CaptureMouse()
[debut du glisse] (X: 657, Y: 242)
Glisser... Position (X: 658, Y: 242)
Glisser... Position (X: 659, Y: 240)
Glisser... Position (X: 669, Y: 237)
Glisser... Position (X: 681, Y: 231)
Glisser... Position (X: 693, Y: 227)
Glisser... Position (X: 703, Y: 225)
Glisser... Position (X: 714, Y: 222)
Glisser... Position (X: 722, Y: 221)
Glisser... Position (X: 731, Y: 220)
Glisser... Position (X: 743, Y: 219)
Glisser... Position (X: 755, Y: 217)
Glisser... Position (X: 761, Y: 216)
Glisser... Position (X: 766, Y: 216)
Glisser... Position (X: 779, Y: 215)
Glisser... Position (X: 786, Y: 215)
Glisser... Position (X: 800, Y: 214)
Glisser... Position (X: 807, Y: 213)
Glisser... Position (X: 819, Y: 212)
Glisser... Position (X: 830, Y: 210)
Glisser... Position (X: 835, Y: 210)
Glisser... Position (X: 846, Y: 207)
Glisser... Position (X: 856, Y: 207)
Glisser... Position (X: 862, Y: 206)
Glisser... Position (X: 869, Y: 206)
Glisser... Position (X: 874, Y: 205)
Glisser... Position (X: 879, Y: 205)
Glisser... Position (X: 886, Y: 205)
Glisser... Position (X: 890, Y: 205)
Glisser... Position (X: 896, Y: 205)
Glisser... Position (X: 901, Y: 204)
Glisser... Position (X: 905, Y: 204)
Glisser... Position (X: 915, Y: 203)
Glisser... Position (X: 919, Y: 203)
Glisser... Position (X: 922, Y: 203)
Glisser... Position (X: 926, Y: 202)
Glisser... Position (X: 927, Y: 202)
Glisser... Position (X: 930, Y: 202)
Glisser... Position (X: 931, Y: 202)
Glisser... Position (X: 932, Y: 202)
Glisser... Position (X: 933, Y: 202)
Glisser... Position (X: 934, Y: 202)
Glisser... Position (X: 935, Y: 202)
Glisser... Position (X: 949, Y: 201)
Glisser... Position (X: 960, Y: 200)
Glisser... Position (X: 964, Y: 200)
[fin du gilsse] (X: 964, Y: 200)
-> Mode Capture : DESACTIVE
[debut du glisse] (X: 702, Y: 233)
Glisser... Position (X: 704, Y: 233)
Glisser... Position (X: 711, Y: 232)
Glisser... Position (X: 742, Y: 224)
Glisser... Position (X: 793, Y: 244)
Glisser... Position (X: 786, Y: 246)
Glisser... Position (X: 783, Y: 247)
Glisser... Position (X: 776, Y: 249)
Glisser... Position (X: 767, Y: 252)
Glisser... Position (X: 760, Y: 253)
Glisser... Position (X: 753, Y: 255)
Glisser... Position (X: 746, Y: 256)
Glisser... Position (X: 740, Y: 257)
Glisser... Position (X: 733, Y: 259)
Glisser... Position (X: 729, Y: 260)
Glisser... Position (X: 725, Y: 261)
Glisser... Position (X: 722, Y: 262)
Glisser... Position (X: 719, Y: 262)
Glisser... Position (X: 717, Y: 262)
Glisser... Position (X: 716, Y: 263)
Glisser... Position (X: 715, Y: 263)
Glisser... Position (X: 714, Y: 263)
Glisser... Position (X: 713, Y: 263)
Glisser... Position (X: 714, Y: 263)
Glisser... Position (X: 715, Y: 263)
Glisser... Position (X: 716, Y: 263)
Glisser... Position (X: 732, Y: 260)
Glisser... Position (X: 752, Y: 257)
Glisser... Position (X: 760, Y: 256)
Glisser... Position (X: 772, Y: 254)
Glisser... Position (X: 784, Y: 253)
Glisser... Position (X: 797, Y: 253)
Glisser... Position (X: 796, Y: 174)
Glisser... Position (X: 793, Y: 175)
Glisser... Position (X: 791, Y: 175)
Glisser... Position (X: 790, Y: 176)
Glisser... Position (X: 789, Y: 176)
Glisser... Position (X: 788, Y: 176)
Glisser... Position (X: 787, Y: 176)
Glisser... Position (X: 786, Y: 176)
Glisser... Position (X: 785, Y: 176)
Glisser... Position (X: 784, Y: 176)
Glisser... Position (X: 782, Y: 177)
Glisser... Position (X: 779, Y: 177)
Glisser... Position (X: 778, Y: 177)
[debut du glisse] (X: 778, Y: 177)
[fin du gilsse] (X: 778, Y: 177)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (577.89s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

---

## 2. Analyse et point de vue de l'utilisateur

### Sans capture de la souris (`window.CaptureMouse(false)`)
Lorsque l'utilisateur presse le bouton dans la fenêtre et déplace le curseur au-delà des bordures, le glisser s'interrompt brusquement au bord de la fenêtre et le programme arret de donner les coordonnées de la sourie.
on peut donc dire que dès que le curseur sort du cadre, la fenêtre cesse de recevoir les événements de mouvement.et  Si le bouton est relâché à l'extérieur, l'événement `NkMouseReleaseEvent` n'est pas transmis à l'application.

### Avec capture de la souris (`window.CaptureMouse(true)`)
L'utilisateur commence son glisser dans la fenêtre et peut le continuer de manière fluide à l'extérieur.
La fenêtre continue de recevoir tous les événements de mouvement et de bouton jusqu'au relâchement de ceux ci, même si le curceur se trouve physiquement hors du cadre de la fenetre.
