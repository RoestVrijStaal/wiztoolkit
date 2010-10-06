#include "wiztoolkit.h"
// nasty I know!
#include "debug.c"
#include "containers.c"
#include "button.c"
#include "image.c"
#include "checkbox.c"
#include "draw.c"
#include "events.c"

/*
 * Initialize a handler
 */
int wizToolkit_Init(WIZTOOLKIT_INOUT wizToolkitHandler **handler)
{
	#ifdef _DEBUG
		printf("wizToolkit_Init(%p)\n", *handler);
	#endif
	// grab space from heap
	*handler = malloc(sizeof(wizToolkitHandler));
	// something wrong?
	if ( NULL == *handler )
	{
		#ifdef _DEBUG
			printf("wizToolkit_Init unable to allocate handler %p\n", *handler);
		#endif
		return WIZTOOLKIT_ERROR;
	}
	#ifdef _DEBUG
		printf("wizToolkit_Init handler now points to %p\n", *handler);
	#endif
	// clean memory
	memset(*handler, 0x0, sizeof(wizToolkitHandler));

	// load font for buttons
	wizToolkitHandler *newHandler = *handler;
	newHandler->buttonFont = TTF_OpenFont("ttf/VeraMoBd.ttf", 12);
	if ( NULL == newHandler->buttonFont )
	{
		#ifdef _DEBUG
			printf("wizToolkit_Init unable to load truetype fonts\n");
		#endif
		return WIZTOOLKIT_ERROR;
	}
	return WIZTOOLKIT_OK;
}

/*
 * Destroy a handler
 */
void wizToolkit_Cleanup(WIZTOOLKIT_INOUT wizToolkitHandler **handler)
{
	#ifdef _DEBUG
		printf("wizToolkit_Cleanup(%p)\n", *handler);
	#endif
	if ( NULL == *handler)
	{
		#ifdef _DEBUG
			printf("wizToolkit_Cleanup Warning, this handler already free\n");
		#endif
		return;
	}
	wizToolkitHandler *newHandler = *handler;
	free(newHandler->buttonFont);

	//@todo free all containers

	free(*handler);
	*handler = 0x0;
}

