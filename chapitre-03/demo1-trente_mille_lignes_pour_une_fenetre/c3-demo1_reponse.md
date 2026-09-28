# Chapitre 03 — Démo 1 : Trente mille lignes pour une fenêtre

## 1. Mesures du module

* **Commande utilisée :** ` cloc Kernel\Runtime\NKWindow Kernel\Runtime\NKEvent `
```powershell
 167 text files.
     165 unique files.                                          
       2 files ignored.

github.com/AlDanial/cloc v 2.06  T=3.90 s (42.3 files/s, 17002.5 lines/s)
-------------------------------------------------------------------------------
Language                     files          blank        comment           code
-------------------------------------------------------------------------------
C++                             47           3132           4321          17407
C/C++ Header                   100           4599          17339          14232
Objective-C++                    8            451            288           2189
Markdown                         3            242              0           1076
TypeScript                       2             63            220            328
C                                2             38             51            179
Java                             3             25             52            118
-------------------------------------------------------------------------------
SUM:                           165           8550          22271          35529
-------------------------------------------------------------------------------
```

* **Nombre de fichiers source:** 155 (cpp et haeder)
* **Nombre de lignes :** 33 828

## 2. Liste des backends de plateforme
* **commande :** `ls -l Kernel\Runtime\NKWindow\src\NKWindow\Platform`

```powershell
 ls -l Kernel\Runtime\NKWindow\src\NKWindow\Platform

    Répertoire : D:\2DS\projet\programmation_cpp\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform

Mode                 LastWriteTime         Length Name
----                 -------------         ------ ----
d----          10/09/2026    19:59                Android
d----          10/09/2026    19:59                Cocoa
d----          10/09/2026    19:59                Common
d----          10/09/2026    19:59                Emscripten
d----          10/09/2026    19:59                HarmonyOS
d----          10/09/2026    19:59                Linux
d----          10/09/2026    19:59                Noop
d----          10/09/2026    19:59                UIKit
d----          10/09/2026    19:59                UWP
d----          10/09/2026    19:59                Wayland
d----          14/09/2026    20:19                Win32
d----          10/09/2026    19:59                Xbox
d----          10/09/2026    19:59                XCB
d----          10/09/2026    19:59                XLib
```
on a donc 14 backend de plateforme.

## 3. Comparaison de l'implémentation d'un appel (`SetTitle`)

* **pour windows :** dans le fichier `Kernel\Runtime\NKWindow\src\NKWindow\Platform\Win32\NkWin32Window.cpp`
```cpp
void NkWindow::SetTitle(const NkString &t) {
    mConfig.title = t;
    if (mData.mHwnd) {
        SetWindowTextW(mData.mHwnd, NkUtf8ToWide(t).CStr());
        // La synchronisation est déjà faite via la modification de mConfig
    }
}
```
* **pour XLIB :** dans le fichier `Kernel\Runtime\NKWindow\src\NKWindow\Platform\XLib\NkXLibWindow.cpp`
```cpp
void NkWindow::SetTitle(const NkString &title) {
		mConfig.title = title;
		if (mData.mDisplay && mData.mXid) {
			XStoreName(mData.mDisplay, mData.mXid, title.CStr());
		}
	}
```
## 4. Analyse des similitudes et des différences
Ce qui est identique entre les deux implémentations est QUE La signature de la fonction `NkWindow::SetTitle` prend un paramètre const NkString& et ne retourne rien.
Les deux versions mettent à jour la structure de configuration interne (`mConfig.title = ...`).

Ce qui change: Xlib utilise un pointeur de connexion au serveur X (`mData.mDisplay`) et un identifiant de fenêtre (`mData.mXid`), alors que Win32 utilise un unique pointeur de fenêtre HWND (`mData.mHwnd`). Xlib fait appel à `XStoreName`, tandis que Windows utilise l'API système `SetWindowTextW.Xlib` accepte la chaîne brute (title.CStr()), alors que Win32 exige une conversion explicite vers le format UTF-16 avec la fonction `NkUtf8ToWide(t).CStr()`.

## 5. Synthèse : Ce que le module absorbe
Le module absorbe la diversité des API système natives (Win32 et Xlib) en masquant leurs types de handles (HWND vs Display*/XID) et leurs fonctions d'appel sous une meme méthode C++. Il prend en charge l'adaptation des formats de données, comme la conversion de chaîne UTF-8 vers UTF-16 requise par l'API Windows. Il isole ainsi le code applicatif des détails de bas niveau, permettant la portabilité de l'application.