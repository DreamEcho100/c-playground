#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "./index.h"
#include "../vm/index.h"

// #pragma once

void snek_object_free(snek_object_t *obj)
{

	switch (obj->kind)
	{
	case INTEGER:
	case FLOAT:
		break;
	case STRING:
		free(obj->data.v_string);
		break;
	case VECTOR3:
	{
		break;
	}
	case ARRAY:
	{
		free(obj->data.v_array.elements);
		break;
	}
	}
	free(obj);
}

void refcount_free(snek_object_t *obj)
{
	if (obj == NULL)
	{
		return;
	}

	switch (obj->kind)
	{
	case INTEGER:
	case FLOAT:
		break;
	case STRING:
		free(obj->data.v_string);
		break;
	case VECTOR3:
	{
		snek_vector_t vec = obj->data.v_vector3;
		if (vec.x)
			refcount_dec(vec.x);
		if (vec.y)
			refcount_dec(vec.y);
		if (vec.z)
			refcount_dec(vec.z);
		break;
	}
	case ARRAY:
	{
		snek_array_t array = obj->data.v_array;
		for (size_t i = 0; i < array.size; ++i)
		{
			if (array.elements[i])
				refcount_dec(array.elements[i]);
		}
		free(array.elements);
		break;
	}
	default:
		fprintf(stderr, "Error: Unhandled object kind in refcount_free.\n");
		exit(EXIT_FAILURE); // Gracefully terminate the program
	}
	free(obj);
}
void refcount_inc(snek_object_t *obj)
{
	if (obj == NULL)
	{
		return;
	}

	obj->refcount++;
	return;
}
void refcount_dec(snek_object_t *obj)
{

	if (
			obj == NULL
			// Prevent double free _(dangling pointer)_
			|| obj->refcount == 0)
	{
		return;
	}
	obj->refcount--;
	if (obj->refcount == 0)
	{
		return refcount_free(obj);
	}
	return;
}

snek_object_t *_new_snek_object(vm_t *vm)
{
	snek_object_t *obj = (snek_object_t *)malloc(sizeof(snek_object_t));
	if (obj == NULL)
	{
		fprintf(stderr, "Error: Couldn't allocate snek object.\n");
		exit(EXIT_FAILURE);
	}

	obj->refcount = 1;

	vm_track_object(vm, obj);

	// obj->refcount = 1;
	return obj;
}

snek_object_t *snek_add(vm_t *vm, snek_object_t *a, snek_object_t *b)
{
	// Always check for NULL after allocations
	if (a == NULL || b == NULL)
		return NULL;

	switch (a->kind)
	{
	case INTEGER:
	{
		switch (b->kind)
		{
		case INTEGER:
		{

			return new_snek_integer(vm, a->data.v_int + b->data.v_int);
		}
		case FLOAT:
		{
			return new_snek_float(vm, a->data.v_int + b->data.v_float);
		}
		default:
		{
			return NULL;
		}
		}
	}
	case FLOAT:
	{
		switch (b->kind)
		{
		case INTEGER:
		{

			return new_snek_float(vm, a->data.v_int + b->data.v_float);
		}
		case FLOAT:
		{
			return new_snek_float(vm, a->data.v_float + b->data.v_float);
		}
		default:
		{
			return NULL;
		}
		}
	}
	case STRING:
	{
		if (b->kind != STRING)
		{
			return NULL;
		}

		// size_t new_len = strlen(a->data.v_string) + strlen(b->data.v_string)
		// 								 // To properly handling the null terminator `\0`
		// 								 + 1;
		// char *new_string = (char *)calloc(new_len, sizeof(char));
		// if (new_string == NULL)
		// {
		// 	return NULL;
		// }

		// strcat(new_string, a->data.v_string);
		// strcat(new_string, b->data.v_string);

		// Calculate total length needed
		size_t a_len = strlen(a->data.v_string);
		size_t b_len = strlen(b->data.v_string);
		size_t new_len = a_len + b_len + 1; // +1 for null terminator

		// Allocate string buffer
		char *new_string = (char *)malloc(new_len);
		if (new_string == NULL)
		{
			return NULL;
		}

		// Copy strings directly (more efficient than calloc + strcat)
		memcpy(new_string, a->data.v_string, a_len);
		memcpy(new_string + a_len, b->data.v_string, b_len);
		new_string[new_len - 1] = '\0'; // Add null terminator

		snek_object_t *result = new_snek_string(vm, new_string);
		// !IMPORTANT;
		// Free the intermediate buffer after new_snek_string makes its copy
		// Because `new_snek_string` makes its own copy of the string.
		free(new_string);
		return result;
	}
	case VECTOR3:
	{
		if (b->kind != VECTOR3)
		{
			return NULL;
		}

		return new_snek_vector3(
				vm,
				snek_add(vm, a->data.v_vector3.x, b->data.v_vector3.x),
				snek_add(vm, a->data.v_vector3.y, b->data.v_vector3.y),
				snek_add(vm, a->data.v_vector3.z, b->data.v_vector3.z));
	}
	case ARRAY:
	{
		if (b->kind != ARRAY)
		{
			return NULL;
		}

		size_t new_size = a->data.v_array.size + b->data.v_array.size;
		snek_object_t *new_array_obj = new_snek_array(vm, new_size);

		// Use the accessor functions when available (snek_array_get, snek_array_set)
		size_t i = 0;
		for (; i < a->data.v_array.size; ++i)
		{
			snek_array_set(new_array_obj, i, snek_array_get(a, i));
		}

		size_t j = 0;
		for (; j < b->data.v_array.size; j++)
		{
			snek_array_set(new_array_obj, j + i, snek_array_get(b, j));
		}

		return new_array_obj;
	}
	default:
		fprintf(stderr, "Error: Unhandled object kind in snek_add.\n");
		exit(EXIT_FAILURE); // Gracefully terminate the program
	}
}

