#include "NKMedia/Video/NkVideoReader.h"
#include "NKMedia/NkMediaProbe.h"
#include "NKLogger/NkLog.h"

using namespace nkentseu;

void processFile(const char* filepath) {
    NkVideoReader reader;
    bool opened = reader.Open(filepath);
    
    int frameCount = 0;
    if (opened) {
        // Journalisation des informations du lecteur si ouvert avec succès
        const auto& info = reader.Info();
        logger.Info("[LECTEUR] : Fichier ouvert : {0} | Conteneur: {1} | Codec: {2} | Dimensions: {3}x{4}", 
                    filepath, info.container, info.codec, info.width, info.height);

        // Compter les images lues via ReadFrame (selon l'API du lecteur)
        NkVideoFrame frame;
        while (reader.ReadFrame(frame)) {
            frameCount++;
        }
      
        frameCount = info.frameCount; 
    } else {
        logger.Error("[LECTEUR] : Echec de l'ouverture du fichier : {0}", filepath);
    }

    // Utilisation de la sonde pour analyser les pistes du fichier
    auto probeResult = NkMediaProbe::ProbeFile(filepath);
    logger.Info("[SONDE] : Fichier : {0} | Conteneur détecté : {1} | Codec détecté : {2}", 
                filepath, probeResult.container, probeResult.codec);
}

int main() {
   
    processFile("assets/film.mp4");
    processFile("assets/film_tronque.mp4");
    processFile("assets/texte_renomme.mp4");

    return 0;
}