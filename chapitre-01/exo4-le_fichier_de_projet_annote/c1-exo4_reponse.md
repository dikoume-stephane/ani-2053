## fichier jenga choisi 
le fichier jenga choisi est **"Sandbox\System\NKReflection\NKReflectionSandbox.jenga"**
```py
#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
SandboxNKReflection
===================
Projet sandbox cible pour valider NKReflection avec ses dependances
Foundation + System en build isole.
"""

from Jenga import *
# Importe l'API de Jenga avec les fonctions (project, consoleapp, files, filter, etc.).

from jengaconfig import *
# Importe la configuration spécifique du dépôt


with project("SandboxNKReflection"):
# Déclare un nouveau projet nommé "SandboxNKReflection" dans le gestionnaire de contexte.

    consoleapp()
    # TYPE : Spécifie que le projet produit un exécutable avec console.

    language("C++")
    # Spécifie le langage source principal.

    cppdialect("C++17")
    # Définit le standard C++ à utiliser (C++17).

    location(".")
    # Définit le dossier racine du projet (ici, c'st le dossier  où se trouve ce fichier).

    files([
        "src/main.cpp",
    ])
    # SOURCES : Liste des fichiers C++ à compiler pour ce projet.

    includedirs([
        "src",
        "%{NKReflection.location}/src",
        "%{NKLogger.location}/src",
        "%{NKThreading.location}/src",
        "%{NKContainers.location}/src",
        "%{NKMemory.location}/src",
        "%{NKCore.location}/src",
        "%{NKPlatform.location}/src",
    ])
    # EN-TÊTES : Dossiers d'inclusions pour que le compilateur trouve les headers des modules.

    _LINKS = [
        "NKReflection",
        "NKLogger",
        "NKThreading",
        "NKContainers",
        "NKMemory",
        "NKCore",
        "NKPlatform",
    ]
    # VARIABLE PYTHON :  liste contenant le nom de tous les modules internes requis.

    links(_LINKS)
    # ÉDITION DE LIENS : Indique d'inclure les  bibliothèques de la liste à l'édition de liens finale.

    dependson(_LINKS)
    # DÉPENDANCES DE BUILD : Impose à Jenga de construire les projet de la liste celui-ci.

    objdir("%{wks.location}/Build/Obj/%{cfg.buildcfg}-%{cfg.system}/%{prj.name}")
    # Dossier où seront générés les fichiers objets intermédiaires (.o/.obj).

    targetdir("%{wks.location}/Build/Bin/%{cfg.buildcfg}-%{cfg.system}/%{prj.name}")
    # Dossier où sera généré l'exécutable final.

    # FILTRES DE PLATEFORME 

    with filter("system:Windows && options:windows-runtime=uwp"):
    # FILTRE : S'applique uniquement si la cible est Windows ET en mode UWP.
        objdir("%{wks.location}/Build/Obj/%{cfg.buildcfg}-%{cfg.system}-uwp/%{prj.name}")
        targetdir("%{wks.location}/Build/Bin/%{cfg.buildcfg}-%{cfg.system}-uwp/%{prj.name}")
        # Redéfinit des dossiers d'intermédiaires (pour la compilation en 2 temps) et de sortie spécifiques pour UWP.

    with filter("system:Windows && !options:windows-runtime=uwp && !system:XboxSeries && !system:XboxOne"):
    # FILTRE : Windows  ( UWP, Xbox Series et Xbox One).
        usetoolchain(TC_WINDOWS)
        # Configure la chaîne de compilation Windows standard.
        
        links(["user32", "shell32"])
        # ÉDITION DE LIENS : Ajoute les bibliothèques système Windows nécessaires.

    with filter("system:UWP || system:Windows && options:windows-runtime=uwp"):
    # FILTRE : Cibles UWP.
        usetoolchain("xbox-clang")
        # Utilise le compilateur Clang adapté pour l'écosystème UWP et xbox.

    with filter("system:Linux"):
    # FILTRE : Environnement Linux.
        usetoolchain("clang-native")
        # Utilise Clang natif Linux.
        
        links(["pthread"])
        # ÉDITION DE LIENS : Ajoute la bibliothèque de pthread pour linux.

    with filter("system:macOS"):
    # FILTRE : Environnement macOS.
        usetoolchain("clang-native")
        # Utilise Clang natif macOS.
        
        links(["pthread"])
        # ÉDITION DE LIENS : Ajoute la bibliothèque de pthread pour mac os.

    with filter("system:Android"):
    # FILTRE : Plateforme Android.
        usetoolchain("android-ndk")
        # Utilise le NDK d'Android pour le build cross-platform.
        
        links(["log"])
        # ÉDITION DE LIENS : Ajoute la bibliothèque de log native d'Android (`liblog`).

    with filter("system:Web"):
    # FILTRE : Compilation Web (WebAssembly).
        usetoolchain("emscripten")
        # Utilise le compilateur Emscripten.

    with filter("system:XboxSeries || system:XboxOne"):
    # FILTRE : Consoles Xbox.
        usetoolchain("xbox-clang")
        # Utilise la chaîne de compilation spécifique aux consoles Xbox.

    # FILTRES DE CONFIGURATION 

    with filter("config:Debug"):
    # filtre du mode Debug.
        defines(["_DEBUG", "DEBUG", "NKENTSEU_DEBUG"])
        # Macros du préprocesseur pour activer les .
        
        optimize("Off")
        # Désactive les optimisations .
        
        symbols(True)
        # ?

    with filter("config:Release"):
    # filtre du mode Release.
        defines(["NDEBUG"])
        # Macro du mode debug.
        
        optimize("Speed")
        # Optimise l'exécutable.
        
        symbols(False)
        # ?
```
