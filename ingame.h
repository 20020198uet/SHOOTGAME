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
    int w; // window width
    int h; // window height

    int stage; // level = 0, 1, 2 , ...

    static const int N = 100; // max number of enemies
    kieuquandich quandich[N];
    double global_time;

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
void render(SDL_Renderer *rend, State &s,int coloring, SDL_Texture *texture, SDL_Texture *texture_plane,SDL_Texture *texture_enemy);
//-----------------------------------
void run(SDL_Renderer *renderer, State &s, int x);
//-------------------------------------
void update_state(State &s, double dt);
///-------------------------------
