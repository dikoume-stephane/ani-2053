# Chapitre 03 — Exercice 4 : Le facteur d'échelle

## 1. Code source ([`c3-exo4_main.cpp`](c3-exo4_main.cpp))

Le code utilise les méthodes disponibles dans la classe `NkWindow` (`GetConfig()`, `GetSize()`, `GetDpiScale()`) pour mesurer les dimensions de la fenêtre et le facteur d'échelle du moniteur.

```cpp
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

```

---

## 2. Relevés d'exécution

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
Taille Fenetre (Zone client): 798 x 592 px
Taille Cible Rendu (GPU)    : 997 x 740 px
Facteur d'Echelle (DPI)     : 1.25
--------------------------------------------------

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (12.40s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
PS D:\2DS\projet\programmation_cpp\Firt_window\Firtwindow> 
```

---

* **on obtient donc :**
>   - Taille Fenetre (Zone client): 798 x 592 px
>   - Taille Cible Rendu (GPU)    : 997 x 740 px
>   - Facteur d'Echelle (DPI)     : 1.25

## 3. Constats et analyse du comportement de l'API

1. **Absence de méthode explicite du genre `GetRenderTargetSize()` :** L'objet `NkWindow` ne fournit pas directement de fonction dédiée au calcul de la cible de rendu physique. Il met à disposition `GetSize()` pour la taille de zone cliente et `GetDpiScale()` pour obtenir le facteur d'échelle.
2. **Ajustement des dimensions par le système (798 × 592 px) :** Bien qu'une taille de $800 \times 600$ soit spécifiée dans la configuration initiale, le système d'exploitation adapte la zone cliente utile de la fenêtre en tenant compte des bordures et de la mise à l'échelle DPI, ce qui ramène la surface réelle d'affichage à $798 \times 592$ pixels.
3. **Déduction de la taille physique GPU :** Pour obtenir la véritable résolution de rendu en pixels physiques sur le processeur graphique, il convient de multiplier la taille renvoyée par `GetSize()` par la valeur de `GetDpiScale()` ($798 \times 1.25 = 997.5 \approx 997$ pixels en largeur, et $592 \times 1.25 = 740$ pixels en hauteur).
