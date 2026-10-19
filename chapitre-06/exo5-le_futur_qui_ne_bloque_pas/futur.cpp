#include <NKWindow/NKWindow.h>
#include <NKCanvas/NKCanvas.h>
#include <NKThreading/NkThread.h>
#include <NKThreading/NkThreadPool.h>
#include <NKThreading/NkPromise.h>
#include <NKThreading/NkFuture.h>
#include <NKCore/NkChrono.h>
#include <NKCore/NkTraits.h>
#include <iostream>
#include <algorithm>

using namespace nkentseu;
using namespace nkentseu::threading;

constexpr bool kUseBlockingGet = false; 

int nkmain(const NkEntryState &state)
{
    // Création de la fenêtre et du canvas de dessin
    NkWindow window("Exercice 5 - Asynchronous Image Loader", 800, 600);
    NkCanvas canvas(window);

    // Réserve de fils et synchronisation asynchrone
    NkThreadPool pool(2);
    NkPromise<NkImage> promesse;
    NkFuture<NkImage> futur = promesse.GetFuture();

    NkImage loadedImage;
    bool imageLoadedAndRetrieved = false;
    bool loadingStarted = false;

    // Métriques de performance
    int frameCount = 0;
    int framesDuringLoading = 0;
    double maxFrameTimeMs = 0.0;

    int squareX = 0;
    NkChrono frameChrono;

    while (window.IsOpen()) {
        frameChrono.Reset();
        window.PollEvents();

        frameCount++;

        // Lancement du chargement asynchrone au bout de 60 trames
        if (frameCount == 60 && !loadingStarted) {
            loadingStarted = true;
            pool.Enqueue([&promesse]() {
                NkImage img;
                // Remplacez par le nom/chemin de votre grande photo
                img.Load("grande-photo.png"); 
                promesse.SetValue(nkentseu::traits::NkMove(img));
            });

            // Version 1 : Appel direct de Get() (bloque le thread principal)
            if (kUseBlockingGet) {
                loadedImage = futur.Get();
                imageLoadedAndRetrieved = true;
            }
        }

        // Compte le nombre de trames dessinées pendant que le chargement est en cours
        if (loadingStarted && !imageLoadedAndRetrieved) {
            framesDuringLoading++;

            if (!kUseBlockingGet && futur.IsReady()) {
                loadedImage = futur.Get();
                imageLoadedAndRetrieved = true;
            }
        }

        canvas.Clear(NkColor::Black);

        if (imageLoadedAndRetrieved && loadedImage.IsValid()) {
            canvas.DrawImage(loadedImage, 0, 0);
        }

        squareX = (squareX + 1) % window.GetWidth();
        canvas.FillRect(squareX, 280, 40, 40, NkColor::Red);

        canvas.Present();

        double currentFrameTimeMs = frameChrono.Elapsed().milliseconds();
        if (currentFrameTimeMs > maxFrameTimeMs) {
            maxFrameTimeMs = currentFrameTimeMs;
        }
    }

    std::cout << "Mode : " << (kUseBlockingGet ? "Get" : "IsReady") << std::endl;
    std::cout << "Trame la plus longue : " << maxFrameTimeMs << " ms" << std::endl;
    std::cout << "Trames pendant le chargement : " << framesDuringLoading << std::endl;

    return 0;
}