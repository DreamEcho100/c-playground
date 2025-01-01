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

void frame_free(frame_t *frame)
{
	// if (frame == NULL)
	// {
	// 	fprintf(stderr, "Error: `frame` is NULL.\n");
	// 	exit(EXIT_FAILURE); // Gracefully terminate the program
	// }

	// for (size_t i = 0; i < frame->references->count; ++i)
	// {
	// 	free(frame->references->data[i]);
	// }
	// stack_free(frame->references);
	// free(frame);

	stack_free(frame->references);
	free(frame);
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

		stack_free(vm->frames);
	}
	if (vm->objects != NULL)
	{
		for (size_t i = 0; i < vm->objects->count; ++i)
		{
			snek_object_free(vm->objects->data[i]);
		}

		stack_free(vm->objects);
	}

	free(vm);
}

void frame_reference_object(frame_t *frame, snek_object_t *obj)
{
	if (frame == NULL)
	{
		fprintf(stderr, "Error: `frame` is NULL.\n");
		exit(EXIT_FAILURE);
	}

	stack_push(frame->references, obj);
}

void mark(vm_t *vm)
{
	if (vm == NULL)
		// Should exit
		return;

	for (size_t i = 0; i < vm->frames->count; ++i)
	{
		frame_t *frame = vm->frames->data[i];

		for (size_t j = 0; j < frame->references->count; ++j)
		{
			snek_object_t *obj = frame->references->data[j];
			obj->is_marked = true;
		}
	}
}

void trace(vm_t *vm)
{
	// Create a new stack (stack_new) with a capacity of 8 called gray_objects. If the allocation fails, return.
	stack_t *gray_objects = stack_new(8);
	if (gray_objects == NULL)
	{
		// Should exit
		return;
	}

	// Iterate over each of the objects in the VM:
	for (size_t i = 0; i < vm->objects->count; i++)
	{
		snek_object_t *obj = vm->objects->data[i];
		// If the object is marked, push it onto the gray_objects stack.
		if (obj->is_marked)
		{
			stack_push(gray_objects, obj);
		}
	}

	// While the gray_objects stack is not empty:
	while (gray_objects->count > 0)
	{
		// Pop an object off the gray_objects stack.
		// Call trace_blacken_object on the object.
		trace_blacken_object(gray_objects, stack_pop(gray_objects));
	}

	// Free the gray_objects stack (stack_free)
	stack_free(gray_objects);
}

void trace_blacken_object(stack_t *gray_objects, snek_object_t *obj)
{
	// If the object is an INTEGER, FLOAT or STRING do nothing. These don't contain references to other objects.
	switch (obj->kind)
	{
	case INTEGER:
	case FLOAT:
	case STRING:
		break;

	// If it's a VECTOR3, call trace_mark_object on the x, y, and z fields.
	case VECTOR3:
	{
		trace_mark_object(gray_objects, obj->data.v_vector3.x);
		trace_mark_object(gray_objects, obj->data.v_vector3.y);
		trace_mark_object(gray_objects, obj->data.v_vector3.z);
		break;
	}

	// If it's an ARRAY, call trace_mark_object on each element.
	default:
		for (size_t i = 0; i < obj->data.v_array.size; i++)
		{
			trace_mark_object(gray_objects, obj->data.v_array.elements[i]);
		}

		break;
	}
}

void trace_mark_object(stack_t *gray_objects, snek_object_t *obj)
{
	// If the object is NULL or already marked, return immediately without doing anything.
	if (obj == NULL || obj->is_marked)
		// Should exit
		return;

	// Otherwise, mark the object and push it onto the gray_objects stack.
	obj->is_marked = true;
	stack_push(gray_objects, obj);
}

void vm_collect_garbage(vm_t *vm)
{
	// Call mark.
	mark(vm);

	// Call trace.
	trace(vm);

	// Call sweep.
	sweep(vm);
}

void sweep(vm_t *vm)
{
	// Iterate over all of the VM's objects:
	for (size_t i = 0; i < vm->objects->count; i++)
	{
		snek_object_t *obj = vm->objects->data[i];

		// Should check if `obj` exists???

		if (obj->is_marked)
		{
			// If the object is marked, reset is_marked = false and continue.
			obj->is_marked = false;
			continue;
		}

		// Otherwise, free the object and set the data at that position in the stack to NULL.
		// You can use the snek_object_free function to free the objects
		snek_object_free(obj);
		vm->objects->data[i] = NULL;
		// Call stack_remove_nulls to remove any NULL objects from the VM's objects stack.
	}

	stack_remove_nulls(vm->objects);
}
