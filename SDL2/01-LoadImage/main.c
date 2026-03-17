#include <SDL2/SDL.h>

const int WINDOW_WIDTH	= 800;
const int WINDOW_HEIGHT	= 800;

uint8_t f_init(SDL_Window* *mainWindow, SDL_Surface* *mainWindowSurface);

uint8_t f_loadImage(SDL_Surface* *imageSurface, char* imagePath);

void f_close(SDL_Window* *mainWindow, SDL_Surface* *imageSurface);

int main (void)
{
	SDL_Window*		mainWindow = NULL;
	SDL_Surface*	mainWindowSurface = NULL;

	SDL_Surface*	imageSurface = NULL;

	SDL_Event		eventHandler;

	uint8_t			quit = 1;

	if (f_init(&mainWindow, &mainWindowSurface) == 0)
	{
		printf("[ERROR] f_init\n");
	}
	else if (f_loadImage(&imageSurface, "media/table.bmp") == 0)
	{
		printf("[ERROR] f_loadImage");
	}
	else if (SDL_BlitSurface(imageSurface, NULL, mainWindowSurface, NULL) < 0)
	{
		printf("[ERROR] Blit Surface, imageSurface -> mainWindowSurface.\n%s\n", SDL_GetError());
	}
	else if (SDL_UpdateWindowSurface(mainWindow) < 0)
	{
		printf("[ERROR] Update Window Surface, main Window.\n%s\n", SDL_GetError());
	}
	else
	{
		while (quit == 1)
		{
			while (SDL_PollEvent(&eventHandler))
			{
				if (eventHandler.type == SDL_QUIT)
				{
					quit = 0;
				}
			}
		}
	}

	f_close(&mainWindow, &imageSurface);

	return 0;
}

uint8_t f_init(SDL_Window* *mainWindow, SDL_Surface* *mainWindowSurface)
{
	uint8_t flag_success = 1;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("[ERROR] Init Video and Events subsystems.\n%s\n", SDL_GetError());
		flag_success = 0;
	}
	else
	{
		*mainWindow = SDL_CreateWindow("Load Image", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

		if (*mainWindow == NULL)
		{
			printf("[ERROR] Create main Window.\n%s\n", SDL_GetError());
			flag_success = 0;
		}
		else
		{
			*mainWindowSurface = SDL_GetWindowSurface(*mainWindow);
			
			if (*mainWindowSurface == NULL)
			{
				printf("[ERROR] Get main Window Surface.\n%s\n", SDL_GetError());
				flag_success = 0;
			}
		}
	}

	return flag_success;
}

uint8_t f_loadImage(SDL_Surface* *imageSurface, char* imagePath)
{
	uint8_t flag_success = 1;

	*imageSurface = SDL_LoadBMP(imagePath);

	if (*imageSurface == NULL)
	{
		printf("[ERROR] Load BMP for image Surface.\n%s\n", SDL_GetError());
		flag_success = 0;
	}

	return flag_success;
}

void f_close(SDL_Window* *mainWindow, SDL_Surface* *imageSurface)
{
	SDL_FreeSurface(*imageSurface);
	*imageSurface = NULL;

	SDL_DestroyWindow(*mainWindow);
	*mainWindow = NULL;

	SDL_Quit();
}