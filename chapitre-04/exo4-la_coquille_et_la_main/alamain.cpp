#include "NKWindow/NKWindow.h"
#include "NKCanvas/Renderer/Targets/NkRenderWindow.h"
#include "NKTime/NkTime.h"
#include "NKWindow/NKMain.h"

int nkmain(const nkentseu::NkEntryState &state) {
    nkentseu::NkWindowConfig config{} ;
    config.title = state.appName ;
    config.width = 800;
    config.height = 600;

    nkentseu::NkWindow window;

    if (!window.Create(config)) {
        logger.Error("Failed to create window") ;
        return 1;
    }
    if (!window.IsOpen()) {
        return -1;
    }

    nkentseu::NkContextDesc contextDesc;
    contextDesc.api = nkentseu::NkGraphicsApi::NK_GFX_API_OPENGL;
    nkentseu::renderer::NkRenderWindow renderer(window,contextDesc);

    if (!renderer.IsValid()) {
        return -1;
    }

    auto &eventS = nkentseu::NkEvents();

    nkentseu::float32 x = 50.0f;
    nkentseu::NkClock clock;

    while (window.IsOpen()) {
        nkentseu::float32 dt = clock.Tick().delta;

        nkentseu::NkEvent *event;
        while (eventS.PollEvent(event)) {
            if (event->As<nkentseu::NkWindowCloseEvent>()) {
                window.Close();
            }
        }

        x += 100.0f * dt;

        renderer.Clear(nkentseu::renderer::NkColor2D(18, 18, 24));
        renderer.GetRenderer2D().DrawFilledRect(
            nkentseu::math::NkRect2f{x, 250.0f, 100.0f, 100.0f},
            nkentseu::renderer::NkColor2D(230, 50, 50, 255)
        );
        renderer.Display();
    }

    return 0;
}
