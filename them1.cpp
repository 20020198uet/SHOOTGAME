#include "them1.h"
#include <time.h>
void draw(int n, double x, double y, double size, SDL_Renderer* renderer) {
    if (n == 0) return;

    drawSquare(x, y, size, renderer);


    double ratio = 2.2;

    // recursively draw 4 smaller trees of order n-1
    draw(n-1, x - size/2, y - size/2, size/ratio, renderer); // lower left

    draw(n-1, x - size/2, y + size/2, size/ratio, renderer);    // upper left

    draw(n-1, x + size/2, y - size/2, size/ratio, renderer);    // lower right

    draw(n-1, x + size/2, y + size/2, size/ratio, renderer);    // upper right

}
///------------
void drawSquare(double x, double y, double size, SDL_Renderer* renderer) {
	SDL_Rect rect;
    rect.x = x - size/2;
    rect.y = y - size/2;
    rect.w = size;
    rect.h = size;


	SDL_SetRenderDrawColor(renderer, 60, 200, 200, 0);
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderDrawRect(renderer, &rect);
    srand(time(NULL));
    SDL_RenderPresent(renderer);
}
///----------------
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer,
        int screenWidth, int screenHeight, const char* windowTitle)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout, "SDL_Init", true);

    window = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_CENTERED,
       SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
    //window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
    //   SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);

    //Khi thông thường chạy với môi trường bình thường ở nhà
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);
    //Khi chạy ở máy thực hành WinXP ở trường (máy ảo)
    //renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));
    if (renderer == nullptr) logSDLError(std::cout, "CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, screenWidth, screenHeight);
}
///--------------------
void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}


void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_WaitEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}
