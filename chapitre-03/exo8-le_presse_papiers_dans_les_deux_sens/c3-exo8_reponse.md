# Chapitre 03 — Exercice 8 : Le presse-papiers dans les deux sens

## 1. Code source ([`c3-exo8_main.cpp`](c3-exo8_main.cpp))

```cpp
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include "NKEvent/NkKeyboardEvent.h"
#include "NKEvent/NkWindowEvent.h"
#include <iostream>

using namespace nkentseu;

// Transforme le texte du presse-papiers en majuscules 
void ClipboardText(NkWindow& window) {
    NkString text = window.GetClipboardText();
    if (text.Empty()) {
        std::cout << "[Texte] Aucun texte valide trouvé dans le presse-papiers." << std::endl;
        return;
    }

    std::cout << "[Texte] Contenu original : " << text.CStr() << std::endl;
    
    // Transformation du texte en majuscules
    text.ToUpper();

    window.SetClipboardText(text);
    std::cout << "\nTexte converti en majuscules et remis dans le presse papier : " << text.CStr();
}

// Inverse les couleurs de l'image
void ClipboardImage(NkWindow& window) {
    NkClipboardImage img;
    if (!window.GetClipboardImage(img) || !img.IsValid()) {
        std::cout << "\nAucune image valide trouvee dans le presse-papiers.";
        return;
    }

    std::cout << "\nImage recupere (" << img.width << "x" << img.height << "). inversion des couleurs en cour..";

    for (usize i = 0; i + 3 < img.pixels.Size(); i += 4) {
        img.pixels[i + 0] = static_cast<uint8>(255 - img.pixels[i + 0]); 
        img.pixels[i + 1] = static_cast<uint8>(255 - img.pixels[i + 1]); 
        img.pixels[i + 2] = static_cast<uint8>(255 - img.pixels[i + 2]); 
        // on peu laisser le canal Alpha (img.pixels[i + 3])
    }

    if (window.SetClipboardImage(img)) {
        std::cout << "\nl'image est dans le presse papier!";
    } else {
        std::cout << "\nÉchec de l'ajout de l'image dans le presse papier.";
    }
}

int nkmain(const NkEntryState& state) {
    NkWindowConfig cfg;
    cfg.title  = "Exo8 - Le presse-papiers dans les deux sens";
    cfg.width  = 800;
    cfg.height = 600;

    NkWindow window(cfg);
    if (!window.IsOpen()) {
        return -1;
    }

    std::cout << "=================== INSTRUCTIONS ===================" << std::endl;
    std::cout << " Appuyez sur [T] : Convertir le texte en MAJUSCULES" << std::endl;
    std::cout << " Appuyez sur [I] : INVERSER les couleurs de l'image" << std::endl;
    std::cout << " Appuyez sur [ESC] : Quitter" << std::endl;
    std::cout << "====================================================" << std::endl;

    while (window.IsOpen()) {
        while (NkEvent* ev = NkEvents().PollEvent()) {
            if (ev->Is<NkWindowCloseEvent>()) {
                window.Close();
            }
            else if (auto* kp = ev->As<NkKeyPressEvent>()) {
                if (kp->GetKey() == NkKey::NK_ESCAPE) {
                    window.Close();
                }
                else if (kp->GetKey() == NkKey::NK_T) {
                    ClipboardText(window);
                }
                else if (kp->GetKey() == NkKey::NK_I) {
                    ClipboardImage(window);
                }
            }
        }
    }

    return 0;
}
```
## 2. sortie du terminal
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
 Appuyez sur [T] : Convertir le texte en MAJUSCULES
 Appuyez sur [I] : INVERSER les couleurs de l'image
 Appuyez sur [ESC] : Quitter
====================================================
[Texte] Contenu original : [Texte] Aucun texte valide trouv├® dans le presse-papiers.

Texte converti en majuscules et remis dans le presse papier : [TEXTE] AUCUN TEXTE VALIDE TROUV├® DANS LE PRESSE-PAPIERS.
Image recupere (803x633). inversion des couleurs en cour..
l'image est dans le presse papier!
Image recupere (803x633). inversion des couleurs en cour..
l'image est dans le presse papier!
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (619.92s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```
## 3.  Explications du fonctionnement
* Traitement du texte : La méthode window.`GetClipboardText()` permet de récupérer la chaîne courante stockée depuis le presse-papiers Windows.La méthode `text.ToUpper()` transforme chaque caractère de la chaîne NkString en majuscule et `window.SetClipboardText(text)`  injecte la nouvelle chaîne convertie.
* Traitement de l'image : `window.GetClipboardImage(img)` extrait les données de l'image depuis le presse papiers et décode l'image sous forme de tableau de pixels .   Inversion des couleurs : La boucle parcourt le vecteur de pixels par blocs de 4 octets (R, G, B, A). Chaque composante de couleur primaire est inversée selon la formule `inverse = 255 - couleur`.`window.SetClipboardImage(img)` réassemble l'image et la renvot dans presse-papiers.