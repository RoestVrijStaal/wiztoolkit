/*
 * Add container to existing handler
 */
int wizToolkit_Add_Container(WIZTOOLKIT_INOUT wizToolkitHandler *handler, WIZTOOLKIT_IN wizToolkitObjectContainer *container,
								WIZTOOLKIT_OUT long * containerId)
{
	long counter;
	unsigned char foundHole = 0;
	#ifdef _DEBUG
		printf("wizToolkit_Add_Container(%p, %p, %p)\n", handler, container, containerId);
	#endif

	if ( NULL == handler )
	{
		#ifdef _DEBUG
			printf("wizToolkit_Add_Container -> trying to allocate new container on a invalid hanlder (%p)\n", handler);
		#endif
		return WIZTOOLKIT_ERROR;
	}
	
	// find empty container

	for (counter = 0; counter < WIZTOOLKIT_MAX_CONTAINERS;counter++)
	{
		if ( WIZTOOLKIT_CONTAINER_FREE == handler->containers[counter].type)
		{
			#ifdef _DEBUG
				printf("wizToolkit_Add_Container -> free container found at  %lu\n", counter);
			#endif
			foundHole = 1;
			break;
		}
	}
	// we found a hole?
	if ( foundHole == 0)
	{
		#ifdef _DEBUG
			printf("wizToolkit_Add_Container -> handler full (%p)\n", handler);
		#endif
		return WIZTOOLKIT_ERROR;
	}

	*containerId = counter;
	handler->containers[counter].type = container->type;
	handler->containers[counter].object = container->object;
	return WIZTOOLKIT_OK;
}

/*
 * Remove container from existing handler
 */
int wizToolkit_Remove_Container(WIZTOOLKIT_INOUT wizToolkitHandler *handler, WIZTOOLKIT_IN long containerId)
{
	#ifdef _DEBUG
		printf("wizToolkit_Remove_Container(%p, %li)\n", handler, containerId);
	#endif

	if ( NULL == handler )
	{
		#ifdef _DEBUG
			printf("wizToolkit_Remove_Container -> trying to remove container on a invalid hanlder (%p)\n", handler);
		#endif
		return WIZTOOLKIT_ERROR;
	}
	if ( WIZTOOLKIT_MAX_CONTAINERS < containerId )
	{
		#ifdef _DEBUG
			printf("wizToolkit_Remove_Container -> trying to remove container out of bounds (%li) WIZTOOLKIT_MAX_CONTAINERS=%i\n",
										containerId, WIZTOOLKIT_MAX_CONTAINERS);
		#endif
		return WIZTOOLKIT_ERROR;
	}
	// note: free don't need this, but...
	if ( NULL != handler->containers[containerId].object )
	{
		free(handler->containers[containerId].object);
		handler->containers[containerId].object = NULL;
	}
	handler->containers[containerId].type = WIZTOOLKIT_CONTAINER_FREE;
	return WIZTOOLKIT_OK;
}

