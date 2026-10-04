#include "NKCanvas/App/NkCanvasApp.h"
#include "NKWindow/NKMain.h"

using namespace nkentseu;

class FenetreNueApp : public renderer::NkCanvasApp {
public:
    FenetreNueApp() {
        Config().title = "La fenetre nue";
        Config().width = 800;
        Config().height = 600;
        Config().clearColor = renderer::NkColor2D(18, 18, 24);
    }

    bool OnInit() override {
        return true;
    }
};

int nkmain(const NkEntryState& state) {
    return renderer::NkCanvasApp::Run<FenetreNueApp>(state);
}
