#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>

#define WIZTOOLKIT_IN
#define WIZTOOLKIT_OUT
#define WIZTOOLKIT_INOUT


#define WIZTOOLKIT_OK			0
#define WIZTOOLKIT_ERROR		-1
#define WIZTOOLKIT_MEMORY_ERROR		-2

// modify as you like
#define WIZTOOLKIT_MAX_CONTAINERS	256

#define WIZTOOLKIT_CONTAINER_FREE	0
#define WIZTOOLKIT_EMPTY_CONTAINER	1
#define WIZTOOLKIT_BUTTON_CONTAINER	2
#define WIZTOOLKIT_IMAGE_CONTAINER	3
#define WIZTOOLKIT_CHECKBOX_CONTAINER	4

// data structures
typedef struct wizToolkitObjectContainer_s
{
	int type;
	void * object;
} wizToolkitObjectContainer;

typedef struct wizToolkitHandler_s
{
	TTF_Font * buttonFont;
	wizToolkitObjectContainer containers[WIZTOOLKIT_MAX_CONTAINERS];
} wizToolkitHandler;

typedef void (*wizToolKit_onClick)(wizToolkitHandler *, long);

// button type object
typedef struct wizToolkitObjectButton_s
{
	int x;
	int y;
	int h;
	int w;
	char * label;
	SDL_Surface * labelSurfaceCache;
	void * onClick;
} wizToolkitObjectButton;

// image type object
typedef struct wizToolkitObjectImage_s
{
	int x;
	int y;
	int h;
	int w;
	char * fileName;
	SDL_Surface * image;
	void * onClick;
} wizToolkitObjectImage;

// checkbox type object
typedef struct wizToolkitObjectCheckbox_s
{
	int x;
	int y;
	int h;
	int w;
	int checked;
	char * label;
	SDL_Surface * labelSurfaceCache;
	void * onClick;
} wizToolkitObjectCheckbox;

// initialization
int wizToolkit_Init(WIZTOOLKIT_INOUT wizToolkitHandler **handler);
void wizToolkit_Cleanup(WIZTOOLKIT_INOUT  wizToolkitHandler **handler);

// object creation
/// buttons
int wizToolkit_Add_Button(WIZTOOLKIT_INOUT wizToolkitHandler *handler, WIZTOOLKIT_OUT long * containerId,
				WIZTOOLKIT_IN int x, WIZTOOLKIT_IN int y, WIZTOOLKIT_IN int h, WIZTOOLKIT_IN int w,
				WIZTOOLKIT_IN char *label, WIZTOOLKIT_IN void * onClickCallback);
int wizToolkit_Remove_Button(WIZTOOLKIT_INOUT wizToolkitHandler *handler, WIZTOOLKIT_OUT long containerId);
/// images
int wizToolkit_Add_Image(WIZTOOLKIT_INOUT wizToolkitHandler *handler, WIZTOOLKIT_OUT long * containerId,
				WIZTOOLKIT_IN int x, WIZTOOLKIT_IN int y, WIZTOOLKIT_IN int h, WIZTOOLKIT_IN int w,
				WIZTOOLKIT_IN char * file, WIZTOOLKIT_IN void * onClickCallback);
int wizToolkit_Remove_Image(WIZTOOLKIT_INOUT wizToolkitHandler *handler, WIZTOOLKIT_OUT long containerId);
// object draw to SDL
int wizToolkit_Draw(WIZTOOLKIT_IN wizToolkitHandler *handler, SDL_Surface * surface);

// object events from SDL
int wizToolkit_Event(WIZTOOLKIT_IN wizToolkitHandler *handler, WIZTOOLKIT_IN SDL_Event event);

// container handling (low level)
int wizToolkit_Add_Container(WIZTOOLKIT_INOUT wizToolkitHandler *handler, WIZTOOLKIT_IN wizToolkitObjectContainer *container,
					WIZTOOLKIT_OUT long * containerId);
int wizToolkit_Remove_Container(WIZTOOLKIT_INOUT wizToolkitHandler *handler, WIZTOOLKIT_IN long containerId);

// debug (invalid in release)
#ifdef _DEBUG
void wizToolkit_dump_handler(WIZTOOLKIT_IN wizToolkitHandler *handler);
#endif
