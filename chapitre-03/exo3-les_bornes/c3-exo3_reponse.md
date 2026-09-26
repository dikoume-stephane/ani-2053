# Chapitre 03 — Exercice 3 : Les bornes

## 1. Code source ([`c3-exo3_main.cpp`](c3-exo3_main.cpp))

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
    cfg.minHeight = 200;
    cfg.minWidth = 200;

    // les 7 droits
    cfg.resizable = false; 
    cfg.movable = true;  
    cfg.closable = true;  
    cfg.minimizable = false;  
    cfg.maximizable = true;  
    cfg.canFullscreen = false; 
    cfg.fullscreen = false; 

    NkWindow window(cfg);

    nkentseu::math::NkVec2T size = window.GetSize();

     std::cout << "\nla taille : ( "<< size.height<<"H , "<<size.width<<" W ) au depart"; 

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

            if (auto* rz = ev->As<NkWindowResizeEvent>()) 
            {
                math::NkVec2u size = window.GetSize();
                
                std::cout << "\nla taille : ( "<< size.height<<"H , "<<size.width<<" W ) redimentionnét"; 
            }
           
        }
    }

    return 0;
}

```

---

## 2. Technique de capture de la taille

Pour mesurer précisément la taille de la fenêtre et relever la dimension minimale acceptée, la méthode suivante a été implémentée dans le code :

1. **Lecture initiale :** Récupération des dimensions dès la création de la fenêtre via l'appel `window.GetSize()`, qui renvoie un vecteur `math::NkVec2u`.


2. **Interception dynamique des événements :** Détection de l'événement `NkWindowResizeEvent` dans la boucle d'événements grâce à `ev->As<NkWindowResizeEvent>()`.


3. **Affichage console en temps réel :** À chaque modification de la taille par l'utilisateur à la souris, `window.GetSize()` est réinterrogé et les valeurs instantanées de largeur et de hauteur sont envoyées dans la sortie `std::cout`.



---

## 3. Observations et résultats des tests

### Test 1 : Avec taille minimale imposée (`minWidth = 200`, `minHeight = 200`)

* **Comportement :** Lorsque l'on tente de réduire la fenêtre en dessous du seuil à la souris, le système bloque la réduction.

```poweshell
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


la taille : ( 592H , 798 W ) au depart
la taille : ( 592H , 798 W ) redimentionn├®t
la taille : ( 153H , 182 W ) redimentionn├®t
la taille : ( 153H , 182 W ) redimentionn├®t
la taille : ( 153H , 182 W ) redimentionn├®t
la taille : ( 153H , 182 W ) redimentionn├®t
la taille : ( 153H , 182 W ) redimentionn├®t
la taille : ( 153H , 182 W ) redimentionn├®t
la taille : ( 153H , 182 W ) redimentionn├®t
la taille : ( 153H , 182 W ) redimentionn├®t
la taille : ( 153H , 182 W ) redimentionn├®t
la taille : ( 153H , 182 W ) redimentionn├®t
la taille : ( 153H , 182 W ) redimentionn├®t
la taille : ( 153H , 182 W ) redimentionn├®t
la taille : ( 153H , 182 W ) redimentionn├®t
la taille : ( 153H , 182 W ) redimentionn├®t
la taille : ( 153H , 182 W ) redimentionn├®t
la taille : ( 153H , 182 W ) redimentionn├®t
```


* **Résultat console :** Les valeurs imprimées par `std::cout` cessent de diminuer dès qu'elles atteignent **182 W x 153 H**. ici , on voit directement une marge de 2 pixels en moin pour la largeur et de 47 pixels pour la hauteur . cet ecart peut s'expliqué par la presence des marges de la fenetre et de la barrre de titre. avec cette explication probable, on confirme le respect des bornes spécifiées dans `NkWindowConfig`.



---

### Test 2 : Sans taille minimale applicative

* **Comportement :** Après suppression des bornes explicites, la fenêtre peut être réduite beaucoup plus bas jusqu'à la limite physique autorisée par le systeme.
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


la taille : ( 592H , 798 W ) au depart
la taille : ( 592H , 798 W ) redimentionn├®t
la taille : ( 43H , 148 W ) redimentionn├®t
la taille : ( 43H , 148 W ) redimentionn├®t
la taille : ( 43H , 148 W ) redimentionn├®t
la taille : ( 43H , 148 W ) redimentionn├®t
la taille : ( 43H , 148 W ) redimentionn├®t
la taille : ( 43H , 148 W ) redimentionn├®t
la taille : ( 43H , 148 W ) redimentionn├®t
la taille : ( 43H , 148 W ) redimentionn├®t
la taille : ( 43H , 148 W ) redimentionn├®t
la taille : ( 43H , 148 W ) redimentionn├®t
la taille : ( 43H , 148 W ) redimentionn├®t
la taille : ( 43H , 148 W ) redimentionn├®t
la taille : ( 43H , 148 W ) redimentionn├®t
la taille : ( 43H , 148 W ) redimentionn├®t
la taille : ( 43H , 148 W ) redimentionn├®t
la taille : ( 43H , 148 W ) redimentionn├®t
la taille : ( 43H , 148 W ) redimentionn├®t
la taille : ( 43H , 148 W ) redimentionn├®t
la taille : ( 43H , 148 W ) redimentionn├®t
la taille : ( 43H , 148 W ) redimentionn├®t
la taille : ( 43H , 148 W ) redimentionn├®t
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (52.09s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```


* **Plus petite taille acceptée par le système :** La dernière valeur affichée dans la console lors de la réduction maximale représente la taille minimale absolue imposée par le système soit **148*43**. Et, on voit encore une marge de 2 pixels en moin pour la largeur et de 47 pixels pour la hauteur .
