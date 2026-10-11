#include "NKWindow/NKMain.h"
#include "NKWindow/NKWindow.h"
#include "NKImage/Core/NkImage.h"
#include "NKLogger/NkLog.h"
#include <vector>
#include <string>

using namespace nkentseu;

int nkmain(const nkentseu::NkEntryState &state) {

    NkWindow window;
    NkWindowConfig cfg;
    cfg.title = "Exo 1 - Calcul et Mesure Memoire";
    cfg.width = 800;
    cfg.height = 600;
    if (!window.Create(cfg)) {
        return -1;
    }

    std::vector<NkImage> imagesChargees;
   
    const std::vector<std::string> chemins = {
        "window/assets/icone.png",
        "window/assets/capture.png",
        "window/assets/aplat.png",
        "window/assets/photo1.jpg",
        "window/assets/photo2.jpg"
    };

    logger.Info("[APP] : Instructions : Appuyez sur les touches 1, 2, 3, 4 ou 5 pour charger chaque image.");

    bool running = true;
    while (running && window.IsOpen()) {
       
        while (NkEvent* ev = NkEvents().PollEvent()) {
            if (ev->Is<NkWindowCloseEvent>()) {
                window.Close();
                running = false;
            }
        
            else if (auto* kp = ev->As<NkKeyPressEvent>()) {
                int index = -1;
                
                if (kp->GetKey() == NkKey::NK_NUM1 || kp->GetKey() == NkKey::NK_NUMPAD_1) index = 0;
                else if (kp->GetKey() == NkKey::NK_NUM2 || kp->GetKey() == NkKey::NK_NUMPAD_2) index = 1;
                else if (kp->GetKey() == NkKey::NK_NUM3 || kp->GetKey() == NkKey::NK_NUMPAD_3) index = 2;
                else if (kp->GetKey() == NkKey::NK_NUM4 || kp->GetKey() == NkKey::NK_NUMPAD_4) index = 3;
                else if (kp->GetKey() == NkKey::NK_NUM5 || kp->GetKey() == NkKey::NK_NUMPAD_5) index = 4;

                if (index >= 0 && index < (int)chemins.size()) {
                    NkImage img;
                   
                    if (img.Load(chemins[index].c_str(), 4) && img.IsValid()) {
                        int32 w = img.Width();
                        int32 h = img.Height();
                        int32 bpp = img.BytesPP();
                        usize calculMemoire = (usize)w * (usize)h * (usize)bpp;

                        logger.Info("[APP] : Image {0} - Largeur {1} - Hauteur {2} - BytesPP() : {3} - Calcul RAM : {4} octets",
                                     chemins[index].c_str(), w, h, bpp, calculMemoire);

                        imagesChargees.push_back(std::move(img));
                    } else {
                        logger.Error("[APP] : Echec du chargement de l'image : {0}", chemins[index].c_str());
                    }
                }
            }
        }
    }

    return 0;
}