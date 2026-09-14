# Exercice 8 : Comparaison des configurations Debug et Release

**Projet étudié :** `MonEssai`

---

## mode release
* **commande utilisée :** `jenga build --project MonEssai --config Release`
* **rsultat :**
```
 D:\2DS\projet\programmation_cpp\Nkentseu> jenga build --project MonEssai --config Release

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

Loading workspace...
[NKCode] ATTENTION : aucun wheel Jenga trouve (dist/*.whl) -> le paquet n'aura PAS de Jenga embarque, et les boutons Construire/Executer seront inoperants. Produisez-le avec ./cri.sh dans le depot Jenga.

Configuration: Release
Target:        Windows x86_64
Toolchain:     clang-mingw

Build Order (6 projects):
  1. NKPlatform [STATIC_LIB] → 
  2. NKCore [STATIC_LIB] (depends: NKPlatform) → 
  3. NKMemory [STATIC_LIB] (depends: NKCore, NKPlatform) → 
  4. NKContainers [STATIC_LIB] (depends: NKCore, NKMemory, NKPlatform) → 
  5. NKMath [STATIC_LIB] (depends: NKContainers, NKCore, NKMemory, NKPlatform) → 
  6. MonEssai [CONSOLE_APP] (depends: NKMath)



✓   [5/12] Compiled: NkMat.cpp
✓   [6/12] Compiled: NkQuat.cpp
✓   [7/12] Compiled: NkRandom.cpp
✓   [8/12] Compiled: NkRange.cpp
✓   [9/12] Compiled: NkSIMD.cpp
✓   [10/12] Compiled: NkRectangle.cpp
✓   [11/12] Compiled: NkSegment.cpp
✓   [12/12] Compiled: NkVec.cpp
ℹ Linking...
✓ Built: Build\Lib\Release-Windows\NKMath.lib

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                            Time: 16.95s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: MonEssai                                                        Kind: CONSOLE_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓   [1/1] Compiled: main.cpp
ℹ Linking...
✓ Built: Build\Bin\Release-Windows\MonEssai\MonEssai.exe

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 4.26s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                BUILD COMPLETED                                 
════════════════════════════════════════════════════════════════════════════════
Projects Built:  6/6
Time:           55.72s
Status:         ✓ SUCCESS
════════════════════════════════════════════════════════════════════════════════
```

## mode debug
* **commande utilisée :** `jenga build --project MonEssai --config debug`
* **resultat :**
```
jenga build --project MonEssai --config Debug  

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

Loading workspace...
[NKCode] ATTENTION : aucun wheel Jenga trouve (dist/*.whl) -> le paquet n'aura PAS de Jenga embarque, et les boutons Construire/Executer seront inoperants. Produisez-le avec ./cri.sh dans le depot Jenga.

Configuration: Debug
Target:        Windows x86_64
Toolchain:     clang-mingw

Build Order (1 projects):
  1. MonEssai [CONSOLE_APP]


╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: MonEssai                                                        Kind: CONSOLE_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓   [1/1] Compiled: main.cpp
ℹ Linking...
✓ Built: Build\Bin\Debug-Windows\MonEssai\MonEssai.exe

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 1.60s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                BUILD COMPLETED                                 
════════════════════════════════════════════════════════════════════════════════
Projects Built:  1/1
Time:           1.60s
Status:         ✓ SUCCESS
════════════════════════════════════════════════════════════════════════════════

PS D:\2DS\projet\programmation_cpp\Nkentseu> jenga clean --all                            

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

[NKCode] ATTENTION : aucun wheel Jenga trouve (dist/*.whl) -> le paquet n'aura PAS de Jenga embarque, et les boutons Construire/Executer seront inoperants. Produisez-le avec ./cri.sh dans le depot Jenga.
Removed D:\2DS\projet\programmation_cpp\Nkentseu\Build
PS D:\2DS\projet\programmation_cpp\Nkentseu> jenga build --project MonEssai --config Debug

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

Loading workspace...
[NKCode] ATTENTION : aucun wheel Jenga trouve (dist/*.whl) -> le paquet n'aura PAS de Jenga embarque, et les boutons Construire/Executer seront inoperants. Produisez-le avec ./cri.sh dans le depot Jenga.

Configuration: Debug
Target:        Windows x86_64
Toolchain:     clang-mingw

Build Order (6 projects):
  1. NKPlatform [STATIC_LIB] → 
  2. NKCore [STATIC_LIB] (depends: NKPlatform) → 
  3. NKMemory [STATIC_LIB] (depends: NKCore, NKPlatform) → 
  4. NKContainers [STATIC_LIB] (depends: NKCore, NKMemory, NKPlatform) → 
  5. NKMath [STATIC_LIB] (depends: NKContainers, NKCore, NKMemory, NKPlatform) → 
  6. MonEssai [CONSOLE_APP] (depends: NKMath)





✓   [39/43] Compiled: NkStringView.cpp
✓   [40/43] Compiled: NkStringUtils.cpp
✓   [41/43] Compiled: NkResult.cpp
✓   [42/43] Compiled: NkVariant.cpp
✓   [43/43] Compiled: NkSpan.cpp
ℹ Linking...
✓ Built: Build\Lib\Debug-Windows\NKContainers.lib

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                            Time: 14.71s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: NKMath                                                           Kind: STATIC_LIB  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 12 source file(s)
✓   [1/12] Compiled: NkAngle.cpp
✓   [2/12] Compiled: NkEulerAngle.cpp
✓   [3/12] Compiled: NkColor.cpp
✓   [4/12] Compiled: NkFunctions.cpp
✓   [5/12] Compiled: NkMat.cpp
✓   [6/12] Compiled: NkQuat.cpp
✓   [7/12] Compiled: NkRandom.cpp
✓   [8/12] Compiled: NkRange.cpp
✓   [9/12] Compiled: NkSIMD.cpp
✓   [10/12] Compiled: NkRectangle.cpp
✓   [11/12] Compiled: NkSegment.cpp
✓   [12/12] Compiled: NkVec.cpp
ℹ Linking...
✓ Built: Build\Lib\Debug-Windows\NKMath.lib

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                            Time: 16.50s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: MonEssai                                                        Kind: CONSOLE_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓   [1/1] Compiled: main.cpp
ℹ Linking...
✓ Built: Build\Bin\Debug-Windows\MonEssai\MonEssai.exe

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 4.61s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                BUILD COMPLETED                                 
════════════════════════════════════════════════════════════════════════════════
Projects Built:  6/6
Time:           48.52s
Status:         ✓ SUCCESS
════════════════════════════════════════════════════════════════════════════════

```

