int wizToolkit_Draw_Button(WIZTOOLKIT_IN wizToolkitHandler *handler, WIZTOOLKIT_IN SDL_Surface * surface, WIZTOOLKIT_IN long containerId)
{
	#ifdef _DEBUG2
		printf("wizToolkit_Draw_Button(%p, %p, %li)\n", handler, surface, containerId);
	#endif
	wizToolkitObjectButton * theButton = (wizToolkitObjectButton *)handler->containers[containerId].object;
	#ifdef _DEBUG2
		printf("wizToolkit_Draw_Button -> the Button %p\n", theButton);
	#endif
	if ( NULL == theButton->labelSurfaceCache )
	{
		if ( NULL != theButton->label )
		{
			if (NULL != handler->buttonFont)
			{
				#ifdef _DEBUG
					printf("wizToolkit_Draw_Button -> Rendering font with font %p and text '%s'\n",
												handler->buttonFont, theButton->label);
				#endif

				SDL_Color fontColor;
				fontColor.r = 255;
				fontColor.g = 255;
				fontColor.b = 255;
				theButton->labelSurfaceCache = TTF_RenderText_Solid(handler->buttonFont, theButton->label, fontColor);

				#ifdef _DEBUG
					printf("wizToolkit_Draw_Button -> Font surface %p\n", theButton->labelSurfaceCache);
				#endif
				
			}
		}
	}
	if ( NULL == theButton->labelSurfaceCache )
	{
		#ifdef _DEBUG
			printf("wizToolkit_Draw_Button -> Unable to render correctly button %li of handler %p\n", containerId, handler);
		#endif
		return WIZTOOLKIT_ERROR;
	}
	#ifdef _DEBUG2
		printf("wizToolkit_Draw_Button -> label surface cache %p\n", theButton->labelSurfaceCache);
	#endif


	// draw button
	SDL_Rect buttonRect;
	buttonRect.x = theButton->x;
	buttonRect.y = theButton->y;
	buttonRect.h = theButton->h;
	buttonRect.w = theButton->w;
	SDL_FillRect(surface, &buttonRect, 0xffffff);

	buttonRect.x = theButton->x+1;
	buttonRect.y = theButton->y+1;
	buttonRect.h = theButton->h-2;
	buttonRect.w = theButton->w-2;
	SDL_FillRect(surface, &buttonRect, 0x0);

	// draw text
	SDL_Rect objectRect;
	objectRect.x = theButton->x + (theButton->w /2) - (theButton->labelSurfaceCache->w / 2); 
	objectRect.y = theButton->y + (theButton->h /2) - (theButton->labelSurfaceCache->h / 2); 

	SDL_BlitSurface(theButton->labelSurfaceCache, NULL, surface, &objectRect);

	return WIZTOOLKIT_OK;
}

int wizToolkit_Draw(WIZTOOLKIT_IN wizToolkitHandler *handler, WIZTOOLKIT_IN SDL_Surface * surface)
{
	long counter;
	#ifdef _DEBUG2
		printf("wizToolkit_Draw(%p, %p)\n", handler, surface);
	#endif

	for (counter = 0; counter < WIZTOOLKIT_MAX_CONTAINERS; counter++)
	{
		if ( WIZTOOLKIT_CONTAINER_FREE != handler->containers[counter].type)
		{
			switch (handler->containers[counter].type)
			{
				case WIZTOOLKIT_BUTTON_CONTAINER:
					wizToolkit_Draw_Button(handler, surface, counter);
				break;
				case WIZTOOLKIT_IMAGE_CONTAINER:
					//@todo wizToolkit_Draw_Image(handler, surface, counter);
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