int snek_length(snek_object_t *obj)
{
	// If the input is NULL return -1 (which we've chosen to indicate failure).
	if (obj == NULL)
	{
		return -1;
	}

	switch (obj->kind)
	{
		// If the input is an integer, its size is always 1.
		// If the input is a float, its size is always 1.
	case INTEGER:
	case FLOAT:
		return 1;
		// If the input is a string, its size is the length of the string in bytes.
	case STRING:
		return strlen(obj->data.v_string);
		// If the input is a VECTOR3, its size is always 3.
	case VECTOR3:
		return 3;
		// If the input is an array, its size is stored in the v_array.size field.
	case ARRAY:
		return obj->data.v_array.size;
		// If the input is none of the above, return -1.
	default:
		return -1;
	}
}
bool snek_array_set(snek_object_t *snek_obj, size_t index, snek_object_t *value)
{
	if (
			snek_obj == NULL || value == NULL ||
			//
			snek_obj->kind != ARRAY ||
			//
			index >= snek_obj->data.v_array.size)
	{
		return false;
	}

	// Is this needed or even correct in this context?
	// if (snek_obj->data.v_array.elements[index] == NULL)
	// {
	// 	snek_obj->data.v_array.size++;
	// }

	if (snek_obj->data.v_array.elements[index] != NULL)
	{
		refcount_dec(snek_obj->data.v_array.elements[index]);
	}
	snek_obj->data.v_array.elements[index] = value;
	refcount_inc(value);
	return true;
}
snek_object_t *snek_array_get(snek_object_t *snek_obj, size_t index)
{

	if (
			snek_obj == NULL ||
			//
			snek_obj->kind != ARRAY ||
			//
			index >= snek_obj->data.v_array.size)
		return NULL;

	return snek_obj->data.v_array.elements[index];
}
snek_object_t *new_snek_array(vm_t *vm, size_t size)
{
	snek_object_t *obj = _new_snek_object(vm);
	if (obj == NULL)
	{
		fprintf(stderr, "Error: Couldn't allocate snek object.\n");
		exit(EXIT_FAILURE);
	}

	obj->kind = ARRAY;
	// obj->data.element = (snek_object_t*)malloc(sizeof(snek_object_t*) * size);
	snek_object_t **elements = (snek_object_t **)calloc(size, sizeof(snek_object_t *));
	if (elements == NULL)
	{
		free(obj);
		fprintf(stderr, "Error: Couldn't allocate snek object elements.\n");
		exit(EXIT_FAILURE);
	}
	obj->data.v_array = (snek_array_t){.size = size, .elements = elements};

	return obj;
}

snek_object_t *new_snek_vector3(vm_t *vm, snek_object_t *x, snek_object_t *y, snek_object_t *z)
{
	snek_object_t *obj = _new_snek_object(vm);
	if (obj == NULL)
	{
		fprintf(stderr, "Error: Couldn't allocate snek object.\n");
		exit(EXIT_FAILURE);
	}

	obj->kind = VECTOR3;
	obj->data.v_vector3 = (snek_vector_t){.x = x, .y = y, .z = z};
	if (x)
		refcount_inc(x);
	if (y)
		refcount_inc(y);
	if (z)
		refcount_inc(z);

	return obj;
}

snek_object_t *new_snek_string(vm_t *vm, char *value)
{
	snek_object_t *obj = _new_snek_object(vm);
	if (obj == NULL)
	{
		fprintf(stderr, "Error: Couldn't allocate snek object.\n");
		exit(EXIT_FAILURE);
	}

	obj->kind = STRING;

	// Calculate the length (in bytes using strlen) of the string passed in.
	size_t value_len = strlen(value);
	// Allocate memory in a char * field equal to the length of the string plus one (for the null terminator).
	char *v_string = (char *)malloc(value_len + 1);
	// If the allocation fails, return NULL and free the memory allocated for the snek object.
	if (v_string == NULL)
	{
		free(obj);
		fprintf(stderr, "Error: Couldn't allocate string.\n");
		exit(EXIT_FAILURE);
	}
	// Copy the data from the input value into the new string field you just allocated using strcpy.
	strcpy(v_string, value);
	// Store the newly allocated string in the object.
	obj->data.v_string = v_string;

	return obj;
}

snek_object_t *new_snek_integer(vm_t *vm, int value)
{
	snek_object_t *obj = _new_snek_object(vm);
	if (obj == NULL)
	{
		fprintf(stderr, "Error: Couldn't allocate snek object.\n");
		exit(EXIT_FAILURE);
	}

	obj->kind = INTEGER;
	obj->data.v_int = value;
	return obj;
}

snek_object_t *new_snek_float(vm_t *vm, float value)
{
	snek_object_t *obj = _new_snek_object(vm);
	if (obj == NULL)
	{
		fprintf(stderr, "Error: Couldn't allocate snek object.\n");
		exit(EXIT_FAILURE);
	}

	obj->kind = FLOAT;
	obj->data.v_float = value;
	return obj;
}
