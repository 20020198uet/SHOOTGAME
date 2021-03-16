#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include<string.h>
#include <time.h>
#include <math.h>

//SDL_Texture* loadTexture(const string &file, SDL_Renderer *ren);



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

struct nguoichoi {
    Block b;
};
///cửa sổ terminal
struct State {
    int w; // window width
    int h; // window height

    int stage; // level = 0, 1, 2 , ...

    static const int N = 100; // max number of enemies
    kieuquandich quandich[N];
    double global_time;

    nguoichoi PLAYER;
    Block danban;
    bool bantrung;
};
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
//----------------------------------
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);
//------------------------------
void init_state(State &s, int stage);

void draw_block(SDL_Renderer *r, Block &b);

void render(SDL_Renderer *renderer, State &s);

void run(SDL_Renderer *renderer, State &s);

void update_state(State &s, double dt);

int main(int argc, char* args[]) {
    State s;
    init_state(s, 0);


	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Surface* tempSurface = NULL;
	SDL_Texture* texture = NULL;
	SDL_Event mainEvent;
	SDL_Rect sourceRect;
	SDL_Rect desRect;
	bool isRunning = true;
	//initializes  the subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("Unable to initialize SDL %s\n", SDL_GetError());
		return -1;
	}

	//Create window
	window = SDL_CreateWindow("HUY GAME ", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,870, 600, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		printf("Could not create window %s", SDL_GetError());
		return -1;
	}
	//create a renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		printf("Could not create render %s", SDL_GetError());
		return -1;
	}

	//create a tempSurface
	tempSurface = SDL_LoadBMP("theme2.bmp");
	//create a texutre from surface
	texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	//free surface
	SDL_FreeSurface(tempSurface);


	SDL_QueryTexture(texture, NULL, NULL, &sourceRect.w, &sourceRect.h);

	sourceRect.x = 0;
	sourceRect.y = 0;
	sourceRect.w = sourceRect.w ;
	sourceRect.h = sourceRect.h ;

	desRect.x = 0;
	desRect.y = 0;
	desRect.w = sourceRect.w;
	desRect.h = sourceRect.h;

	//set background color
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	//main loop
	while (isRunning)
	{

		// clear the window to black
		SDL_RenderClear(renderer);
		//main event
		while (SDL_PollEvent(&mainEvent))
		{
			switch (mainEvent.type)
			{
				//User - requested quit
				case SDL_QUIT:
				{
					isRunning = false;
					break;
				}
				default:
				{
					break;
				}
			}
		}

		// copy a portion of the texture to the current rendering target.
		SDL_RenderCopy(renderer, texture, &sourceRect, &desRect);
		//draw to the screen
		SDL_RenderPresent(renderer);


	}
    while (SDL_PollEvent(&mainEvent))
		{
			switch (mainEvent.type)
			{
				//User - requested quit
				case SDL_SCANCODE_DOWN:
				{
					quitSDL(window, renderer);
					break;
				}
				default:
				{
					break;
				}
			}
		}
    run(renderer, s);

    //SDL_RenderSetLogicalSize(renderer, s.w, s.h);
}
///----------------------------------------------
void quitSDL(SDL_Window* window, SDL_Renderer* renderer){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
///-----------------------------------------------

void run(SDL_Renderer *renderer, State &s) {

    bool keep_running = true;
    while (keep_running) {

        double dt =  0.01;///thoi gian di chuyen

        /// lenh dau vao
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                keep_running = false;
            else if (event.type == SDL_KEYDOWN) {
                switch ( event.key.keysym.sym ) {
                case SDLK_ESCAPE:
                    keep_running = false;
                    break;
                }
            }
        }
        const Uint8 *keyboard_state = SDL_GetKeyboardState(NULL);
        /// sang phải
        if (keyboard_state[SDL_SCANCODE_RIGHT]) {
            s.PLAYER.b.x += dt * 200.0;

        }
        /// sang trái
        if (keyboard_state[SDL_SCANCODE_LEFT]) {
            s.PLAYER.b.x -= dt * 200.0;

        }
        /// BẮN
        if (keyboard_state[SDL_SCANCODE_SPACE]) {
            s.bantrung = false;
            s.danban.x = s.PLAYER.b.x;
            s.danban.y = s.PLAYER.b.y - s.PLAYER.b.size;
        }

        /// cập nhật trạng thái
        update_state(s, dt);

        /// vẽ
        render(renderer, s);

        SDL_Delay(2);

    }
}

