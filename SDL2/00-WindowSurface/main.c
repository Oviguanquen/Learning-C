#include <SDL2/SDL.h>

const int WINDOW_WIDTH	= 800;
const int WINDOW_HEIGHT	= 800;

uint8_t f_init(SDL_Window* *mainWindow, SDL_Surface* *mainWindowSurface);

void f_close(SDL_Window* *mainWindow);

int main (void)
{
	SDL_Window*		mainWindow = NULL;
	SDL_Surface*	mainWindowSurface = NULL;
	SDL_Event		eventHandler;

	uint8_t			quit = 1;

	if (f_init(&mainWindow, &mainWindowSurface) == 0)
	{
		printf("[ERROR] f_init\n");
	}
	else if (SDL_FillRect(mainWindowSurface, NULL, SDL_MapRGB(mainWindowSurface->format, 255, 0, 0)) < 0)
	{
		printf("[ERROR] Fill Rect, RGB(255, 0, 0) -> mainWindowSurface.\n%s\n", SDL_GetError());
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

	f_close(&mainWindow);

	return 0;
}

uint8_t f_init(SDL_Window* *mainWindow, SDL_Surface* *mainWindowSurface)
{
	uint8_t flag_success = 1;

	/*	Initialize Video and Events subsystems
	*/
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("[ERROR] Init Video and Events subsystems.\n%s\n", SDL_GetError());
		flag_success = 0;
	}
	else
	{
		*mainWindow = SDL_CreateWindow("My First Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

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

void f_close(SDL_Window* *mainWindow)
{
	SDL_DestroyWindow(*mainWindow);
	*mainWindow = NULL;

	SDL_Quit();
}