## 1. Relevé des quatre nombres

| Configuration | Temps de construction (s) | Taille du binaire (Ko / Mo) |
| :--- | :--- | :--- |
| **Debug** | **`48.52` s**  | **`3415` Ko**  |
| **Release** | **`55.72` s**  | **`2794` Ko**  |

---

## 2. Identification et explication des lignes dans `Nkentseu.jenga`

Les écarts observés entre ces quatre nombres s'expliquent par les directives définies dans les filtres de configuration du fichier `Nkentseu.jenga` (c'est le workspace qui decide des configurations):

### A. Explication de la différence de taille  :  
  En Debug, la génération des symboles enrichit l'executable de toutes les métadonnées de débogage (noms de variables, numéros de lignes). En Release, ces données sont omises, réduisant drastiquement la taille du fichier exécutable. j'ai changé d'approche en remettant les depandances de "MonEssai" que j'avais mis à l'exo d'avant .on observe bien l'ecart entre les deux executables.avec mon ancien main.cpp, ettant vide,le compilateur n'avait rien à optimiser dons l'ecart de taille ne se fait pas sentir.
* **`optimize("Speed")` (Release) :**  
  L'optimiseur supprime le code inutilisé.

### B. Explication de la différence de temps de build (Nombre 1 vs Nombre 3)
  
  En mode Debug, l'absence d'optimisation permet une traduction C++ vers assembleur directe et très rapide. En mode Release, le compilateur doit effectuer de multiples passes complexes d'analyse et d'optimisation , ce qui augmente le temps de compilation.

## 2. Localisation réelle des directives et mécanisme d'héritage

Une vérification ciblée via la commande `Select-String` permet de clarifier la répartition des directives :

* **pour NKensteu.jenga**: la commande est `Select-String -Path Nkentseu.jenga -Pattern "optimize|symbols"`
```powershell

PS D:\2DS\projet\programmation_cpp\Nkentseu> Select-String -Path Nkentseu.jenga -Pattern "optimize|symbols"
PS D:\2DS\projet\programmation_cpp\Nkentseu> 
```
* **pour Nkmath :** la commande est `Select-String -Path Kernel\Foundation\NKMath\NKMath.jenga -Pattern "optimize|symbols"`


```powershell
 D:\2DS\projet\programmation_cpp\Nkentseu> Select-String -Path Kernel\Foundation\NKMath\NKMath.jenga -Pattern "optimize|symbols"

Kernel\Foundation\NKMath\NKMath.jenga:65:        optimize("Off")
Kernel\Foundation\NKMath\NKMath.jenga:66:        symbols(True)
Kernel\Foundation\NKMath\NKMath.jenga:69:        optimize("Speed")
Kernel\Foundation\NKMath\NKMath.jenga:70:        symbols(False)

```
## Analyse de l'architecture de configuration :
Au niveau des modules (ex: NKMath.jenga) : Chaque module déclare explicitement ses propres règles de compilation selon la configuration active :

```Python
with filter("config: Debug"):
    defines(["_DEBUG", "DEBUG", "NKENTSEU_DEBUG"])
    optimize("Off")
    symbols(True)

with filter("config: Release"):
    defines(["NDEBUG", "NKENTSEU_RELEASE"])
    optimize("Speed")
    symbols(False)
```

Au niveau du projet applicatif (MonEssai.jenga) : Le fichier MonEssai.jenga ne contient aucune directive symbols() ou optimize().

D'où viennent les options de MonEssai ?
Puisque le workspace racine ne dicte pas ces règles et que MonEssai.jenga ne les définit pas, MonEssai hérite uniquement des options par défaut du moteur de build Jenga.

En revanche, lors de la construction globale, les dépendances internes (NKMath, NKContainers, etc.) sont compilées avec les directives spécifiques déclarées dans leurs propres fichiers .jenga. Les variations de taille et de temps observées sur le binaire final proviennent donc majoritairement de la compilation de ces dépendances.

---

### 2. Analyse de l'écart de temps

* **Variabilité des mesures :** L'écart de 1-6 seconde représente moins de 15 % du temps total, ce qui entre dans la marge d'erreur du système (bruit de mesure causé par le disque et le processeur sous Windows).
* **Répartition du temps de compilation :** La majeure partie du temps de construction est consommée par le prétraitement des en-têtes C++ (`#include`), étape dont la durée est strictement identique dans les deux configurations. 
* **Effet de compensation :** Le temps supplémentaire passé par le compilateur à optimiser le code en Release est compensé en Debug par le surcoût de l'écriture des symboles de débogage lourds lors de la phase d'édition de liens.