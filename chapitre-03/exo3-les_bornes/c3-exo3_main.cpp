#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include "NKEvent/NkKeyboardEvent.h"
#include "NKEvent/NkWindowEvent.h"

using namespace nkentseu;

int nkmain(const NkEntryState& state) {
    NkWindowConfig cfg;
    cfg.title  = "Exo2 - Les sept droits";
    cfg.width  = 800;
    cfg.height = 600;
    cfg.minHeight = 200;
    cfg.minWidth = 200;

    // les 7 droits
    cfg.resizable = false; 
    cfg.movable = true;  
    cfg.closable = true;  
    cfg.minimizable = false;  
    cfg.maximizable = true;  
    cfg.canFullscreen = false; 
    cfg.fullscreen = false; 

    NkWindow window(cfg);

    nkentseu::math::NkVec2T size = window.GetSize();

     std::cout << "\nla taille : ( "<< size.height<<"H , "<<size.width<<" W ) au depart"; 

    if (!window.IsOpen()) {
        return -1;
    }

    while (window.IsOpen()) {
        while (NkEvent* ev = NkEvents().PollEvent()) {
            if (ev->Is<NkWindowCloseEvent>()) {
                window.Close();
            }
            else if (auto* kp = ev->As<NkKeyPressEvent>()) {
                // Touche ÉCHAP pour fermer 
                if (kp->GetKey() == NkKey::NK_ESCAPE) {
                    window.Close();
                }
            }

            if (auto* rz = ev->As<NkWindowResizeEvent>()) 
            {
                math::NkVec2u size = window.GetSize();
                
                std::cout << "\nla taille : ( "<< size.height<<"H , "<<size.width<<" W ) redimentionnét"; 
            }
           
        }
    }

    return 0;
}
