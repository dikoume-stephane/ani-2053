# Exercice 7 : Mesure du temps de compilation
**Projet testé :** `NKMath`

---

## 1. Relevé des temps

* **Chronomètre 1 (Construction complète à froid) :** `57.67` secondes
```
 D:\2DS\projet\programmation_cpp\Nkentseu> jenga build --target NKMath                    

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

Build Order (5 projects):
  1. NKPlatform [STATIC_LIB] → 
  2. NKCore [STATIC_LIB] (depends: NKPlatform) → 
  3. NKMemory [STATIC_LIB] (depends: NKCore, NKPlatform) → 
  4. NKContainers [STATIC_LIB] (depends: NKCore, NKMemory, NKPlatform) → 
  5. NKMath [STATIC_LIB] (depends: NKContainers, NKCore, NKMemory, NKPlatform)



Compiled: NkRectangle.cpp
✓   [10/12] Compiled: NkSIMD.cpp
✓   [11/12] Compiled: NkSegment.cpp
✓   [12/12] Compiled: NkVec.cpp
ℹ Linking...
✓ Built: Build\Lib\Debug-Windows\NKMath.lib

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                            Time: 22.21s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                BUILD COMPLETED                                 
════════════════════════════════════════════════════════════════════════════════
Projects Built:  5/5
Time:           57.67s
Status:         ✓ SUCCESS
════════════════════════════════════════════════════════════════════════════════


```

* **Chronomètre 2 (Seconde construction immédiate) :** `4.99` seconde 
```
D:\2DS\projet\programmation_cpp\Nkentseu> jenga build --target NKMath

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

Build Order (5 projects):
  1. NKPlatform [STATIC_LIB] → 
  2. NKCore [STATIC_LIB] (depends: NKPlatform) → 
  3. NKMemory [STATIC_LIB] (depends: NKCore, NKPlatform) → 
  4. NKContainers [STATIC_LIB] (depends: NKCore, NKMemory, NKPlatform) → 
  5. NKMath [STATIC_LIB] (depends: NKContainers, NKCore, NKMemory, NKPlatform)


╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: NKPlatform                                                       Kind: STATIC_LIB  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 7 source file(s)
✓ All files up to date


┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 1.00s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                BUILD COMPLETED                                 
════════════════════════════════════════════════════════════════════════════════
Projects Built:  5/5
Time:           4.99s
Status:         ✓ SUCCESS
════════════════════════════════════════════════════════════════════════════════

```
* **commande lancée :** `jenga build --target NKMath`

---

## 2. Explication de l'écart 

L'écart entre les deux temps est expliqué par la **gestion du cache et de la compilation** de Jenga :

1. **Lors du premier build :** Jenga doit compiler chaque fichier source `.cpp` en fichier objet `.obj` / `.o` puis exécuter l'éditeur de liens pour créer le binaire final.

2. **Lors du second build :** Jenga vérifie les horodatages (**timestamps**) de tous les fichiers du projet. Constatant qu'aucun fichier source `.cpp` ou d'en-tête `.h` n'a été modifié depuis la dernière passe, il conclut que tous les fichiers sont à jour. Aucun appel au compilateur ou au linker n'est déclenché, ce qui rend l'exécution presque instantanée.

---

## 3. Mécanisme de détection des dépendances (`.d` / `.obj`)

### Comment Jenga identifie-t-il la liste exacte des en-têtes ?
La liste des dépendances n'est pas écrite dans les fichiers `.jenga`. C'est le **compilateur C++ lui-même** (GCC, Clang ou MSVC) qui génère automatiquement un fichier de dépendances à la compilation de chaque fichier source (via des options comme `-MMD -MP` ou `/showIncludes`).

Exemple d'association extrait de `src_NKContainers_Associative_NkBinaryTree.obj` :

```makefile
D:\2DS\...\NkBinaryTree.obj: \
  D:/2DS/.../NKContainers/src/.../NkBinaryTree.cpp \
  D:/2DS/.../NKContainers/src/.../NkBinaryTree.h \
  D:/2DS/.../NKCore/src/.../NkTypes.h \
  D:/2DS/.../NKPlatform/src/.../NkArchDetect.h \
```
