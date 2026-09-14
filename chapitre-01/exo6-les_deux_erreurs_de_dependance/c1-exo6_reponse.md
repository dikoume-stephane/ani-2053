# Exercice 6 : Les deux erreurs de dépendance

## mise a jour du main.cpp
**Projet utilisé :** `MonEssai` avec dépendance vers `NKMath`
apres inclusion des hearder, j'ai appelé une fonction propre à NKMath
```cpp
#include "NKMath/NKMath.h"


int main() {
    // Appel à une fonction ou un type du module NKMath
    nkentseu::math::NkColor color = nkentseu::math::NkColor::White;
    return 0;
}
```
## mise a jour du MonEssai.jenga
ajout des includes et des autres configurations
```python
from Jenga import *
from jengaconfig import *

with project("MonEssai"):
    consoleapp()
    language("C++")
    cppdialect("C++17")
    location(".")

    files(["main.cpp"])

    objdir("%{wks.location}/Build/Obj/%{cfg.buildcfg}-%{cfg.system}/%{prj.name}")
    targetdir("%{wks.location}/Build/Bin/%{cfg.buildcfg}-%{cfg.system}/%{prj.name}")

    includedirs(["%{NKMath.location}/src","%{NKCore.location}/src","%{NKPlatform.location}/src","%{NKContainers.location}/src","%{NKMemory.location}/src"])
    dependson(["NKMath"])
    links(["NKPlatform","NKCore","NKMemory","NKContainers","NKMath"])

    with filter("system: Windows"):
        usetoolchain(TC_WINDOWS)
```
## test avec la configuration actuelle
* **commande executée :** `jenga build --project MonEssai`
* **resultat :**
```

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: MonEssai                                                        Kind: CONSOLE_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓   [1/1] Compiled: main.cpp
ℹ Linking...
✓ Built: Build\Bin\Debug-Windows\MonEssai\MonEssai.exe

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 6.40s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                BUILD COMPLETED                                 
════════════════════════════════════════════════════════════════════════════════
Projects Built:  6/6
Time:           1m6.0s
Status:         ✓ SUCCESS
════════════════════════════════════════════════════════════════════════════════
```
* **explication :** 
- pur la ligne `includedirs(["%{NKMath.location}/src","%{NKCore.location}/src","%{NKPlatform.location}/src","%{NKContainers.location}/src","%{NKMemory.location}/src"])`elle sert à inclure les hearder de toutes les dependance le main.cpp donc de NKMath.
- pour `links(["NKPlatform","NKCore","NKMemory","NKContainers","NKMath"])` , il est necessaire de mettre les bibliotheque dans l'ordre de construction de NKMath pour que le linkeur les integres à l'executable dans l'ordre . en mettant uniquement "NKMath", on obtien une erreur de linckage du style :
```
NK8nkentseu13NkFormatProps10ApplyWidthERKNS_12NkStringViewEb[_ZNK8nkentseu13NkFormatProps10A ║
║ pplyWidthERKNS_12NkStringViewEb]+0x46b): undefined reference to                              ║
║ `nkentseu::NkString::Append(nkentseu::NkStringView)'                                         ║
║ C:/msys64/ucrt64/bin/ld: D:\2DS\projet\programmation                                         ║
║ cpp\Nkentseu\Kernel\Foundation\NKContainers\src/NKContainers/String/NkFormat.h:177:(.text$_Z ║
║ NK8nkentseu13NkFormatProps10ApplyWidthERKNS_12NkStringViewEb[_ZNK8nkentseu13NkFormatProps10A ║
║ pplyWidthERKNS_12NkStringViewEb]+0x487): undefined reference to                              ║
║ `nkentseu::NkString::Append(unsigned long long, char)'                                       ║
║ C:/msys64/ucrt64/bin/ld: D:\2DS\projet\programmation                                         ║
║ cpp\Nkentseu\Kernel\Foundation\NKContainers\src/NKContainers/String/NkFormat.h:180:(.text$_Z ║
║ NK8nkentseu13NkFormatProps10ApplyWidthERKNS_12NkStringViewEb[_ZNK8nkentseu13NkFormatProps10A ║
║ pplyWidthERKNS_12NkStringViewEb]+0x4a8): undefined reference to 
```
car l'executable sera lié uniquement à NKMat et non à ses dependances.
- pour `dependson(["NKMath"])`, il n'est pas necessaire de lister les autre car jenga va remonter automatiquement les dependances de NKMath et les compiler avant NKMath grace à l'ordre de build.

---

## 1. Test sans `dependson` (Ordre de construction manquant)

* **Modification dans le `.jenga` :** `links(["NKPlatform","NKCore","NKMemory","NKContainers","NKMath"])` présent, mais `dependson(["NKMath"])` retiré.
* **Commande exécutée :** `jenga clean` puis `jenga build --project MonEssai`
* **Message d'erreur obtenu :**
```

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
╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                                Compilation Error: Link Failed                                ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ C:/msys64/ucrt64/bin/ld: cannot find -lNKPlatform: No such file or directory                 ║
║ C:/msys64/ucrt64/bin/ld: cannot find -lNKCore: No such file or directory                     ║
║ C:/msys64/ucrt64/bin/ld: cannot find -lNKMemory: No such file or directory                   ║
║ C:/msys64/ucrt64/bin/ld: cannot find -lNKContainers: No such file or directory               ║
║ C:/msys64/ucrt64/bin/ld: cannot find -lNKMath: No such file or directory                     ║
║ clang++: error: linker command failed with exit code 1 (use -v to see invocation)            ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝
✗ Link failed: Build\Bin\Debug-Windows\MonEssai\MonEssai.exe

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✗ Build Failed                                                                 Time: 5.38s  │
│ Errors: 1  | Failed files: 1                                                                 │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                  BUILD FAILED                                  
════════════════════════════════════════════════════════════════════════════════
Projects Built:  0/1
Failed:         1
Errors:         1
Time:           5.39s
Status:         ✗ FAILURE
════════════════════════════════════════════════════════════════════════════════

Echecs (1) — a corriger :
  ✗ MonEssai
```

