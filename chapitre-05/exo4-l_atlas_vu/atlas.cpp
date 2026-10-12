#include "NKImage/Core/NkImage.h"
#include "NKCanvas/Renderer/Resources/NkFont.h"
#include "NKFont/NkFont.h"
#include "NKLogger/NkLog.h"

using namespace nkentseu;

int main() {
    const char* fontPath = "window/assets/Sekuya-Regular.ttf";

    // 18 px
    {
        NkFontAtlas atlas18;
    
        NkFont* font18 = atlas18.AddFontFromFile(fontPath, 18.f);
        atlas18.Build();

        uint8* pixels18 = nullptr;
        int32 width18 = 0, height18 = 0;
        atlas18.GetTexDataAsRGBA32(&pixels18, &width18, &height18);
        if (pixels18 && width18 > 0 && height18 > 0) {
            NkImage img18 = NkImage::Wrap(const_cast<uint8*>(pixels18), width18, height18, NkImagePixelFormat::NK_RGBA32);
            //img18.SavePNG("atlas_18.png"); 
        }
    }

    // 48 px
    {
        NkFontAtlas atlas48;
        NkFont* font48 = atlas48.AddFontFromFile(fontPath, 48.f);
        
        atlas48.Build();

        uint8* pixels48 = nullptr;
        int32 width48 = 0, height48 = 0;
        atlas48.GetTexDataAsRGBA32(&pixels48, &width48, &height48);

        if (pixels48 && width48 > 0 && height48 > 0) {
            NkImage img48 = NkImage::Wrap(const_cast<uint8*>(pixels48), width48, height48, NkImagePixelFormat::NK_RGBA32);
            img48.SavePNG("atlas.png");
            
            logger.Info("[APP] : Atlas 48 genere avec succes {0} - {1}", width48, height48);
        } else {
            logger.Error("[APP] : Echec de generation de l'atlas de police.");
        }
    }

    return 0;
}