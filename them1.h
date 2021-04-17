#include <SDL_ttf.h>
#include <iostream>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include<windows.h>

void drawSquare(double x, double y, double size, SDL_Renderer* renderer);
void draw(int n, double x, double y, double size, SDL_Renderer* renderer);
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer,int screenWidth, int screenHeight, const char* windowTitle);
void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void waitUntilKeyPressed();