* **Explication :** Jenga ne connaît pas l'ordre d'exécutabilité des builds. Il tente de compiler/lier `MonEssai` avant que `NKMath` n'ait été généré.et l'erreur mentionne tous les projets manquant .

---

## 2. Test sans `links` (Édition de liens manquante)

* **Modification dans le `.jenga` :** `dependson(["NKMath"])` présent, mais `links(["NKMath"])` retiré[cite: 1].
* **Commande exécutée :** `jenga build --project MonEssai`[cite: 1]
* **Message d'erreur obtenu :**
```

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
✓   [9/12] Compiled: NkRectangle.cpp
✓   [10/12] Compiled: NkSIMD.cpp
✓   [11/12] Compiled: NkSegment.cpp
✓   [12/12] Compiled: NkVec.cpp
ℹ Linking...
✓ Built: Build\Lib\Debug-Windows\NKMath.lib

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                            Time: 18.66s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: MonEssai                                                        Kind: CONSOLE_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓   [1/1] Compiled: main.cpp
ℹ Linking...
╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                                Compilation Error: Link Failed                                ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ C:/msys64/ucrt64/bin/ld: D:\2DS\projet\programmation                                         ║
║ cpp\Nkentseu\Build\Lib\Debug-Windows\NKMath.lib(src_NKMath_NkColor.obj): in function         ║
║ `nkentseu::math::NkColor::FromName(nkentseu::NkString const&)':                              ║
║ D:\2DS\projet\programmation                                                                  ║

║ more undefined references to `nkentseu::NkString::~NkString()' follow                        ║
║ C:/msys64/ucrt64/bin/ld: D:\2DS\projet\programmation                                         ║
║ cpp\Nkentseu\Build\Lib\Debug-Windows\NKMath.lib(src_NKMath_NkColor.obj): in function         ║
║ `nkentseu::detail::NkFmtFloat(double, nkentseu::NkFormatProps const&)':                      ║
║ D:\2DS\projet\programmation                                                                  ║
║ cpp\Nkentseu\Kernel\Foundation\NKContainers\src/NKContainers/String/NkFormat.h:389:(.text$_Z ║
║ N8nkentseu6detail10NkFmtFloatEdRKNS_13NkFormatPropsE[_ZN8nkentseu6detail10NkFmtFloatEdRKNS_1 ║
║ 3NkFormatPropsE]+0x561): undefined reference to                                              ║
║ `nkentseu::NkStringView::NkStringView(nkentseu::NkString const&)'                            ║
║ C:/msys64/ucrt64/bin/ld: D:\2DS\projet\programmation                                         ║
║ cpp\Nkentseu\Kernel\Foundation\NKContainers\src/NKContainers/String/NkFormat.h:390:(.text$_Z ║
║ N8nkentseu6detail10NkFmtFloatEdRKNS_13NkFormatPropsE[_ZN8nkentseu6detail10NkFmtFloatEdRKNS_1 ║
║ 3NkFormatPropsE]+0x587): undefined reference to `nkentseu::NkString::~NkString()'            ║
║ C:/msys64/ucrt64/bin/ld: D:\2DS\projet\programmation                                         ║
║ cpp\Nkentseu\Kernel\Foundation\NKContainers\src/NKContainers/String/NkFormat.h:390:(.text$_Z ║
║ N8nkentseu6detail10NkFmtFloatEdRKNS_13NkFormatPropsE[_ZN8nkentseu6detail10NkFmtFloatEdRKNS_1 ║
║ 3NkFormatPropsE]+0x5a1): undefined reference to `nkentseu::NkString::~NkString()'            ║
║ clang++: error: linker command failed with exit code 1 (use -v to see invocation)            ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝
✗ Link failed: Build\Bin\Debug-Windows\MonEssai\MonEssai.exe

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✗ Build Failed                                                                 Time: 5.25s  │
│ Errors: 179  | Failed files: 1                                                               │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                  BUILD FAILED                                  
════════════════════════════════════════════════════════════════════════════════
Projects Built:  5/6
Failed:         1
Errors:         179
Time:           55.32s
Status:         ✗ FAILURE
════════════════════════════════════════════════════════════════════════════════

Echecs (1) — a corriger :
  ✗ MonEssai
```

* **Explication :** `NKMath` a bien été construit avant `MonEssai` ainsi que toutes ses dependances, mais l'éditeur de liens n'a pas inclus le code binaire de `NKMath` dans l'exécutable final de `MonEssai`.

---

## 3. Synthèse des différences

| Option | Rôle principal | Phase où l'erreur survient | Symptômes de l'erreur |
| :--- | :--- | :--- | :--- |
| **`dependson`** | Définit **dans quel ordre** construire les projets. | Phase d'organisation du build. | Fichier binaire `.lib` ou `.a` manquant. |
| **`links`** | Indique **avec quoi lier** l'exécutable final[cite: 1]. | Phase d'édition de liens (Linker). | Erreur de symboles / références non résolues (`undefined reference`). |