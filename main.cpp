#include "ingame.h"
#include "them1.h"
#include <time.h>

int main(int argc, char* args[]) {

    /// RANDOM 6 VIEN DA VO CUC
    srand(time(0));
    std::string random = "0123456789",anhthu[12];
    int nhanvat[12];
    int dem = 0 ,check = 0;
    while(dem < 6){
        int i = rand() % random.length();
        nhanvat[dem] = int(random[i]) - 48;
        random.erase(i,1);
        ++dem;
    }

    ///INIT

	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Surface* tempSurface = NULL;
	SDL_Texture* texture = NULL;
	SDL_Event mainEvent;
	SDL_Rect sourceRect;
	SDL_Rect desRect;
    TTF_Font* font = NULL;

    State s;
    init_state(s, 0);

	bool isRunning = true;
	//initializes  the subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("Unable to initialize SDL %s\n", SDL_GetError());
		return -1;
	}
	//Create window
	window = SDL_CreateWindow("HUY hai huoc ", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,1320, 720, SDL_WINDOW_SHOWN);
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
	tempSurface = SDL_LoadBMP("menuchatluong.bmp");
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

	///======================================================================VAO MENU
	isRunning = true;
	while (isRunning)
	{

		//main event
		while (SDL_PollEvent(&mainEvent))
		{
			switch (mainEvent.type)
			{
				//User - requested quit
				case SDL_KEYDOWN:
				    if (mainEvent.key.keysym.sym == SDLK_i){
                            tempSurface = SDL_LoadBMP("instruction.bmp");
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
				    }
				    if (mainEvent.key.keysym.sym == SDLK_BACKSPACE){
                            tempSurface = SDL_LoadBMP("menuchatluong.bmp");
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
				    }
                    if (mainEvent.key.keysym.sym == SDLK_s){
                                isRunning = false;
                                break;
                    }
                    default:
                    {
                        break;
                    }
                }

		// copy a portion of the texture to the current rendering target.
		SDL_RenderCopy(renderer, texture, &sourceRect, &desRect);
		//draw to the screen
		SDL_RenderPresent(renderer);
        }
	}
	///-------------------------------------------------------------------
	///LOADING 1 CHUT for fun
	tempSurface = SDL_LoadBMP("1111.bmp");
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
    SDL_RenderCopy(renderer, texture, &sourceRect, &desRect);
		//draw to the screen
    SDL_RenderPresent(renderer);
    SDL_Delay(500);
    tempSurface = SDL_LoadBMP("2222.bmp");
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
    SDL_RenderCopy(renderer, texture, &sourceRect, &desRect);
		//draw to the screen
    SDL_RenderPresent(renderer);
    SDL_Delay(500);
    tempSurface = SDL_LoadBMP("3333.bmp");
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
    SDL_RenderCopy(renderer, texture, &sourceRect, &desRect);
		//draw to the screen
    SDL_RenderPresent(renderer);
    SDL_Delay(500);
    /// GAME START
    run(window,renderer,s
        ,nhanvat[0],nhanvat[1],nhanvat[2],nhanvat[3],nhanvat[4],nhanvat[5]);

    ///END

    if(s.quandich[nhanvat[0]].chet&&s.quandich[nhanvat[1]].chet&&
       s.quandich[nhanvat[2]].chet&&s.quandich[nhanvat[3]].chet&&s.quandich[nhanvat[4]].chet&&s.quandich[nhanvat[5]].chet){
        SDL_Surface * image_thanos = SDL_LoadBMP("thanos_win.bmp");
        SDL_Texture* texture_thanos = SDL_CreateTextureFromSurface(renderer, image_thanos);
        SDL_RenderCopy(renderer, texture_thanos, NULL, NULL);
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
        SDL_Delay(5000);
        quitSDL(window,renderer);
    }

        SDL_Surface * image_thanos2 = SDL_LoadBMP("thanos_death.bmp");
        SDL_Texture* texture_thanos2 = SDL_CreateTextureFromSurface(renderer, image_thanos2);
        SDL_RenderCopy(renderer, texture_thanos2, NULL, NULL);
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
        SDL_Delay(5000);
        quitSDL(window,renderer);

}
///---------------------------------------------

