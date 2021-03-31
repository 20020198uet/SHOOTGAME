#include "ingame.h"

//SDL_Texture* loadTexture(const string &file, SDL_Renderer *ren);

///----------------------------------
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
	window = SDL_CreateWindow("HUY hai huoc ", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,870, 610, SDL_WINDOW_SHOWN);
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

	int coloring = 0;

	//main loop
	isRunning = true;
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
				case SDL_KEYDOWN:
                {
                    if (mainEvent.key.keysym.sym == SDLK_r){
                        //create a tempSurface
                        tempSurface = SDL_LoadBMP("blue_player.bmp");
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

                        coloring = 0;

                    }
                    if (mainEvent.key.keysym.sym == SDLK_RIGHT){
                        //create a tempSurface
                        tempSurface = SDL_LoadBMP("pink_player.bmp");

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
                        tempSurface = SDL_LoadBMP("blue_player.bmp");
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
                }
                if (mainEvent.key.keysym.sym == SDLK_g){
                            isRunning = false;
                            break;
                }
				default:
				{
					break;
				}
			}
		}
//        while()
		// copy a portion of the texture to the current rendering target.
		SDL_RenderCopy(renderer, texture, &sourceRect, &desRect);
		//draw to the screen
		SDL_RenderPresent(renderer);
        }

        run(renderer, s,coloring);


}
//---------------------------------------------

