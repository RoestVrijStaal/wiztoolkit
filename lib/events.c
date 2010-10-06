int wizToolkitInRect(int px, int py, int x, int y, int h, int w)
{
	if (( x < px ) && ( y < py ))
	{
		if (((y + h) > py ) && ((x + w)  > px ))
		{
			return WIZTOOLKIT_OK;
		}
	}
	return WIZTOOLKIT_ERROR;
}
 
int wizToolkit_Event_Button(WIZTOOLKIT_IN wizToolkitHandler *handler, WIZTOOLKIT_IN SDL_Event event, long containerId)
{
	wizToolkitObjectButton * theButton = (wizToolkitObjectButton *)handler->containers[containerId].object;
	// @todo cast type of event and call the callbacks
	switch(event.type)
	{
		case SDL_MOUSEMOTION:
			break;
		case SDL_MOUSEBUTTONDOWN:
			break;
		case SDL_MOUSEBUTTONUP:
			if ( NULL != theButton->onClick )
			{
				if ( WIZTOOLKIT_OK == wizToolkitInRect(event.motion.x, event.motion.y, theButton->x, theButton->y,
											theButton->h, theButton->w))
				{
					wizToolKit_onClick doClick;
					doClick = (wizToolKit_onClick)theButton->onClick;
					doClick(handler, containerId);
				}
			}
			break;
	}
	return WIZTOOLKIT_OK;
}

int wizToolkit_Event(WIZTOOLKIT_IN wizToolkitHandler *handler, WIZTOOLKIT_IN SDL_Event event)
{
	long counter;
	#ifdef _DEBUG2
		printf("wizToolkit_Event(%p, %p)\n", handler, &event);
	#endif

	for (counter = 0; counter < WIZTOOLKIT_MAX_CONTAINERS; counter++)
	{
		if ( WIZTOOLKIT_CONTAINER_FREE != handler->containers[counter].type)
		{
			switch (handler->containers[counter].type)
			{
				case WIZTOOLKIT_BUTTON_CONTAINER:
					wizToolkit_Event_Button(handler, event, counter);
				break;
				#ifdef _DEBUG
				default:
					printf("Unknown object %i %li in handler %p\n", handler->containers[counter].type, counter, handler);
				#endif
			}

		}
	}
	return WIZTOOLKIT_OK;
}

