#ifdef _DEBUG
void wizToolkit_dump_Button(WIZTOOLKIT_IN wizToolkitHandler *handler, long id)
{
	wizToolkitObjectButton *button = (wizToolkitObjectButton *)handler->containers[id].object;
	printf("\t\tX: %i\n", button->x);
	printf("\t\tY: %i\n", button->y);
	printf("\t\tH: %i\n", button->h);
	printf("\t\tW: %i\n", button->w);
	printf("\t\tlabel: %s\n", button->label);
}

void wizToolkit_dump_handler(WIZTOOLKIT_IN wizToolkitHandler *handler)
{
	long counter;

	printf("wizToolkit_dump_handler(%p)\n", handler);

	for (counter = 0; counter < WIZTOOLKIT_MAX_CONTAINERS;counter++)
	{
		if ( WIZTOOLKIT_CONTAINER_FREE != handler->containers[counter].type)
		{
			printf("Container number: %lu\n", counter);
			printf("\tPoints to: %p\n", handler->containers[counter].object);
			printf("\tType: ");
			switch (handler->containers[counter].type)
			{
				case WIZTOOLKIT_EMPTY_CONTAINER:
					printf("WIZTOOLKIT_EMPTY_CONTAINER\n");
				break;
				case WIZTOOLKIT_BUTTON_CONTAINER:
					printf("WIZTOOLKIT_BUTTON_CONTAINER\n");
					wizToolkit_dump_Button(handler, counter);
				break;
			}
		}
	}
	printf("wizToolkit_dump_handler ends here\n");

}
#endif
