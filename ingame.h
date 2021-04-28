#include <SDL.h>
#include <SDL_image.h>
#include <string.h>
#include<windows.h>
#include<sstream>

#include "them1.h"
struct Block {
    double x;
    double y;
    int size;

};

struct kieuquandich {
    Block b;
    bool song;
    bool chet;
};
//--------------------------
struct drawnguoichoi {
    Block b;
};

//--------------------------
///cửa sổ terminal
struct State {
    int w;
    int h;

    static const int N = 100; // max number of enemies
    kieuquandich quandich[N];

    drawnguoichoi PLAYER;
    Block danban;
    Block timeleft;
    bool bantrung;
};
///-----------------------------------
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
//----------------------------------
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);
//------------------------------
void init_state(State &s, int stage);
//-------------------------------
void draw_block(SDL_Renderer *r, Block &b);
//----------------------------------
void render(SDL_Renderer *rend, State &s, SDL_Texture *texture
            ,SDL_Texture *texture_plane,SDL_Texture *texture_bullet
            ,SDL_Texture *texture_00,SDL_Texture *texture_11,SDL_Texture *texture_22,SDL_Texture *texture_33
            ,SDL_Texture *texture_44,SDL_Texture *texture_55,SDL_Texture *texture_66,SDL_Texture *texture_77
            ,SDL_Texture *texture_88,SDL_Texture *texture_99,SDL_Texture *texture_death
            ,int nvkhong,int nvmot,int nvhai,int nvba,int nvbon,int nvnam
            ,SDL_Texture *texture_0,SDL_Texture *texture_1,SDL_Texture *texture_2,SDL_Texture *texture_3,SDL_Texture *texture_4,SDL_Texture *texture_5);
//-----------------------------------
void run(SDL_Window *window,SDL_Renderer *renderer, State &s
            ,int nvkhong,int nvmot,int nvhai,int nvba,int nvbon,int nvnam);
//-------------------------------------
void update_state(State &s, double dt);
///-------------------------------
