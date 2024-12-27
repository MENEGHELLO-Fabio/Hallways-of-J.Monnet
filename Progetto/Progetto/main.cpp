#define IMM2D_WIDTH 512
#define IMM2D_HEIGHT 512
#define IMM2D_SCALE 1
#define IMM2D_IMPLEMENTATION
#include "immediate2d.h"

using Image = int;

static constexpr const char BgPng[] = "sfondo.png";
static constexpr const char SpriteStatic[] = "sprite_fermo.png";
static constexpr const char SpritePunch[] = "sprite_pugno.png";
static constexpr const char SpriteStaticRight[] = "sprite_fermo_right.png";
static constexpr const char SpritePunchRight[] = "sprite_pugno_right.png";



int EnemyMovementX(int EnemyX, int SpriteX);
int EnemyMovementY(int EnemyY, int SpriteY);

void run()
{
    int x = 0;
    int y = -512;
    int delay = 20;
    int SpriteX = 0;
    int SpriteY = 437;
	int EnemyX = 400;
	int EnemyY = 437;
    
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
            
            DrawImage(x, y, Background);
            
            DrawImage(SpriteX, SpriteY, punch);
            
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
        
		EnemyX = EnemyMovementX(EnemyX, SpriteX);
		EnemyY = EnemyMovementY(EnemyY, SpriteY);

		DrawImage(EnemyX, EnemyY, stat);
       
        Wait(delay);
        
      
    }

    
}

int EnemyMovementX(int EnemyX, int SpriteX) {
	if (EnemyX > SpriteX) {

			EnemyX -= 1;
		
	}
	else if (EnemyX < SpriteX) {
		
			EnemyX += 1;
		
	}

    return EnemyX;
}
int EnemyMovementY(int EnemyY, int SpriteY) {
    if (EnemyY > SpriteY) {

        EnemyY -= 1;

    }
    else if (EnemyY < SpriteY) {

        EnemyY += 1;

    }

    return EnemyY;
}