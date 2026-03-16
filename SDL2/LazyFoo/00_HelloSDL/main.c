#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(void)
{
	SDL_Window*		window = NULL;
	SDL_Surface*	windowSurface = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		printf("[ERROR]: %s\n", SDL_GetError());

	else
	{
		window = SDL_CreateWindow("My first Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (window == NULL)
			printf("[ERROR]: %s\n", SDL_GetError());

		else
		{
			windowSurface = SDL_GetWindowSurface(window);

			SDL_FillRect(windowSurface, NULL, SDL_MapRGB(windowSurface->format, 0xFF, 0xFF, 0xFF));

			SDL_UpdateWindowSurface(window);

			/*	Prevent window from closing
			*/
			SDL_Event e;
			bool quit = false;
			while (quit == false)
			{
				while (SDL_PollEvent(&e))
				{
					if (e.type == SDL_QUIT)
						quit = true;
				}
			}
		}
	}

	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}