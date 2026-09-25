# Chapitre 03 — Exercice 1 : La fenêtre nue

## 1. Code source minimal [(`c3-exo1_main.cpp`)](c3-exo1_main.cpp)

```cpp
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"

using namespace nkentseu;

int nkmain(const NkEntryState &state) {
    
    NkWindow window(NkWindowConfig{});
    if (!window.IsOpen()) {
        logger.Error("[app] creation fenetre echouee");
        return -1;
    }
    while (window.IsOpen()) { /* les evenements arrivent ici */ }
    return 0;
}

```
## 2. Décompte des lignes

Le programme comporte **20 lignes de code** (comprenant les lignes de presentation et les inclusions nécessaires).

---

## 3. Explication ligne par ligne et correspondance avec le cours

* **Ligne 1 : `#include "NKWindow/NKWindow.h"**`
* **Rôle :** Inclut les hearders publique du module `NKWindow` (définition des fonctions de NKWindow).

* **Ligne 2 : `#include "NKWindow/NKMain.h"**`
* **Rôle :** Génère le point d'entrée natif selon la plateforme hôte (Windows, Linux, Android, etc.) et déclenche l'exécution de `nkmain`.

* **Ligne 4 : `using namespace nkentseu;**`
* **Rôle :** Permet d'accéder directement aux classes et types du moteur sans passé par `nkentseu::`.

* **Ligne 6 : `int nkmain(const NkEntryState& state) {**`
* **Rôle :** Définit le point d'entrée de l'application Nkentseu recevant l'état d'initialisation (`NkEntryState`).

* **Ligne 8 : `NkWindow window(NkWindowConfig{});`
* **Rôle :** Instancie et crée la fenêtre native avec la configuration par défaut (`NkWindowConfig`).

* **bloc 9-12 :
* **Rôle :**  `if (!window.IsOpen())` verifi si la fenetre n'est pas ouverte . si oui, `logger.Error("[app] creation fenetre echouee");` renvoit un log d'erreur. et  `return -1;`ferme le programme avec une valeur d'erreur.

* **Ligne 13 : `while (window.IsOpen()) {.....}`
* **Rôle :** Démarre la boucle principale qui tourne tant que la fenêtre reste ouverte .

* **Lignes 14 et 15 : `return 0;` / `}`
* **Rôle :** Fermeture de la boucle, fin de la fonction `nkmain` avec un code de retour succès (`0`) et destruction propre de la fenêtre.

## 4. Constats et analyse du comportement

### Observations lors de l'exécution
Dans cette version du code où le corps de la boucle `while (window.IsOpen())` est vide :
1. **Incapacité d'interagir normalement avec la fenêtre :** Les boutons de la barre de titre (fermeture, réduction, agrandissement) ne fonctionnent pas.
2. **Fenêtre figée :** La fenêtre ne répond plus aux événements du système d'exploitation.
3. **Fermeture impossible :** La fenêtre reste bloquée ouverte et l'arrêt du programme nécessite d'interrompre manuellement le processus dans le terminal (via `Ctrl + C` ).

### Explication technique
Ce comportement s'explique par l'absence de traitement des événements :
* **Accumulation des messages système :** Le système d'exploitation envoie en continu des événements natifs à la fenêtre (clics sur la croix, déplacements, rafraîchissement d'affichage).
* **Blocage du traitement :** En l'absence de l'appel à `NkEvents().PollEvent()`, cette file d'événements n'est jamais vidée ni traitée. 
* **Boucle infinie :** Comme l'événement de fermeture (`NkWindowCloseEvent`) n'est jamais intercepté, la méthode `window.IsOpen()` continue de renvoyer `true` indéfiniment, bloquant le programme dans la boucle principale.

**Conclusion :** Pour qu'une fenêtre reste réactive et puisse être fermée proprement, il est necessaire d'ajouter la gestion d'événements à chaque tour de la boucle principale.