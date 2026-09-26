# Chapitre 03 — Exercice 4 : Le facteur d'échelle

## 1. Code source ([`c3-exo4_main.cpp`](c3-exo4_main.cpp))

Le code utilise les méthodes disponibles dans la classe `NkWindow` (`window.GetSurfaceDesc()`, `GetSize()`, `GetDpiScale()`) pour mesurer les dimensions de la fenêtre et le facteur d'échelle du moniteur.

```cpp
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

```

---

## 2. Relevés d'exécution
* premier run avec une mise à l'echelle de 125%.

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


=== INFORMATIONS D'├ëCHELLE AU D├ëMARRAGE ===
--------------------------------------------------
Taille Config (Demandee)    : 798 x 592 px
Taille Cible Rendu (GPU)    : 798 x 592 px
Facteur d'Echelle (DPI)     : 1.25
--------------------------------------------------

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (12.14s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

* **on obtient donc :**
>   - Taille Fenetre (Zone client): 798 x 592 px
>   - Taille Cible Rendu (GPU)    : 798 x 592 px
>   - Facteur d'Echelle (DPI)     : 1.25

---
* deuxieme run avec une mise à l'echelle de 150% (modifiée dans les paramettres de l'ecran)
```powershell 

D:\2DS\projet\programmation_cpp\Firt_window\Firtwindow> jenga run

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


=== INFORMATIONS D'├ëCHELLE AU D├ëMARRAGE ===
--------------------------------------------------
Taille Config (Demandee)    : 794 x 583 px
Taille Cible Rendu (GPU)    : 794 x 583 px
Facteur d'Echelle (DPI)     : 1.50
--------------------------------------------------

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (3.35s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

---

* **on obtient donc :**
>   - Taille Fenetre (Zone client): 794 x 583 px
>   - Taille Cible Rendu (GPU)    : 794 x 583 px
>   - Facteur d'Echelle (DPI)     : 1.50

## 3. Constats et analyse du comportement de l'API

1. dans le premier test, on constate que la cible du rendu et la zone client ont la meme taille soit `798 x 592 px`
3. dans le deuxieme test , apres avoir modifié la mise à l'echelle dans les parammetres, on costate que les valeurs de la zone client et de la cible de rendu envolues ensemble en passant de `798 x 592 à 794 x 583 px`. 
2. **Ajustement des dimensions par le système (798 × 592 px) :** Bien qu'une taille de $800 \times 600$ soit spécifiée dans la configuration initiale, le système d'exploitation adapte la zone cliente utile de la fenêtre en tenant compte des bordures et de la mise à l'échelle DPI, ce qui ramène la surface réelle d'affichage à $798 \times 592$ pixels.

