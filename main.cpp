#include "ingame.h"
#include "them1.h"

int main(int argc, char* args[]) {



	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Surface* tempSurface = NULL;
	SDL_Texture* texture = NULL;
	SDL_Event mainEvent;
	SDL_Rect sourceRect;
	SDL_Rect desRect;


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
	window = SDL_CreateWindow("HUY hai huoc ", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,1300, 750, SDL_WINDOW_SHOWN);
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

	//set background color
	//SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	int coloring = 0;

	//main loop
	isRunning = true;
	while (isRunning)
	{
		// clear the window to black
		//SDL_RenderClear(renderer);
		//main event
		while (SDL_PollEvent(&mainEvent))
		{
			switch (mainEvent.type)
			{
				//User - requested quit
				case SDL_KEYDOWN:

                    if (mainEvent.key.keysym.sym == SDLK_r){
                        //create a tempSurface
                        tempSurface = SDL_LoadBMP("blue_player2.bmp");
                        coloring = 0;
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
                    if (mainEvent.key.keysym.sym == SDLK_RIGHT){
                        //create a tempSurface
                        tempSurface = SDL_LoadBMP("pink_player2.bmp");

                        coloring = 1;

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
                    if (mainEvent.key.keysym.sym == SDLK_LEFT){
                        //create a tempSurface
                        tempSurface = SDL_LoadBMP("blue_player2.bmp");
                        coloring = 0;
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
                    if (mainEvent.key.keysym.sym == SDLK_f){
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
	/*tempSurface = SDL_LoadBMP("1111.bmp");
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
    SDL_Delay(900);
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
    SDL_Delay(900);
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
    SDL_Delay(900);
    tempSurface = SDL_LoadBMP("4444.bmp");
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
    SDL_Delay(900);
    tempSurface = SDL_LoadBMP("5555.bmp");
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
    SDL_Delay(900);
    tempSurface = SDL_LoadBMP("6666.bmp");
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
    SDL_Delay(900);*/
	//set background color
	//SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    //SDL_RenderClear(renderer);///tach dan ban khoi keo dai


    run(renderer, s,coloring);


}
///---------------------------------------------

