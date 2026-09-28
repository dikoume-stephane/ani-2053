# Chapitre 03 — Démo 3 : La fenêtre sans bordure et la perte de la barre système

## 1. Fonctionnement de la fenêtre sans bordure personnalisée

Lorsque la fenêtre est configurée sans bordure native (`cfg.borderless = true`), l'ensemble des comportements d'une barre de titre classique doit être réimplémenté manuellement :

* **Déplacement (Glisser-déplacer) :** Un clic enfoncé dans la zone supérieure ($Y \le 35\text{ px}$) capture la souris (`CaptureMouse(true)`) et calcule le vecteur de déplacement relatif entre la position du curseur et l'origine de la fenêtre pour mettre à jour la position via `SetPosition()`.
* **Agrandissement / Restauration :** 
  * Un double-clic rapide Delta t < 300ms dans la barre de titre bascule entre l'état maximisé (`Maximize()`) et restauré (`Restore()`).
  * Un clic sur la zone virtuelle du bouton déclenche le meme comportement.
* **Boutons de contrôle virtuels :** Les zones de collision (*hitboxes*) à l'extrême droite de la zone supérieure interceptent les clics pour déclencher la réduction en barre des tâches (`Minimize()`) ou la fermeture (`Close()`).

---

## 2. Ce qui est perdu par rapport à la barre de titre système

En supprimant la décoration native gérée par le gestionnaire de fenêtres du système d'exploitation, plusieurs fonctionnalités clés sont perdues :

| Fonctionnalité | Description de la perte |
| :--- | :--- |
| **Ancrage de la fenetre** | Perte du menu de disposition des fenêtres au survol du bouton d'agrandissemen |
| **Menu contextuel système** | Indisponibilité du menu système natif accessible par clic droit sur la barre de titre ou par le raccourci `Alt + Espace` (restaurer, déplacer, taille, réduire, agrandir, fermer). |
| **apparence** |perte de l'apparence de la barre de titre du sytheme et de celle des boutons (la notre est invisible avec ses boutons ). |
| **Thème et intégration OS** | La barre de titre personnalisée ne suit plus automatiquement le mode sombre/clair global du système ni les couleurs définies par l'utilisateur. |

---
## 3. test
<video src="demo3.mp4" controls width="640" height="360">
    `demonstration video`
</video>
---

## 4. code source
```cpp
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include "NKEvent/NkWindowEvent.h"
#include <iostream>
#include <chrono>

using namespace nkentseu;

int nkmain(const NkEntryState& state) {
    NkWindowConfig cfg;
    cfg.title      = "Exo10 - La fenetre sans bordure";
    cfg.width      = 800;
    cfg.height     = 600;
    cfg.frame = false; // Retire la barre de titre native et les bordures du systeme

    NkWindow window(cfg);
    if (!window.IsOpen()) {
        return -1;
    }

    // Dimensions de la barre de titre personnalisee
    const float titleBarHeight = 35.0f;
    const float buttonWidth    = 40.0f;

    // Etats pour le deplacement et la fenetre
    bool isDragging = false;
    math::NkVector2i dragStartMouseRel;
    math::NkVector2i dragStartWindowPos;
    bool isMaximized = false;

    // Gestion du double-clic
    auto lastClickTime = std::chrono::steady_clock::now();

    std::cout << "=================== INSTRUCTIONS ===================" << std::endl;
    std::cout << " Fenetre sans bordure creee avec succes." << std::endl;
    std::cout << " Barre de titre virtuelle : Zone superieure (Y = 0 a 35 px)" << std::endl;
    std::cout << " Boutons virtuels :" << std::endl;
    std::cout << " Fermer : Extremiite droite" << std::endl;
    std::cout << " Agrandir : A gauche du bouton Fermer" << std::endl;
    std::cout << " Reduire : A gauche du bouton Agrandir" << std::endl;
    std::cout << " Clic + Glisser sur le titre : Deplace la fenetre" << std::endl;
    std::cout << " Double-clic sur le titre : Agrandit ou restaure" << std::endl;
    std::cout << " Touche [ESC] : Quitter" << std::endl;
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
            }
            // Interception des clics de la souris
            else if (auto* mp = ev->As<NkMouseButtonPressEvent>()) {
                if (mp->GetButton() == NkMouseButton::NK_MB_LEFT) {
                    float mx = static_cast<float>(mp->GetX());
                    float my = static_cast<float>(mp->GetY());
                    float winWidth = static_cast<float>(window.GetSize().x);

                    // Verification si le clic s'effectue dans la barre de titre (Y <= 35)
                    if (my <= titleBarHeight) {
                        float btnCloseStart = winWidth - buttonWidth;
                        float btnMaxStart   = winWidth - (2.0f * buttonWidth);
                        float btnMinStart   = winWidth - (3.0f * buttonWidth);

                        // 1. Bouton Fermer
                        if (mx >= btnCloseStart) {
                            std::cout << "Clic -> Fermer la fenetre" << std::endl;
                            window.Close();
                        }
                        // 2. Bouton Agrandir
                        else if (mx >= btnMaxStart) {
                            std::cout << "Clic -> Agrandir" << std::endl;
                            isMaximized = !isMaximized;
                            if (isMaximized) window.Maximize();
                            else window.Restore();
                        }
                        // 3. Bouton Reduire
                        else if (mx >= btnMinStart) {
                            std::cout << "Clic -> Reduire la fenetre" << std::endl;
                            window.Minimize();
                        }
                        // 4. Zone neutre du titre : Deplacement ou Double-Clic
                        else {
                            auto now = std::chrono::steady_clock::now();
                            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastClickTime).count();
                            lastClickTime = now;

                            if (elapsed < 300) { // Clics espaces de moins de 300ms
                                std::cout << "Double-clic -> Agrandir" << std::endl;
                                isMaximized = !isMaximized;
                                if (isMaximized) window.Maximize();
                                else window.Restore();
                            } else {
                                // Debut du glisser
                                isDragging = true;
                                window.CaptureMouse(true);
                                dragStartMouseRel = math::NkVector2i(mp->GetX(), mp->GetY());
                                dragStartWindowPos = window.GetPosition();
                            }
                        }
                    }
                }
            }
            // Relachement de la souris
            else if (auto* mr = ev->As<NkMouseButtonReleaseEvent>()) {
                if (mr->GetButton() == NkMouseButton::NK_MB_LEFT && isDragging) {
                    isDragging = false;
                    window.CaptureMouse(false);
                    std::cout << "Fin de deplacement" << std::endl;
                }
            }
            // Deplacement de la souris pendant le glisser
            else if (auto* mm = ev->As<NkMouseMoveEvent>()) {
                if (isDragging) {
                    math::NkVector2i currentMouseRel(mm->GetX(), mm->GetY());
                    math::NkVector2i currentWindowPos = window.GetPosition();
                    
                    // Calcul de la nouvelle position globale de la fenetre
                    math::NkVector2i newWindowPos = currentWindowPos + (currentMouseRel - dragStartMouseRel);
                    window.SetPosition(newWindowPos);
                }
            }
        }
    }

    return 0;
}
``