
int wizToolkit_Add_Image(WIZTOOLKIT_INOUT wizToolkitHandler *handler, WIZTOOLKIT_OUT long * containerId,
				WIZTOOLKIT_IN int x, WIZTOOLKIT_IN int y, WIZTOOLKIT_IN int h, WIZTOOLKIT_IN int w,
				WIZTOOLKIT_IN char * file, WIZTOOLKIT_IN void * onClickCallback)
{
	#ifdef _DEBUG
		printf("wizToolkit_Add_Image(%p, %p, %i, %i, %i, %i, '%s', %p)\n", handler, containerId, x, y, h, w, file, onClickCallback);
	#endif


	wizToolkitObjectImage * newImage = malloc(sizeof(wizToolkitObjectImage));
	if ( NULL == newImage )
	{
		#ifdef _DEBUG
			printf("wizToolkit_Add_Image unable to allocate image %p\n", handler);
		#endif
		return WIZTOOLKIT_ERROR;
	}
	#ifdef _DEBUG
		printf("wizToolkit_Add_Button new image allocated at %p\n", newImage);
	#endif
	char * newFile = NULL;
	if ( NULL != file )
	{
		newFile = malloc(strlen(file)+1);
		if ( NULL == newFile )
		{
			#ifdef _DEBUG
				printf("wizToolkit_Add_Image unable to allocate image filename %p\n", handler);
			#endif
			free(newImage);
			return WIZTOOLKIT_ERROR;
		}
		memcpy(newFile, file, strlen(file)+1);
	}

	newImage->x = x;
	newImage->y = y;
	newImage->h = h;
	newImage->w = w;
	newImage->fileName = newFile;
	newImage->onClick = onClickCallback;

	wizToolkitObjectContainer container;
	container.type = WIZTOOLKIT_IMAGE_CONTAINER;
	container.object = newImage;

	if ( WIZTOOLKIT_OK != wizToolkit_Add_Container(handler, &container, containerId) )
	{
		if ( NULL != newImage->fileName )
		{
			free(newImage->fileName);
		}
		free(newImage);
		return WIZTOOLKIT_ERROR;
	}

	return WIZTOOLKIT_OK;
}

int wizToolkit_Remove_Image(WIZTOOLKIT_INOUT wizToolkitHandler *handler, WIZTOOLKIT_OUT long containerId)
{
	#ifdef _DEBUG
		printf("wizToolkit_Remove_Image(%p, %li)\n", handler, containerId);
	#endif

	if ( NULL == handler )
	{
		#ifdef _DEBUG
			printf("wizToolkit_Remove_Image -> trying to remove image on a invalid hanlder (%p)\n", handler);
		#endif
		return WIZTOOLKIT_ERROR;
	}
	if ( WIZTOOLKIT_MAX_CONTAINERS < containerId )
	{
		#ifdef _DEBUG
			printf("wizToolkit_Remove_Image -> trying to remove image out of bounds (%li) WIZTOOLKIT_MAX_CONTAINERS=%i\n",
										containerId, WIZTOOLKIT_MAX_CONTAINERS);
		#endif
		return WIZTOOLKIT_ERROR;
	}
	if ( WIZTOOLKIT_IMAGE_CONTAINER != handler->containers[containerId].type )
	{
		#ifdef _DEBUG
			printf("wizToolkit_Remove_Image -> type of container mismatch (%d) try to use with wizToolkit_Remove_Container()\n",
											handler->containers[containerId].type);
		#endif
		return WIZTOOLKIT_ERROR;
		
	}
	handler->containers[containerId].type = WIZTOOLKIT_CONTAINER_FREE;

	if ( NULL == handler->containers[containerId].object )
	{
		#ifdef _DEBUG
			printf("wizToolkit_Remove_Image -> trying to remove image already free (%p)\n", handler->containers[containerId].object);
		#endif
		return WIZTOOLKIT_ERROR;
	}
	wizToolkitObjectImage * theImage = (wizToolkitObjectImage *)handler->containers[containerId].object;
	if ( NULL != theImage->fileName )
	{
		free(theImage->fileName);
	}
	//@todo destroy SDL_Surface
	free(theImage);
	handler->containers[containerId].object = NULL;
	return WIZTOOLKIT_OK;
}

