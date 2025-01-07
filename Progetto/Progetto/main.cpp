#define IMM2D_WIDTH 512
#define IMM2D_HEIGHT 512
#define IMM2D_SCALE 1
#define IMM2D_IMPLEMENTATION
#include "immediate2d.h"
#include <string>

using namespace std;

using Image = int;

//path delle immagini
static constexpr const char BgPng[] = "sfondo.png";
static constexpr const char SpriteStatic[] = "sprite_fermo.png";
static constexpr const char SpritePunch[] = "sprite_pugno.png";
static constexpr const char SpriteStaticRight[] = "sprite_fermo_right.png";
static constexpr const char SpritePunchRight[] = "sprite_pugno_right.png";
static constexpr const char SfondoMenu[] = "sfondo_menu.png";

int EnemyMovementX(int& EnemyX, int SpriteX);
int EnemyMovementY(int EnemyY, int SpriteY);
void MenuIniziale();

void run()
{
    void UseDoubleBuffering(bool enabled);
    MenuIniziale();

    int x = 0;
    int y = -512;
    int delay = 20;
    int SpriteX = 0;
    int SpriteY = 437;
    int EnemyX = 256;  // Posizione iniziale del nemico
    int EnemyY = 437;
    int colpiRicevuti = 0;
    int colpiDati = 0;
    int botte;
    bool nemicoMorto = false;
    bool personaggioMorto = false;
    string Health;
    string CandianiHealth;

    const Image Background = LoadImage(BgPng);
    const Image stat = LoadImage(SpriteStaticRight);
    const Image punch = LoadImage(SpritePunchRight);
    const Image statEnemy = LoadImage(SpriteStatic);
    const Image punchEnemy = LoadImage(SpritePunch);
    const Image BackgroundMenu = LoadImage(SfondoMenu);

    char ultimotasto;

    while (true) {

        

        // Movimento nemico
        EnemyMovementX(EnemyX, SpriteX);
        EnemyY = EnemyMovementY(EnemyY, SpriteY);

        ultimotasto = LastKey();
        Clear();

        Health = to_string(100 - colpiRicevuti);
        CandianiHealth = to_string(100 - colpiDati);
        const char* sprite = Health.c_str();
        const char* candi = CandianiHealth.c_str();
        

        // Controllo se il personaggio esce dallo schermo
        if (SpriteX < -5 || SpriteX > 500) {
            Clear(0);
            DrawImage(0, 0, BackgroundMenu);
            DrawString(256, 256, "SEI UN CODARDO", "Arial", 34, White, true);
            Wait(2000);
            Clear(0);
            DrawImage(0, 0, BackgroundMenu);
            DrawString(256, 156, "GAME OVER", "Arial", 34, White, true);
            break;
        }
        
        // Disegno dello sfondo
        DrawImage(x, y, Background);
        DrawRectangle(0, 0, 125, 65, White);
        DrawString(5, 5, " Your health", "Arial", 14, Black);
        DrawString(55, 25, sprite, "Arial", 24, Black);

        DrawRectangle(387, 0, 125, 65, White);
        DrawString(390, 5, "Candiani", "Arial", 14, Black);
        DrawString(445, 25, candi, "Arial", 24, Black);


        // Movimento del personaggio
        switch (ultimotasto) {
        case 'w':
            if (SpriteY <= 256) {

            }
            else {
                SpriteY -= 5;
            }
            
            break;
        case 's':
            
            SpriteY += 5;
            break;
        case 'a':
            SpriteX -= 5;
            break;
        case 'd':
            SpriteX += 5;
            break;
        }

        // Disegno del personaggio
        if (ultimotasto == ' ') {
            DrawImage(SpriteX, SpriteY, punch);
        }
        else {
            DrawImage(SpriteX, SpriteY, stat);
        }

        botte = RandomInt(0, 10);

        // Disegno del nemico se non è morto
        if (!nemicoMorto) {
            if ((EnemyX - SpriteX) < 45 && SpriteY == EnemyY && botte == 0) {
                DrawImage(EnemyX, EnemyY, punchEnemy);
                colpiRicevuti++;
                if (colpiRicevuti >= 100) {
                    personaggioMorto = true;  // Il personaggio è morto
                }
                else {
                    personaggioMorto = false;
                }
            }
            else {
                DrawImage(EnemyX, EnemyY, statEnemy);
            }
        }

        // Controllo se il nemico è stato colpito
        if (ultimotasto == ' ' && (EnemyX - SpriteX) < 45 && SpriteY == EnemyY) {
            colpiDati++;
            if (colpiDati >= 100) {
                nemicoMorto = true;  // Il nemico è morto
            }
        }

        

        
        if (nemicoMorto) {
            personaggioMorto = false;
        }
        if (personaggioMorto) {
            nemicoMorto = false;
        }



        // Se il nemico è morto
        if (nemicoMorto) {
            Clear();
            DrawImage(0, 0, BackgroundMenu);
            DrawString(256, 156, "IL NEMICO E MORTO!", "Arial", 34, White, true);
            Wait(2000);
            Clear();
            DrawImage(0, 0, BackgroundMenu);
            DrawString(256, 156, "HAI VINTO", "Arial", 34, White, true);
            break;
        }


        // Se il personaggio è morto
        if (personaggioMorto) {
            Clear();
            DrawImage(0, 0, BackgroundMenu);
            DrawString(256, 156, "SEI MORTO", "Arial", 34, White, true);
            Wait(2000);
            Clear();
            DrawImage(0, 0, BackgroundMenu);
            DrawString(256, 156, "GAME OVER", "Arial", 34, White, true);
            Wait(2000);
            break;
        }




        Wait(delay);

        Present();
    }
}

// Movimento del nemico lungo l'asse X
int EnemyMovementX(int& EnemyX, int SpriteX) {
    if (EnemyX > SpriteX + 45) {
        EnemyX -= 1;
    }
    else if (EnemyX <= SpriteX+35 ) {
        EnemyX += 10;
    }
    return EnemyX;
}

// Movimento del nemico lungo l'asse Y
int EnemyMovementY(int EnemyY, int SpriteY) {
    if (EnemyY > SpriteY) {
        EnemyY -= 1;
    }
    else if (EnemyY < SpriteY) {
        EnemyY += 1;
    }
    return EnemyY;
}

// Menu iniziale
void MenuIniziale()
{
    Clear();
    const Image BackgroundMenu = LoadImage(SfondoMenu);
    DrawImage(0, 0, BackgroundMenu);
    DrawString(256, 200, "BENVENUTO SU", "Arial", 25, White, true);
    DrawString(256, 230, "HALLWAYS OF MONNET", "Arial", 25, White, true);
    DrawString(256, 280, "premi enter per continuare...", "Arial", 13, White, true);

    while (true) {
        char key = LastKey();
        if (key == Enter) {
            break;
        }
    }
}