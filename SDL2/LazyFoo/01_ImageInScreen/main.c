#include <SDL2/SDL.h>

uint8_t f_init(SDL_Window** window, SDL_Surface** windowSurface);

uint8_t f_loadMedia(SDL_Surface** imageSurface);

void f_close(SDL_Surface* *imageSurface, SDL_Window* *window);

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

int main (void)
{
	SDL_Window*		window = NULL;
	SDL_Surface*	windowSurface = NULL;
	SDL_Surface*	imageSurface = NULL;

	if (f_init(&window, &windowSurface) == 0)
	{
		printf("[ERROR] Failed to initialize\n");
	}
	else
	{	
		if (f_loadMedia(&imageSurface) == 0)
		{
			printf("[ERROR] Failed to load Media\n");
		}
		else
		{
			SDL_BlitSurface(imageSurface, NULL, windowSurface, NULL);

			SDL_UpdateWindowSurface(window);

			SDL_Event e;
			uint8_t quit = 0;
			while (quit == 0)
			{
				while (SDL_PollEvent(&e))
				{
					if (e.type == SDL_QUIT)
						quit = 1;
				}
			}
		}
	}

	f_close(&imageSurface, &window);

	return 0;
}

uint8_t f_init(SDL_Window* *window, SDL_Surface* *windowSurface)
{
	uint8_t success = 1;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("[ERROR] Init SDL %s\n", SDL_GetError());
		success = 0;
	}
	else
	{
		*window = SDL_CreateWindow("WindowSurface", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (*window == NULL)
		{
			printf("[ERROR] Create window %s\n", SDL_GetError());
			success = 0;
		}
		else
		{
			*windowSurface = SDL_GetWindowSurface(*window);
		}
	}

	return success;
}

uint8_t f_loadMedia(SDL_Surface* *imageSurface)
{
	uint8_t success = 1;

	*imageSurface = SDL_LoadBMP("media/table.bmp");

	if (*imageSurface == NULL)
	{
		printf("[ERROR] Load BMP media/table.bmp %s\n", SDL_GetError());
		success = 0;
	}

	return success;
}

void f_close(SDL_Surface* *imageSurface, SDL_Window* *window)
{
	SDL_FreeSurface(*imageSurface);
	*imageSurface = NULL;

	SDL_DestroyWindow(*window);
	*window = NULL;

	SDL_Quit();
}