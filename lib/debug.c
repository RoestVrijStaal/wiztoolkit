#ifdef _DEBUG
void wizToolkit_dump_Button(WIZTOOLKIT_IN wizToolkitHandler *handler, long id)
{
	wizToolkitObjectButton *button = (wizToolkitObjectButton *)handler->containers[id].object;
	printf("\t\tX: %i\n", button->x);
	printf("\t\tY: %i\n", button->y);
	printf("\t\tH: %i\n", button->h);
	printf("\t\tW: %i\n", button->w);
	printf("\t\tLabel: '%s'\n", button->label);
	printf("\t\tLabel SDL Surface: %p\n", button->labelSurfaceCache);
	printf("\t\tOnClick callback: %p\n", button->onClick);
}

void wizToolkit_dump_Image(WIZTOOLKIT_IN wizToolkitHandler *handler, long id)
{
	wizToolkitObjectImage *image = (wizToolkitObjectImage *)handler->containers[id].object;
	printf("\t\tX: %i\n", image->x);
	printf("\t\tY: %i\n", image->y);
	printf("\t\tH: %i\n", image->h);
	printf("\t\tW: %i\n", image->w);
	printf("\t\tFileName: '%s'\n", image->fileName);
	printf("\t\tImage SDL Surface: %p\n", image->image);
	printf("\t\tOnClick callback: %p\n", image->onClick);
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
				case WIZTOOLKIT_IMAGE_CONTAINER:
					printf("WIZTOOLKIT_IMAGE_CONTAINER\n");
					wizToolkit_dump_Image(handler, counter);
				break;
			}
		}
	}
	printf("wizToolkit_dump_handler ends here\n");

}
#endif
