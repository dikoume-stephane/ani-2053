# Chapitre 03 — Exercice 12 : L'inventaire des écrans

## 1. Code source ([`c3-exo12_main.cpp`](c3-exo12_main.cpp))

Le programme effectue l'inventaire des écrans connectés au système et surveille la position de la fenêtre pour mettre à jour l'écran hôte en temps réel lors du déplacement.

```cpp
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include "NKEvent/NkWindowEvent.h"
#include <iostream>

using namespace nkentseu;

// Parcourt les écrans connectés et identifie celui contenant la fenêtre
void ListMonitors(const NkWindow& window) {
    auto monitors = window.EnumerateMonitors();
    auto currentM = window.GetCurrentMonitor();
    math::NkVector2i winPos = window.GetPosition();
    math::NkVector2i winSize = window.GetSize();
    bool containsWindow;
    
    std::cout << "\n================ INVENTAIRE DES ECRANS ================" << std::endl;
    std::cout << "Nombre d'ecrans detectes : " << window.GetMonitorCount() << std::endl;

    for (usize i = 0; i < monitors.Size(); ++i) {
        const auto& mon = monitors[i];
        float scale = mon.dpiScale;      // Facteur d'échelle (DPI Scale)
        if ( mon.index == window.GetCurrentMonitor().index) containsWindow =true ;
        std::cout << "Ecran #" << (i + 1) << " : " << mon.name << std::endl;
        std::cout << "  - Position       : (" << mon.posX << ", " << mon.posY << ")" << std::endl;
        std::cout << "  - Resolution     : " << mon.width << " x " << mon.height << " px" << std::endl;
        std::cout << "  - Echelle (DPI)  : " << scale << "x (" << static_cast<int>(scale * 100) << "%)" << std::endl;
        std::cout << "  - Porteur de Fenetre : " << (containsWindow ? " OUI (Fenetre active est ici) " : "Non") << std::endl;
        std::cout << "------------------------------------------------------" << std::endl;
    }
}

int nkmain(const NkEntryState& state) {
    NkWindowConfig cfg;
    cfg.title  = "Exo12 - L'inventaire des ecrans";
    cfg.width  = 800;
    cfg.height = 600;

    NkWindow window(cfg);
    if (!window.IsOpen()) {
        return -1;
    }

    std::cout << "=================== INSTRUCTIONS ===================" << std::endl;
    std::cout << " Deplacez la fenetre d'un ecran a un autre." << std::endl;
    std::cout << " Appuyez sur [I] ou [ESPACE] : Forcer la mise a jour de l'inventaire." << std::endl;
    std::cout << " Appuyez sur [ESC]          : Quitter." << std::endl;
    std::cout << "====================================================" << std::endl;

    // Inventaire initial à l'ouverture
    ListMonitors(window);

    usize lastMonitorIndex = static_cast<usize>(-1);

    while (window.IsOpen()) {
        while (NkEvent* ev = NkEvents().PollEvent()) {
            if (ev->Is<NkWindowCloseEvent>()) {
                window.Close();
            }
            else if (auto* kp = ev->As<NkKeyPressEvent>()) {
                if (kp->GetKey() == NkKey::NK_ESCAPE) {
                    window.Close();
                }
                else if (kp->GetKey() == NkKey::NK_I || kp->GetKey() == NkKey::NK_SPACE) {
                    ListMonitors(window);
                }
            }
            // Détection automatique du changement d'écran lors du déplacement
            else if (ev->Is<NkWindowMoveEvent>()) {

                auto monitors = window.EnumerateMonitors();
                for (usize i = 0; i < monitors.Size(); ++i) {
                    if (monitors[i].index == window.GetCurrentMonitor().index) {
                        if (i != lastMonitorIndex) {
                            lastMonitorIndex = i;
                            std::cout << "\n[Changement d'ecran] La fenetre est maintenant sur l'ecran " << (i + 1) << std::endl;
                            ListMonitors(window);
                        }
                        break;
                    }
                }
            }
        }
    }

    return 0;
}

```
## sortie du terminal

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

=================== INSTRUCTIONS ===================
 Deplacez la fenetre d'un ecran a un autre.
 Appuyez sur [I] ou [ESPACE] : Forcer la mise a jour de l'inventaire.
 Appuyez sur [ESC]          : Quitter.
====================================================

================ INVENTAIRE DES ECRANS ================
Nombre d'ecrans detectes : 1
Ecran #1 : \\.\DISPLAY1
  - Position       : (0, 0)
  - Resolution     : 1920 x 1080 px
  - Echelle (DPI)  : 1.25x (125%)
  - Porteur de Fenetre :  OUI (Fenetre active est ici) 
------------------------------------------------------

[Changement d'ecran] La fenetre est maintenant sur l'ecran #1

================ INVENTAIRE DES ECRANS ================
Nombre d'ecrans detectes : 1
Ecran #1 : \\.\DISPLAY1
  - Position       : (0, 0)
  - Resolution     : 1920 x 1080 px
  - Echelle (DPI)  : 1.25x (125%)
  - Porteur de Fenetre :  OUI (Fenetre active est ici) 
------------------------------------------------------

================ INVENTAIRE DES ECRANS ================
Nombre d'ecrans detectes : 1
Ecran #1 : \\.\DISPLAY1
  - Position       : (0, 0)
  - Resolution     : 1920 x 1080 px
  - Echelle (DPI)  : 1.25x (125%)
  - Porteur de Fenetre :  OUI (Fenetre active est ici) 
------------------------------------------------------

================ INVENTAIRE DES ECRANS ================
Nombre d'ecrans detectes : 1
Ecran #1 : \\.\DISPLAY1
  - Position       : (0, 0)
  - Resolution     : 1920 x 1080 px
  - Echelle (DPI)  : 1.25x (125%)
  - Porteur de Fenetre :  OUI (Fenetre active est ici) 
------------------------------------------------------

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (40.43s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
PS D:\2DS\projet\programmation_cpp\Firt_window\Firtwindow> 
```
