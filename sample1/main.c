#include <stdlib.h>
#include <unistd.h>
#include "../lib/wiztoolkit.h"
#include "SDL/SDL.h"

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define SCREEN_DEPTH 16

#define GP2X_BUTTON_UP              (0)
#define GP2X_BUTTON_DOWN            (4)
#define GP2X_BUTTON_LEFT            (2)
#define GP2X_BUTTON_RIGHT           (6)
#define GP2X_BUTTON_UPLEFT          (1)
#define GP2X_BUTTON_UPRIGHT         (7)
#define GP2X_BUTTON_DOWNLEFT        (3)
#define GP2X_BUTTON_DOWNRIGHT       (5)
#define GP2X_BUTTON_CLICK           (18)
#define GP2X_BUTTON_A               (12)
#define GP2X_BUTTON_B               (13)
#define GP2X_BUTTON_Y               (14)
#define GP2X_BUTTON_X               (15)
#define GP2X_BUTTON_L               (10)
#define GP2X_BUTTON_R               (11)
#define GP2X_BUTTON_MENU            (8)
#define GP2X_BUTTON_SELECT          (9)
#define GP2X_BUTTON_VOLUP           (16)
#define GP2X_BUTTON_VOLDOWN         (17)

SDL_Surface	* screen;

void startSDL(void)
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);
	TTF_Init();
	#ifdef WIZ
	SDL_Joystick *joystick;
	SDL_JoystickEventState(SDL_ENABLE);
	joystick = SDL_JoystickOpen(0);
	#endif
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_DEPTH, SDL_SWSURFACE);
}

void SDLloop(wizToolkitHandler * handler)
{
	SDL_Event event;
	int running = 1;

	while(running)
	{
		// wizToolkit draw function
		wizToolkit_Draw(handler, screen);
		SDL_Flip(screen);
		while(SDL_PollEvent(&event))
		{
			// wizToolkit event handling function
			wizToolkit_Event(handler, event);
			switch(event.type)
			{
				case SDL_QUIT:
					running = 0;
					break;
				#ifdef WIZ
				case SDL_JOYBUTTONDOWN:
					switch( event.jbutton.button )
					{
						case GP2X_BUTTON_MENU:
							running = 0;
							break;
						default:
							break;
					}
				break;
				#endif
			}
		}

	}
}
void exitFromDemo(void)
{

	#ifdef WIZ
		chdir("/usr/gp2x");
		execl("/usr/gp2x/gp2xmenu", "/usr/gp2x/gp2xmenu", NULL);
	#endif
	exit(EXIT_SUCCESS);
}

/*
 * Callback runs on button click
 */
static void helloWorldButtonPressed(wizToolkitHandler * handler, long objectId)
{
	printf("Hello world\n");

	SDL_Quit();
	// cleanup the handler
	wizToolkit_Cleanup(&handler);

	exitFromDemo();
}

int main(int argc, char *argv[])
{
	wizToolkitHandler * handler;	// declare handler

	startSDL();	// normal SDL startup
	#ifdef WIZ
		SDL_ShowCursor(SDL_DISABLE);
	#endif

	// try init handler
	if ( WIZTOOLKIT_OK != wizToolkit_Init(&handler) )
	{
		printf("Error allocating handler\n");
		exitFromDemo();
	} 

	// show handler contents (currently empty)
	#ifdef _DEBUG
	wizToolkit_dump_handler(handler);
	#endif

	// create new button
	long containerId;

	// handler, id returns here, x, y , h , w, label, callbackOnClick
	if ( WIZTOOLKIT_OK == wizToolkit_Add_Button(handler, &containerId, 50, 50, 140, 220, "Hello world!", &helloWorldButtonPressed) )
	{
		printf("Container id : %li\n", containerId);
	}


	#ifdef _DEBUG
	wizToolkit_dump_handler(handler);
	#endif

	SDLloop(handler);

	SDL_Quit();

	// cleanup the handler
	wizToolkit_Cleanup(&handler);

	exitFromDemo();
	return EXIT_SUCCESS;
}

