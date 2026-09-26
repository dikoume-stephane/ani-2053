# Chapitre 03 — Exercice 2 : Les sept droits

## 1. Code source ([`c3-exo2_main.cpp`](c3-exo2_main.cpp))

Le code ci-dessous regroupe les sept propriétés de configuration de la fenêtre. Il suffit de passer manuellement chaque propriété à `false` une par une pour tester l'impact sur le comportement de la fenêtre[cite: 1]. La touche `ÉCHAP` est gérée pour permettre de fermer la fenêtre même lorsque le bouton de fermeture ou la barre de titre est désactivé[cite: 1, 2].

```cpp
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include "NKEvent/NkKeyboardEvent.h"
#include "NKEvent/NkWindowEvent.h"

using namespace nkentseu;

int nkmain(const NkEntryState& state) {
    NkWindowConfig cfg;
    cfg.title  = "Exo2 - Les sept droits";
    cfg.width  = 800;
    cfg.height = 600;

    // les 7 droits
    cfg.resizable = false; 
    cfg.movable = true;  
    cfg.closable = true;  
    cfg.minimizable = true;  
    cfg.maximizable = true;  
    cfg.canFullscreen = true; 
    cfg.fullscreen = true; 

    NkWindow window(cfg);
    if (!window.IsOpen()) {
        return -1;
    }

    while (window.IsOpen()) {
        while (NkEvent* ev = NkEvents().PollEvent()) {
            if (ev->Is<NkWindowCloseEvent>()) {
                window.Close();
            }
            else if (auto* kp = ev->As<NkKeyPressEvent>()) {
                // Touche ÉCHAP pour fermer 
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

## 2. Constats et impacts détaillés pour chaque cas

### Cas 1 : `cfg.resizable = false`

* **Droit désactivé :** Autorisation de redimensionner la fenêtre.


* **Impact utilisateur :** L'utilisateur **ne peut plus redimensionner** la fenêtre en étirant ses bordures ou ses coins avec la souris. Les curseurs de redimensionnement n'apparaissent pas au survol des bords.mais pendans les testes, le comportement attendu n'est pas celui qui à été soulevé. en passant la valeur sur true ou false, ça ne changais rien . 



---

### Cas 2 : `cfg.movable = false`

* **Droit désactivé :** Autorisation de déplacer la fenêtre.


* **Impact utilisateur :** L'utilisateur **ne peut plus déplacer** la fenêtre sur son écran en la faisant glisser par sa barre de titre. La fenêtre reste verrouillée à sa position initiale.mais pendans les testes, le comportement attendu n'est pas celui qui à été soulevé. en passant la valeur sur true ou false, ça ne changais rien . 



---

### Cas 3 : `cfg.closable = false`

* **Droit désactivé :** Autorisation de fermer la fenêtre via l'interface système.


* **Impact utilisateur :** L'utilisateur **ne peut plus fermer** la fenêtre en cliquant sur la croix système (le bouton est grisé ou inactif). La fermeture n'est possible que par programme ou via le raccourci clavier géré dans le code (touche `ÉCHAP`).mais pendans les testes, le comportement attendu n'est pas celui qui à été soulevé. en passant la valeur sur true ou false, ça ne changais rien . 



---

### Cas 4 : `cfg.minimizable = false`

* **Droit désactivé :** Autorisation de réduire la fenêtre.


* **Impact utilisateur :** L'utilisateur **ne peut plus réduire** la fenêtre dans la barre des tâches. Le bouton de réduction de la barre de titre est absent ou grisé.mais pendans les testes, le comportement attendu n'est pas celui qui à été soulevé. en passant la valeur sur true ou false, ça ne changais rien . 



---

### Cas 5 : `cfg.maximizable = false`

* **Droit désactivé :** Autorisation d'agrandir la fenêtre.


* **Impact utilisateur :** L'utilisateur **ne peut plus agrandir** la fenêtre au maximum de la surface de l'écran via le bouton d'agrandissement (bouton grisé ou absent).mais pendans les testes, le comportement attendu n'est pas celui qui à été soulevé. en passant la valeur sur true ou false, ça ne changais rien . 



---

### Cas 6 : `cfg.canFullscreen = false`

* **Droit désactivé :** Capacité d'accès au mode plein écran.


* **Impact utilisateur :** L'utilisateur **ne peut plus faire basculer** la fenêtre en plein écran natif. Les tentatives de bascule ou raccourcis système plein écran sont ignorés. mais pendans les testes, le comportement attendu n'est pas celui qui à été soulevé. en passant la valeur sur true ou false, ça ne changais rien . 



---

### Cas 7 : `cfg.fullscreen = false`

* **Droit désactivé :** plein ecrrant natif.


* **Impact utilisateur :** la fenêtre s'ouvre en mode fenêtré classique dès son lancement. mais, lors des tests  le comportement attendu n'est pas celui qui à été soulevé. en passant la valeur sur true, la fenetre devenais invisible et sur false, elle redevenais normale.
