#include "NKCanvas/App/NkCanvasApp.h"
#include "NKWindow/NKMain.h"

using namespace nkentseu::renderer;

class FenetreNueApp : public NkCanvasApp {
public:
    FenetreNueApp() {
        Config().title = "La fenetre nue";
        Config().width = 800;
        Config().height = 600;
        Config().clearColor = NkColor2D(18, 18, 24);
    }

    bool OnInit() override {
        return true;
    }
};

int nkmain(const nkentseu::NkEntryState& state) {
    return NkCanvasApp::Run<FenetreNueApp>(state);
}
