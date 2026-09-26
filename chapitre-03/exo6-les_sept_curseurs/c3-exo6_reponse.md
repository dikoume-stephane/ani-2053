# Chapitre 03 — Exercice 6 : Les sept curseurs

## 1. Code source ([`c3-exo6_main.cpp`](c3-exo6_main.cpp))

Le programme divise la surface de la fenêtre en 7 zones verticales. Le survol de chaque zone déclenche une mise à jour du curseur via l'appel `window.SetCursor(NkWindow::NkCursorType::...)`.

```cpp
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include "NKEvent/NkKeyboardEvent.h"
#include "NKEvent/NkWindowEvent.h"
#include <iostream>

using namespace nkentseu;

// Les 7 types de curseurs 
const NkWindow::NkCursorType cursors[7] = {
    NkWindow::NkCursorType::Arrow, 
    NkWindow::NkCursorType::TextInput,
    NkWindow::NkCursorType::Hand,
    NkWindow::NkCursorType::ResizeNS, 
    NkWindow::NkCursorType::ResizeWE, 
    NkWindow::NkCursorType::ResizeNWSE,
    NkWindow::NkCursorType::ResizeNESW 
};

int nkmain(const NkEntryState& state) {
    NkWindowConfig cfg;
    cfg.title  = "Exo6 - Les sept curseurs";
    cfg.width  = 800;
    cfg.height = 600;

    NkWindow window(cfg);
    if (!window.IsOpen()) {
        return -1;
    }

   
    window.SetCursor(NkWindow::NkCursorType::Hand);

    int currentZone = -1;

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
            // Détection du déplacement de la souris
            else if (auto* mm = ev->As<NkMouseMoveEvent>()) {
                float mouseX = static_cast<float>(mm->GetX());
                float windowWidth = static_cast<float>(window.GetSize().x);

                // Découpage en 7 zones égales
                float z_Width = windowWidth / 7.0f;
                int newZone = static_cast<int>(mouseX / z_Width);

                if (newZone < 0) newZone = 0;
                if (newZone > 6) newZone = 6;

                // Application du nouveau curseur lors du changement de zone
                if (newZone != currentZone) {
                    currentZone = newZone;
                    window.SetCursor(cursors[currentZone]);
                    std::cout << "Survol Zone " << currentZone << " -> Curseur modifie." << std::endl;
                }
            }
        }
    }

    return 0;
}

```

---

## 2. Découpage des 7 zones et types de curseurs

| Zone | Type de curseur (NkWindow::NkCursorType) | Description visuelle |
|---|---|---|
| Zone 0 | Arrow | Flèche standard |
| Zone 1 | TextInput | Curseur I-beam (saisie de texte)  |
| Zone 2 | Hand | Main (lien ou sélection) |
| Zone 3 | ResizeNS | Flèche de redimensionnement vertical  |
| Zone 4 | ResizeWE | Flèche de redimensionnement horizontal  |
| Zone 5 | ResizeNWSE | Flèche de redimensionnement diagonale |
| Zone 6 | ResizeNESW | Flèche de redimensionnement diagonale |

### sortie du terminal
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

Survol Zone 0 -> Curseur modifie.
Survol Zone 1 -> Curseur modifie.
Survol Zone 2 -> Curseur modifie.
Survol Zone 3 -> Curseur modifie.
Survol Zone 4 -> Curseur modifie.
Survol Zone 5 -> Curseur modifie.
Survol Zone 6 -> Curseur modifie.
Survol Zone 5 -> Curseur modifie.
Survol Zone 4 -> Curseur modifie.
Survol Zone 3 -> Curseur modifie.
Survol Zone 2 -> Curseur modifie.
Survol Zone 1 -> Curseur modifie.
Survol Zone 0 -> Curseur modifie.
Survol Zone 6 -> Curseur modifie.

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (62.36s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

---

## 3. Poser le curseur une seule fois au démarrage

### Description du comportement observé :

Si l'on appelle `window.SetCursor(NkWindow::NkCursorType::Hand)` une seule fois au lancement de la fenêtre et qu'aucun changement n'est effectué dans l'événement `NkMouseMoveEvent` :

**Curseur persistant :** La forme du curseur choisie (`Hand`) reste constante et figée sur l'intégralité de la zone cliente de la fenêtre.
