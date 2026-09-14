# Exercice 10 : Analyse des dépendances de NKCanvas

En analysant le fichier `NKCanvas.jenga` et plus particulièrement ses commentaires détaillés, nous pouvons reconstruire l'arbre de dépendances explicite et implicite du module.

## 1. Dépendances directes (Niveau 1)
La directive `nkentseudependson(_canvasDeps, ...)` liste explicitement les dépendances directes de `NKCanvas`. 
Il y a **16 dépendances de base**, plus **1 conditionnelle** :
* `NKWindow`, `NKFont`, `NKImage`, `NKGui`, `NKEvent`, `NKGlad`
* `NKStream`, `NKTime`, `NKThreading`
* `NKFileSystem`, `NKLogger`, `NKMath`, `NKContainers`, `NKMemory`, `NKCore`, `NKPlatform`
* *(Optionnel)* `NKUI` (si `USE_CANVAS_NKUI` est activé).

```python
_canvasDeps = ["NKWindow", "NKFont", "NKImage", "NKGui", "NKEvent", "NKGlad",
                   "NKStream", "NKTime", "NKThreading",
                   "NKFileSystem", "NKLogger", "NKMath", "NKContainers", "NKMemory",
                   "NKCore", "NKPlatform"]
```


## 2. Dépendances des dépendances (Niveau 2)
à base des commentaires du fichier `.jenga` et des verifications,nous avons relevé de précieuses informations sur le niveau 2 (ce que les dépendances de `NKCanvas` incluent elles-mêmes) :
* **NKGui** dépend de : `NKPlatform`, `NKCore`, `NKMemory`, `NKMath`, `NKThreading`, `NKLogger`, `NKContainers`, `NKEvent`, `NKFont`, `NKImage`.
* **NKFont** et **NKImage** dépendent de : `NKStream` (qui contient `NKIResource.h`).
* **NKWindow** dépend de : modules de fondation (qui ont dû être déclarés explicitement dans `NKCanvas` car "une dépendance transitive n'est pas une dépendance dite").

## 3. Graphe des dépendances (Extrait sur 2 niveaux)

Voici le graphe illustrant les relations révélées par le fichier de configuration :

```text                   ┌────────────────────────┐
                          │        NKCanvas        │
                          └───────────┬────────────┘
                                      │
    ┌─────────────────────────────────┼─────────────────────────────────┐
    │ (Dépendances Directes - Niv 1)  │                                 │
    ▼                                 ▼                                 ▼
┌────────┐                       ┌────────┐                        ┌────────┐
│ NKGui  │                       │NKWindow│                        │ NKFont │ (et NKImage)
└───┬────┘                       └───┬────┘                        └───┬────┘
    │                                │                                 │
    │ (Niv 2)                        │ (Niv 2)                         │ (Niv 2)
    ▼                                ▼                                 ▼
┌──────────────────────┐         ┌──────────────────────┐          ┌────────┐
│NKFont, NKImage,      │         │Modules de fondation  │          │NKStream│
│NKEvent, NKThreading, │         │(NKPlatform, NKCore,  │          └────────┘
│NKLogger, NKMath,     │         │NKMemory, NKContainers│
│NKContainers, NKCore, │         │...)                  │
│NKMemory, NKPlatform  │         └──────────────────────┘
└──────────────────────┘
    
    │
    │  (Autres dépendances directes de Niveau 1 de NKCanvas)
    ▼
┌─────────────────────────────────────────────────────────────────────────────┐
│ NKGlad, NKEvent, NKStream, NKTime, NKFileSystem, NKThreading, NKLogger,     │
│ NKMath, NKContainers, NKMemory, NKCore, NKPlatform, [NKUI si activé]        │
└─────────────────────────────────────────────────────────────────────────────
```

## 4. Bilan : Combien de projets construire avant NKCanvas ?
Avant de pouvoir compiler et lier NKCanvas, le moteur de build doit obligatoirement résoudre et construire `16` projets (ou 17 si l'option USE_CANVAS_NKUI est activée).

**Pourquoi 16 ?**
Le système de build Jenga parcourt cet arbre de bas en haut (ordre topologique). Même si NKCanvas hérite théoriquement de certains modules indirectement (par exemple, NKPlatform est inclus via NKGui et NKWindow), le langage C++ et la configuration stricte de l'auteur exigent que chaque maillon soit présent et compilé individuellement. Les 16 modules listés dans _canvasDeps doivent donc tous exister sous forme de binaires compilés avant le build final de NKCanvas.