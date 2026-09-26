# Chapitre 03 — Exercice 1 : La fenêtre nue

## 1. Code source minimal [(`c3-exo1_main.cpp`)](c3-exo1_main.cpp)

```cpp
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include "NKEvent/NkWindowEvent.h"

using namespace nkentseu;

int nkmain(const NkEntryState &state) {
    
    NkWindow window(NkWindowConfig{});
    if (!window.IsOpen()) {
        logger.Error("[app] creation fenetre echouee");
        return -1;
    }
    while (window.IsOpen()) { 
        while (NkEvent* ev = NkEvents().PollEvent()) {
            if (ev->Is<NkWindowCloseEvent>()) {
                window.Close();
            }
        } 
    }
    return 0;
}

```
## 2. Décompte des lignes

Le programme comporte **23 lignes de code** (comprenant les lignes de presentation et les inclusions nécessaires).

---

## 3. Explication ligne par ligne et correspondance avec le cours

**Code du chapitre**
```cpp
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"

int nkmain(const NkEntryState &state) {
    NkWindowConfig cfg;
    cfg.title  = "Ma fenetre";
    cfg.width  = 1280;
    cfg.height = 720;

    NkWindow window(cfg);
    if (!window.IsOpen()) {
        logger.Error("[app] creation fenetre echouee");
        return -1;
    }
    while (window.IsOpen()) { /* les evenements arrivent ici */ }
    return 0;
}
```

* **Ligne 1 à 3 : les inclusions.
 `#include "NKWindow/NKWindow.h"` et `#include "NKWindow/NKMain.h"`
* **Rôle :** Inclut les hearders publique du module `NKWindow` (définition des fonctions de NKWindow).et Génère le point d'entrée natif selon la plateforme hôte (Windows, Linux, Android, etc.) et déclenche l'exécution de `nkmain`. ils sont present dans le chapitre. mais, `NKEvent/NkWindowEvent.h` n'st pas dans le code du chapitre car il permet de gerer les evenements du. 

* **Ligne 5 : `using namespace nkentseu;**`
* **Rôle :** Permet d'accéder directement aux classes et types du moteur sans passé par `nkentseu::`.il n'est pas present dans le code du chapitre .

* **Ligne 7 : `int nkmain(const NkEntryState& state) {**`
* **Rôle :** Définit le point d'entrée de l'application Nkentseu recevant l'état d'initialisation (`NkEntryState`). cette ligne est aussi presente dans le code du chapitre .

* **Ligne 9 : `NkWindow window(NkWindowConfig{});`
* **Rôle :** Instancie et crée la fenêtre native avec la configuration par défaut (`NkWindowConfig`). cette ligne est equivalente au bloc 
```
NkWindowConfig cfg;
    cfg.title  = "Ma fenetre";
    cfg.width  = 1280;
    cfg.height = 720;
```
du chapitre qui lui fixe manuelement les valeur de configuration .

* **bloc 10-13 :
* **Rôle :**  `if (!window.IsOpen())` verifi si la fenetre n'est pas ouverte . si oui, `logger.Error("[app] creation fenetre echouee");` renvoit un log d'erreur. et  `return -1;`ferme le programme avec une valeur d'erreur.il est aussi present dans le chaqpitre .

* **Ligne 14 : `while (window.IsOpen()) {`
* **Rôle :** Démarre la boucle principale qui tourne tant que la fenêtre reste ouverte . cette ligne est aussi presente dans le chapitre. 

* **bloc 15 à 19 : `return 0;` / `}`
* **Rôle :** Fermeture de la boucle, fin de la fonction `nkmain` avec un code de retour succès (`0`) et destruction propre de la fenêtre.

* lignes 21 et 22 : `while (NkEvent* ev = NkEvents().PollEvent()) {....` 
* **Rôle :** c'est la boucle d'evennement du programme elle toune tantque le programme et le systheme renvoient des evennements et appele la fonction de fermeture du programme`window.close();` quand l'evenement du clic sur la croix de fermeture est detecté. 

## 4 execution 
le programme à ete executé et on peut voir à la sortie du terminal que celui ci se termine normalement .
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


━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (4.73s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```
