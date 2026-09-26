# Chapitre 03 — Exercice 2 : Les sept droits

## 1. Code source ([`c3-exo2_main.cpp`](c3-exo2_main.cpp))
dans le programme ci dessous, noua savont l'utlilisation des sept comfiguration de comportement de la fenetre . 

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

* il est censé ampecher L'utilisateur **de redimensionner** la fenêtre en étirant ses bordures ou ses coins avec la souris.mais pendans les testes, en passant la valeur sur true ou false, ça ne changais rien. la fenetre etais toujour redimentionnable. 



---

### Cas 2 : `cfg.movable = false`

* il est censé ampecher L'utilisateur **de déplacer** la fenêtre sur son écran en la faisant glisser par la barre de titre.mais pendans les testes, en passant la valeur sur true ou false,la fentre etais toujour deplacable.



---

### Cas 3 : `cfg.closable = false`

* cette regle ampeche l'utilisateur **de plus fermer** la fenêtre en cliquant sur la croix système. La fermeture n'est possible que par programme ou via le raccourci clavier (ctrl+c du terminal) ou par une autre mathode.pendans les testes,en passant la valeur sur true ou false la fenetre etais toujour fermable.

---

### Cas 4 : `cfg.minimizable = false`

* L'utilisateur **n'est plus censé pourvoir réduire** la fenêtre dans la barre des tâches.pendans les testes, le comportement attendu n'est pas celui qui à été soulevé. en passant la valeur sur true ou false, le reglage ne s'appliquais pas.


---

### Cas 5 : `cfg.maximizable = false`

* il est censé ampecher l'utilisateur **d'agrandir** la fenêtre au maximum de la surface de l'écran via le bouton d'agrandissement .mais pendans les testes, meme constat que pour les autres.



---

### Cas 6 : `cfg.canFullscreen = false`

* L'utilisateur n'est plus censé pouvoir faire passer la fenêtre en plein écran natif (au debut du programme). Les tentatives de bascule ou raccourcis système plein écran sont ignorés. mais meme constat que les autres pendant le test.



---

### Cas 7 : `cfg.fullscreen = false`

* la fenêtre est censée s'ouvrrir en mode fenêtré classique dès son lancement. mais, lors des tests, en passant la valeur sur true, la fenetre devenais invisible et sur false, elle redevenais normale.

les explication sur chaque configuration son des suppositions faites à partir ds noms des configuration et des commentaire du chapitre.
