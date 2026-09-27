# Chapitre 03 — Exercice 9 : Les quatre dialogues

## 1. Code source ([`c3-exo9_main.cpp`](c3-exo9_main.cpp))

```cpp
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include "NKEvent/NkKeyboardEvent.h"
#include "NKEvent/NkWindowEvent.h"
#include <iostream>

using namespace nkentseu;

int nkmain(const NkEntryState& state) {
    NkWindowConfig cfg;
    cfg.title  = "Exo9 - Les quatre dialogues";
    cfg.width  = 800;
    cfg.height = 600;

    NkWindow window(cfg);
    if (!window.IsOpen()) {
        return -1;
    }

    std::cout << "=================== INSTRUCTIONS ===================" << std::endl;
    std::cout << " Appuyez sur [O] : Dialogue Ouvrir un fichier" << std::endl;
    std::cout << " Appuyez sur [S] : Dialogue Enregistrer un fichier" << std::endl;
    std::cout << " Appuyez sur [F] : Dialogue Choisir un dossier" << std::endl;
    std::cout << " Appuyez sur [M] : Message Box" << std::endl;
    std::cout << " Appuyez sur [ESC]     : Quitter" << std::endl;
    std::cout << "====================================================" << std::endl;

    while (window.IsOpen()) {
        while (NkEvent* ev = NkEvents().PollEvent()) {
            if (ev->Is<NkWindowCloseEvent>()) {
                window.Close();
            }
            else if (auto* kp = ev->As<NkKeyPressEvent>()) {
                if (kp->GetKey() == NkKey::NK_ESCAPE) {
                    window.Close();
                }
                // 1. Dialogue : Ouvrir un fichier
                else if (kp->GetKey() == NkKey::NK_O) {
                    std::cout << "\n[1. Ouvrir Fichier]";
                    NkDialogResult r = NkDialogs::OpenFileDialog("*.png;*.jpg;*.txt", "Ouvrir une image");
                    if (r.confirmed) {
                        std::cout << "\n-> Fichier choisi avec Succès : " << r.path.CStr();
                    } else {
                        std::cout << "\n-> Annule ou ferme sans selection.";
                    }
                }
                // 2. Dialogue : Sauvegarder un fichier
                else if (kp->GetKey() == NkKey::NK_S) {
                    std::cout << "\n[2. Sauvegarder Fichier]";
                    NkDialogResult r = NkDialogs::SaveFileDialog(".dox;*.txt", "Enregistrer la planche");
                    if (r.confirmed) {
                        std::cout << "\n-> le fichier est suvegarde dans : " << r.path.CStr();
                    } else {
                        std::cout << "\n-> Annule ou ferme sans enregistrement.";
                    }
                }
                // 3. Dialogue : Ouvrir un dossier
                else if (kp->GetKey() == NkKey::NK_F) {
                    std::cout << "\n[3. Choisir un Dossier]";
                    NkDialogResult r = NkDialogs::OpenFolderDialog("Choisir un dossier");
                    if (r.confirmed) {
                        std::cout << "\n-> Dossier choisi avec Succes : " << r.path.CStr();
                    } else {
                        std::cout << "\n-> Annule ou ferme sans selection.";
                    }
                }
                // 4. Dialogue : Message Box
                else if (kp->GetKey() == NkKey::NK_M) {
                    std::cout << "\n[4. Message Box]";
                    NkDialogs::OpenMessageBox("Fichier introuvable", "Erreur");
                }
            }
        }
    }

    return 0;
}
```

## 2. sortie du terminal
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

=================== INSTRUCTIONS ===================
 Appuyez sur [O] : Dialogue Ouvrir un fichier
 Appuyez sur [S] : Dialogue Enregistrer un fichier
 Appuyez sur [F] : Dialogue Choisir un dossier
 Appuyez sur [M] : Message Box
 Appuyez sur [ESC]     : Quitter
====================================================

[1. Ouvrir Fichier]
-> Fichier choisi avec Succ├¿s : C:\Users\stephane dikoume 2DS\Documents\j.docx
[1. Ouvrir Fichier]
-> Annule ou ferme sans selection.
[2. Sauvegarder Fichier]
-> le fichier est suvegarde dans : C:\Users\stephane dikoume 2DS\Documents\exo10.txt
[2. Sauvegarder Fichier]
-> Annule ou ferme sans enregistrement.
[3. Choisir un Dossier]
-> Dossier choisi avec Succes : C:\Users\stephane dikoume 2DS
[3. Choisir un Dossier]
-> Annule ou ferme sans selection.
[4. Message Box]
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (127.29s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```
Le programme intègre les quatre fonctions de dialogues proposées par le module `NkDialogs`. Pour chaque dialogue, le retour est analysé via le champ `.confirmed` afin de verifier qu'il n'y a pas eu de problemme lorsque l'utilisateur annule ou ferme la boîte de dialogue sans faire de choix.