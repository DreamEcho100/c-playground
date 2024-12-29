#include <stdio.h>

#include "./index.h"
#include "../stack/index.h"
#include "../snekobject/index.h"

void vm_track_object(vm_t *vm, snek_object_t *obj)
{
	stack_push(vm->objects, obj);
}

void vm_frame_push(vm_t *vm, frame_t *frame)
{
	if (vm == NULL)
	{
		fprintf(stderr, "Error: `vm` is NULL.\n");
		exit(EXIT_FAILURE); // Gracefully terminate the program
	}
	if (frame == NULL)
	{
		fprintf(stderr, "Error: `frame` is NULL.\n");
		exit(EXIT_FAILURE); // Gracefully terminate the program
	}

	stack_push(vm->frames, frame);
}

frame_t *vm_new_frame(vm_t *vm)
{
	if (vm == NULL)
	{
		fprintf(stderr, "Error: `vm` is NULL.\n");
		exit(EXIT_FAILURE); // Gracefully terminate the program
	}

	frame_t *frame = (frame_t *)malloc(sizeof(frame_t));
	if (frame == NULL)
	{
		fprintf(stderr, "Error: Couldn't allocate `frame`.\n");
		exit(EXIT_FAILURE); // Gracefully terminate the program
	}
	frame->references = stack_new(8);

	stack_push(vm->frames, frame);

	return frame;
}

void frame_free(frame_t *frame)
{
	if (frame == NULL)
	{
		fprintf(stderr, "Error: `frame` is NULL.\n");
		exit(EXIT_FAILURE); // Gracefully terminate the program
	}

	for (size_t i = 0; i < frame->references->count; ++i)
	{
		free(frame->references->data[i]);
	}
	stack_free(frame->references);
	free(frame);
}

vm_t *vm_new()
{
	vm_t *vm = (vm_t *)malloc(sizeof(vm_t));

	if (vm == NULL)
	{
		fprintf(stderr, "Error: Couldn't allocate `vm`.\n");
		exit(EXIT_FAILURE); // Gracefully terminate the program
	}

	vm->frames = stack_new(0);

	if (vm->frames == NULL)
	{
		fprintf(stderr, "Error: Couldn't allocate `vm->frames`.\n");
		exit(EXIT_FAILURE); // Gracefully terminate the program
	}

	vm->objects = stack_new(0);

	if (vm->objects == NULL)
	{
		fprintf(stderr, "Error: Couldn't allocate `vm->objects`.\n");
		exit(EXIT_FAILURE); // Gracefully terminate the program
	}

	return vm;
}

void vm_free(vm_t *vm)
{
	if (vm == NULL)
		return;

	if (vm->frames != NULL)
	{
		for (size_t i = 0; i < vm->frames->count; ++i)
		{
			frame_free(vm->frames->data[i]);
		}

		free(vm->frames);
	}
	if (vm->objects != NULL)
		free(vm->objects);

	free(vm);
}