void init_state(State &s, int stage) {
    s.w = 800;
    s.h = 600;
    s.PLAYER.b.size = 10;
    s.PLAYER.b.x = s.w / 2;
    s.PLAYER.b.y = s.h - 2 * s.PLAYER.b.size;

    s.danban.x = 0;
    s.danban.y = s.h*2;
    s.danban.size = 6;
    s.bantrung = true;

    s.stage = stage;

    /// Enemies
    for (int i = 0; i < s.N; i++) {
        s.quandich[i].song = false;
    }

    int enemy_size = 10;
    int ww = 8; // so quan dich hang ngang
    int hh = 2; // so quan dich hang doc

            int index = 0;
            s.quandich[index].song = true;
            s.quandich[index].chet = false;
            s.quandich[index].b.x =  100;
            s.quandich[index].b.y =  100;

            // varying size
            int size = enemy_size - (rand()%(stage + 1));
            if (size < enemy_size / 2) size = enemy_size / 2;
            s.quandich[index].b.size = size;
            // small shifts


}
/// hàm kiểm tra chạm nhau
bool collide(const Block &b1, const Block &b2) {
    return
        (abs(b1.x - b2.x) < b1.size + b2.size) && (abs(b1.y - b2.y) < b1.size + b2.size);
}

void update_state(State &s, double dt) {
    /// đạn bắn
    if (!s.bantrung) {
        s.danban.y -= 200.0 * dt;
        if (s.danban.y < 0) {
            s.bantrung = true;
            s.danban.y = s.h*2;
        }
    }

    /// di chuyển quân địch - crazy movement
    s.global_time += dt;
    double t = s.global_time;
    double speed = (18.0 + 2.0 * s.stage) * sqrt(t);
    double freq = 6.0 + s.stage/4;
    double z = 2.0 * sin(freq * t) + pow(sin(0.25 * freq * t),19);

    double displace_x = speed * z * dt;
    double displace_y = 0.03 * speed * pow(z,4) * dt;

    bool player_died = false;
    bool enemies_are_dead = true;

    for (int i=0; i < s.N; i++) {
        if (s.quandich[i].song) {

            if (s.quandich[i].chet) {
                /// ban chet quan dich
                s.quandich[i].b.y += 200.0 ;

            }


            /// neu trung dan
            if ( collide (s.quandich[i].b, s.danban) ) {
                if ( !s.quandich[i].chet )
                    s.quandich[i].chet = true;

                s.bantrung = true;
                s.danban.y = s.h*2;//dan bien mat
            }
            enemies_are_dead = false;

        }
    }

    if (player_died) {
        int prev_stage = s.stage-1;
        if (prev_stage < 0) prev_stage = 0;
        init_state(s, prev_stage);
    }

    if (enemies_are_dead) {
        int x = s.PLAYER.b.x;
        init_state(s, s.stage + 1);
        s.PLAYER.b.x = x;
    }
}
/// vẽ , tạo khối
void draw_block(SDL_Renderer *rend, Block &b, int red, int green, int blue, int alpha) {
    int x = static_cast<int>(b.x - b.size);
    int y = static_cast<int>(b.y - b.size);
    SDL_Rect r = {x, y, b.size*2, b.size*2};
    SDL_SetRenderDrawColor(rend, red, green, blue, alpha);
    SDL_RenderFillRect(rend, &r);

}
void render(SDL_Renderer *rend, State &s) {
    SDL_SetRenderDrawColor(rend, 50, 50, 50, 255);
    SDL_RenderClear(rend);///tach dan ban khoi keo dai

    /// Quan dich
    for(int i = 0; i < s.N; i++) {
        if (s.quandich[i].song) {
            if (s.quandich[i].chet)
                draw_block(rend, s.quandich[i].b, 0, 0, 0, 255);
            else
                draw_block(rend, s.quandich[i].b, 0, 255, 0, 0);
        }
    }

    /// Player
    draw_block(rend, s.PLAYER.b, 255, 0, 0, 255);

    /// Bullet
    draw_block(rend, s.danban, 255, 255, 0, 0);

    /// Stage number
    for (int i = 0; i < s.stage+1; i++) {
        SDL_Rect r = {(i+1)*10, 10, 5, 5};
        SDL_SetRenderDrawColor(rend, 240, 170, 0, 200);
        SDL_RenderFillRect(rend, &r);
    }

    // Update the screen
    SDL_RenderPresent(rend);
}
///------------------------------
