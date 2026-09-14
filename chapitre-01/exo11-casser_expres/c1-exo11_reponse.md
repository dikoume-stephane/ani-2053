# Exercice 11 : Interruption du build et ordre de construction

## 1. Protocole expérimental
* **Fichier modifié :** Introduction volontaire d'une erreur de syntaxe dans un fichier source du module `NKMath` .
* le fichier choisi est `Kernel\Foundation\NKMath\src\NKMath\NkFunctions.cpp`
* l'erreur :
```cpp
* @param x Valeur d'entrée
		 * @return Plus grand entier <= x
		 */
		float64 NkFloor(float64 x) noexcept {
			retuurn floor(x);
		}

```

* **Action :** Lancement d'une reconstruction globale via `jenga build --target NKMath`.
led: NkInitializerList.cpp
✓   [19/43] Compiled: NkIterator.cpp
✓   [20/43] Compiled: NkContainers.cpp
✓   [21/43] Compiled: NkDeque.cpp
✓   [22/43] Compiled: NkDoubleList.cpp
✓   [23/43] Compiled: NkList.cpp
✓   [24/43] Compiled: NkVector.cpp
✓   [25/43] Compiled: NkGraph.cpp
✓   [26/43] Compiled: NkQuadTree.cpp
✓   [27/43] Compiled: NkASCII.cpp
✓   [28/43] Compiled: NkEncoding.cpp
✓   [29/43] Compiled: NkUTF16.cpp
✓   [30/43] Compiled: NkBase64.cpp
✓   [31/43] Compiled: NkUTF32.cpp
✓   [32/43] Compiled: NkUTF8.cpp
✓   [33/43] Compiled: NkBasicString.cpp
✓   [34/43] Compiled: NkFormat.cpp
✓   [35/43] Compiled: NkString.cpp
✓   [36/43] Compiled: NkStringBuilder.cpp
✓   [37/43] Compiled: NkStringHash.cpp
✓   [38/43] Compiled: NkOptional.cpp
✓   [39/43] Compiled: NkStringUtils.cpp
✓   [40/43] Compiled: NkStringView.cpp
✓   [41/43] Compiled: NkResult.cpp
✓   [42/43] Compiled: NkVariant.cpp
✓   [43/43] Compiled: NkSpan.cpp
ℹ Linking...
✓ Built: Build\Lib\Debug-Windows\NKContainers.lib

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                            Time: 32.15s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: NKMath                                                           Kind: STATIC_LIB  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 12 source file(s)
✓   [1/12] Compiled: NkAngle.cpp
✓   [2/12] Compiled: NkEulerAngle.cpp
✓   [3/12] Compiled: NkColor.cpp

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                              Compilation Error: NkFunctions.cpp                              ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ D:\2DS\projet\programmation_cpp\Nkentseu\Kernel\Foundation\NKMath\src\NKMath\NkFunctions.cpp ║
║ :71:4: error: use of undeclared identifier 'retuurn'; did you mean 'return'?                 ║
║    71 |                         retuurn floor(x);                                            ║
║       |                         ^~~~~~~                                                      ║
║       |                         return                                                       ║
║ 1 error generated.                                                                           ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: D:\2DS\projet\programmation_cpp\Nkentseu\Kernel\Foundation\NKMath\src\NKMath\NkFunctions.cpp
✓   [5/12] Compiled: NkMat.cpp
✓   [6/12] Compiled: NkQuat.cpp
✓   [7/12] Compiled: NkRandom.cpp
✓   [8/12] Compiled: NkRange.cpp
✓   [9/12] Compiled: NkRectangle.cpp
✓   [10/12] Compiled: NkSIMD.cpp
✓   [11/12] Compiled: NkSegment.cpp
✓   [12/12] Compiled: NkVec.cpp

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✗ Build Failed                                                                Time: 48.84s  │
│ Errors: 2  | Failed files: 1                                                                 │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                  BUILD FAILED                                  
════════════════════════════════════════════════════════════════════════════════
Projects Built:  4/5
Failed:         1
Errors:         2
Time:           1m54.1s
Status:         ✗ FAILURE
════════════════════════════════════════════════════════════════════════════════

Echecs (1) — a corriger :
  ✗ NKMath

```

## 2. Observations suite au crash

### A. Temps d'arrêt de la construction
La construction ne s'est arrêté pas très rapidement (en environ **1m54.1 secondes**). Le moteur n'a pas attendu de parcourir l'ensemble du projet pour échouer ; il a stoppé le processus dès que le compilateur a renvoyé un code d'erreur (exit code 1) sur le fichier modifié.

### B. Projets quand même construits
Malgré l'erreur dans `NKMath`, certains projets ont affiché un succès avant le crash. Ce sont exclusivement les fondations de plus bas niveau :
* `NKPlatform`
* `NKCore`
* `NKMemory`
* `NKContainers`

### C. Ce que le message d'erreur nous apprend sur l'ordre de construction
L'erreur et l'arrêt brutal démontrent clairement comment Jenga gère le graphe de dépendances :
1. **Ordre Topologique strict (bas vers le haut) :** Le build commence toujours par les feuilles de l'arbre (les modules qui n'ont aucune dépendance, comme `NKPlatform` et `NKCore`). C'est pourquoi ces projets ont pu être construits avec succès avant le crash.
2. **Propagation de l'échec (Cascade) :** Dès que `NKMath` a échoué, Jenga a immédiatement annulé  la compilation de tous les modules qui en dépendent (le comporte ment aurait étét plus visible si on avait compliler "MonEssai" avec les dependances de NKMath).
3. **Parallélisme limité par les dépendances :** Le système de build ne tente même pas de compiler des fichiers d'un module supérieur tant que 100 % de ses dépendances de niveau inférieur ne sont pas validées.

## 3. Remise en état
Le fichier source de `NKMath` a été corrigé (retrait de la faute de syntaxe). Une nouvelle commande `jenga build --target NKMath` a permis de reprendre la construction là où elle s'était arrêtée, validant la reprise incrémentale.