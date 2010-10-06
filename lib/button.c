
int wizToolkit_Add_Button(WIZTOOLKIT_INOUT wizToolkitHandler *handler, WIZTOOLKIT_OUT long * containerId,
				WIZTOOLKIT_IN int x, WIZTOOLKIT_IN int y, WIZTOOLKIT_IN int h, WIZTOOLKIT_IN int w,
				WIZTOOLKIT_IN char *label, WIZTOOLKIT_IN void * onClickCallback)
{
	#ifdef _DEBUG
		printf("wizToolkit_Add_Button(%p, %p, %i, %i, %i, %i)\n", handler, containerId, x, y, h, w);
	#endif

	wizToolkitObjectButton * newButton = malloc(sizeof(wizToolkitObjectButton));
	if ( NULL == newButton )
	{
		#ifdef _DEBUG
			printf("wizToolkit_Add_Button unable to allocate button %p\n", handler);
		#endif
		return WIZTOOLKIT_ERROR;
	}
	#ifdef _DEBUG
		printf("wizToolkit_Add_Button new button allocated at %p\n", newButton);
	#endif

	char * newLabel = NULL;
	if ( NULL != label )
	{
		newLabel = malloc(strlen(label)+1);
		if ( NULL == newLabel )
		{
			#ifdef _DEBUG
				printf("wizToolkit_Add_Button unable to allocate button label %p\n", handler);
			#endif
			free(newButton);
			return WIZTOOLKIT_ERROR;
		}
		memcpy(newLabel, label, strlen(label)+1);
	}
	newButton->x = x;
	newButton->y = y;
	newButton->h = h;
	newButton->w = w;
	newButton->label = newLabel;
	newButton->labelSurfaceCache = NULL;
	newButton->onClick = onClickCallback;

	wizToolkitObjectContainer container;
	container.type = WIZTOOLKIT_BUTTON_CONTAINER;
	container.object = newButton;

	if ( WIZTOOLKIT_OK != wizToolkit_Add_Container(handler, &container, containerId) )
	{
		if ( NULL != newButton->label )
		{
			free(newButton->label);
		}
		free(newButton);
		return WIZTOOLKIT_ERROR;
	}
	return WIZTOOLKIT_OK;
}

int wizToolkit_Remove_Button(WIZTOOLKIT_INOUT wizToolkitHandler *handler, WIZTOOLKIT_OUT long containerId)
{
	#ifdef _DEBUG
		printf("wizToolkit_Remove_Button(%p, %li)\n", handler, containerId);
	#endif

	if ( NULL == handler )
	{
		#ifdef _DEBUG
			printf("wizToolkit_Remove_Button -> trying to remove button on a invalid hanlder (%p)\n", handler);
		#endif
		return WIZTOOLKIT_ERROR;
	}
	if ( WIZTOOLKIT_MAX_CONTAINERS < containerId )
	{
		#ifdef _DEBUG
			printf("wizToolkit_Remove_Button -> trying to remove button out of bounds (%li) WIZTOOLKIT_MAX_CONTAINERS=%i\n",
										containerId, WIZTOOLKIT_MAX_CONTAINERS);
		#endif
		return WIZTOOLKIT_ERROR;
	}
	if ( WIZTOOLKIT_BUTTON_CONTAINER != handler->containers[containerId].type )
	{
		#ifdef _DEBUG
			printf("wizToolkit_Remove_Button -> type of container mismatch (%d) try to use with wizToolkit_Remove_Container()\n",
											handler->containers[containerId].type);
		#endif
		return WIZTOOLKIT_ERROR;
		
	}
	handler->containers[containerId].type = WIZTOOLKIT_CONTAINER_FREE;

	if ( NULL == handler->containers[containerId].object )
	{
		#ifdef _DEBUG
			printf("wizToolkit_Remove_Button -> trying to remove button already free (%p)\n", handler->containers[containerId].object);
		#endif
		return WIZTOOLKIT_ERROR;
	}
	wizToolkitObjectButton * theButton = (wizToolkitObjectButton *)handler->containers[containerId].object;
	if ( NULL != theButton->label )
	{
		free(theButton->label);
	}
	free(theButton);
	handler->containers[containerId].object = NULL;
	return WIZTOOLKIT_OK;
}


