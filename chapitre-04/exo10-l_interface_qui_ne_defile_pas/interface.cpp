#include "NKWindow/NKMain.h"
#include "NKWindow/NKWindow.h"
#include "NKCanvas/Renderer/Targets/NkRenderWindow.h"
#include "NKCanvas/Renderer/Shapes/NkRectangleShape.h"
#include "NKMath/NKMath.h"
#include "NKTime/NkTime.h"

NKENTSEU_DEFINE_APP_DATA(([]() {
    nkentseu::NkAppData d{};
    d.appName = "exo10-l_interface_qui_ne_defile_pas";
    d.appVersion = "1.0.0";
    return d;
})())

int nkmain(const nkentseu::NkEntryState &state) {
    nkentseu::NkWindowConfig config{};
    config.title = state.appName;
    config.width = 800;
    config.height = 600;

    nkentseu::NkWindow window;
    if (!window.Create(config)) return 1;

    nkentseu::NkContextDesc contextDesc;
    contextDesc.api = nkentseu::NkGraphicsApi::NK_GFX_API_OPENGL;

    nkentseu::renderer::NkRenderWindow renderWindow(window, contextDesc);
    if (!renderWindow.IsValid()) return 2;

    nkentseu::renderer::NkRectangleShape square({80.f, 80.f});
    square.SetFillColor(nkentseu::renderer::NkColor2D{52, 150, 84, 255});

    nkentseu::renderer::NkRectangleShape uiBar({800.f, 50.f});
    uiBar.SetFillColor(nkentseu::renderer::NkColor2D{200, 50, 50, 255});
    uiBar.SetPosition({0.f, 0.f});

    nkentseu::renderer::NkView2D worldView;
    worldView.center = {400.f, 300.f};
    worldView.size = {800.f, 600.f};

    nkentseu::float32 speed = 100.f;
    nkentseu::NkClock clock;
    bool running = true;

    while (running && window.IsOpen()) {
        nkentseu::float32 dt = clock.Tick().delta;
        if (dt > 0.1f) dt = 1.0f / 60.0f;

        nkentseu::NkEvent *event;
        while (nkentseu::NkEvents().PollEvent(event)) {
            if (event->Is<nkentseu::NkWindowCloseEvent>()) {
                running = false;
            }
        }

        // Avancée du centre de la vue avec dt
        worldView.center.x += speed * dt;

        renderWindow.Clear(nkentseu::renderer::NkColor2D(30, 30, 30, 255));

        //Appliquer la vue du monde
        renderWindow.SetView(worldView);

        // Dessin des objets du monde
        for (int i = 0; i < 30; ++i) {
            square.SetPosition({i * 120.f, 260.f});
            renderWindow.Draw(square);
        }

        //renderWindow.ResetView();
        

        //Dessiner la barre d'interface
        renderWindow.Draw(uiBar);

        renderWindow.Display();
    }

    return 0;
}