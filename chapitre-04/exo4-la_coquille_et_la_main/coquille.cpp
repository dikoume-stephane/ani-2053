#include "NKCanvas/App/NkCanvasApp.h"
#include "NKWindow/NKMain.h"

class CarreCoquilleApp : public nkentseu::renderer::NkCanvasApp {
private:
    nkentseu::float32 mX = 50.0f;
    nkentseu::float32 speed = 100.0f;

public:
    CarreCoquilleApp() {
        Config().title = "Carre Coquille";
        Config().width = 800;
        Config().height = 600;
        Config().clearColor = nkentseu::renderer::NkColor2D(18, 18, 24);
    }

    bool OnInit() override {
        return true;
    }

    void OnUpdate(nkentseu::float32 dt) override {
        mX += speed * dt;
    }

    void OnRender(nkentseu::renderer::NkRenderWindow &target) override {
        nkentseu::renderer::NkRenderer2D &r2d = target.GetRenderer2D();
        r2d.DrawFilledRect(
            nkentseu::math::NkRect2f{mX, 250.0f, 100.0f, 100.0f},
            nkentseu::renderer::NkColor2D{230, 50, 50, 255}
        );
    }
};

int nkmain(const nkentseu::NkEntryState &state) {
    return nkentseu::renderer::NkCanvasApp::Run<CarreCoquilleApp>(state);
}
