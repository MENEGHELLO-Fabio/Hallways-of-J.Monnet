#define IMM2D_WIDTH 512
#define IMM2D_HEIGHT 512
#define IMM2D_SCALE 1
#define IMM2D_IMPLEMENTATION
#include "immediate2d.h"

using Image = int;

void run()
{
    int x = 0;
    int y = -512;
    int delay = 20;
    int SpriteX = 0;
    int SpriteY = 437;
    

    static constexpr const char BgPng[] = "sfondo.png";
    static constexpr const char SpriteStatic[] = "sprite_fermo.png";
    static constexpr const char SpritePunch[] = "sprite_pugno.png";
    static constexpr const char SpriteStaticRight[] = "sprite_fermo_right.png";
    static constexpr const char SpritePunchRight[] = "sprite_pugno_right.png";

    const Image Background = LoadImage(BgPng);
    const Image stat = LoadImage(SpriteStatic);
    const Image punch = LoadImage(SpritePunch);
    /*const Image stat = LoadImage(SpriteStatic);
    const Image punch = LoadImage(SpritePunch);*/

    char ultimotasto;

    while (true) {
        ultimotasto = LastKey();
        Clear();

        DrawImage(x, y, Background);
        switch (ultimotasto) {
        case ' ':
            x--;
            DrawImage(x, y, Background);
            x--;
            DrawImage(SpriteX, SpriteY, punch);
            x--;
            Wait(100);
            x--;
            break;
        case 'w':
            for (int i = 0; i < 5; i++) {
                SpriteY -= 1;
            }
            break;
        case 's':
            for (int i = 0; i < 5; i++) {
                SpriteY+=1;
            }
            break;
        case 'a':
            for (int i = 0; i < 5; i++) {

                SpriteX -= 1;
            }
            break;
        case 'd':
            for (int i = 0; i < 5; i++) {

                SpriteX += 1;
            }
            break;
        }

        
        DrawImage(x, y, Background);
        DrawImage(SpriteX, SpriteY, stat);


       
        Wait(delay);
        x--;
      
    }

    
}
