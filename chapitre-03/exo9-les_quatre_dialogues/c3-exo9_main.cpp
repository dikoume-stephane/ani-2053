#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
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