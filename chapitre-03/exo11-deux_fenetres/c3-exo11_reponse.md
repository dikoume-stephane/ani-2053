# Chapitre 03 — Exercice 11 : Deux fenêtres

## 1. Code source ([`c3-exo11_main.cpp`](c3-exo11_main.cpp))

Le programme instancie deux fenêtres distinctes (`win1` et `win2`) et interroge la boucle d'événements globale `NkEvents().PollEvent()`. L'identifiant de la fenêtre cible (`ev->GetWindowId()`) permet de voir quelle fenêtre a reçu chaque clic.

```cpp
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

```
## 2. sorties du terminal

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


[CLIC] Recu par FENETRE 1 (bouton: 2, X: 268, Y: 116)
[CLIC] Recu par FENETRE 1 (bouton: 1, X: 202, Y: 115)
[CLIC] Recu par FENETRE 2 (bouton: 2, X: 177, Y: 204)
[CLIC] Recu par FENETRE 2 (bouton: 1, X: 109, Y: 102)
[Fermeture] fenetre 2 fermee.
[Fermeture] fenetre 1 fermee.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (15.31s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
PS D:\2DS\projet\programmation_cpp\Firt_window\Firtwindow> 
```

## 3. Ce qui manque pour dessiner dans les deux fenêtres
* un contexte de rendu (renderer comme dans la sdl3).Chaque fenêtre doit posséder son propre contexte graphique.
* in systeme de gestion de cible de contexte pour les dessins.