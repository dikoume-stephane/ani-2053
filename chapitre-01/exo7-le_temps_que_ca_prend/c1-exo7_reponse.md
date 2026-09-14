# Exercice 7 : Mesure du temps de compilation
**Projet testé :** `MonEssai`

---

## 1. Relevé des temps

* **Chronomètre 1 (Construction complète à froid) :** ~ `47.72` secondes
```
✓   [9/12] Compiled: NkRectangle.cpp
✓   [10/12] Compiled: NkSIMD.cpp
✓   [11/12] Compiled: NkSegment.cpp
✓   [12/12] Compiled: NkVec.cpp
ℹ Linking...
✓ Built: Build\Lib\Debug-Windows\NKMath.lib

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                            Time: 17.99s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                BUILD COMPLETED                                 
════════════════════════════════════════════════════════════════════════════════
Projects Built:  5/5
Time:           47.72s
Status:         ✓ SUCCESS
════════════════════════════════════════════════════════════════════════════════

```

* **Chronomètre 2 (Seconde construction immédiate) :** ~ `52.01` seconde 
```
  [10/12] Compiled: NkSIMD.cpp
✓   [11/12] Compiled: NkSegment.cpp
✓   [12/12] Compiled: NkVec.cpp
ℹ Linking...
✓ Built: Build\Lib\Debug-Windows\NKMath.lib

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                            Time: 19.54s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                BUILD COMPLETED                                 
════════════════════════════════════════════════════════════════════════════════
Projects Built:  5/5
Time:           52.01s
Status:         ✓ SUCCESS
════════════════════════════════════════════════════════════════════════════════

```
* **commande lancée :** `jenga build --target NKMath`

## explication du comportement actuel 
j'ignore encorre si il sagit un bug du sysytheme ou d'un probleme propre à mon pc mais, jenga, chez moi recompile systhematiquement tous les fichiers sans verification de la date de modification .
---

## 2. Explication de l'écart selon le contexte attendu

L'écart entre les deux temps aurait été explique par la **gestion du cache et de la compilation** de Jenga :

1. **Lors du premier build :** Jenga doit compiler chaque fichier source `.cpp` en fichier objet `.obj` / `.o` puis exécuter l'éditeur de liens pour créer le binaire final.

2. **Lors du second build :** Jenga vérifie les horodatages (**timestamps**) de tous les fichiers du projet. Constatant qu'aucun fichier source `.cpp` ou d'en-tête `.h` n'a été modifié depuis la dernière passe, il conclut que tous les fichiers sont à jour. Aucun appel au compilateur ou au linker n'est déclenché, ce qui rend l'exécution presque instantanée.