#ifndef SNEKLANG_SNEKOBJECT_INDEX_H
#define SNEKLANG_SNEKOBJECT_INDEX_H

#include <stdbool.h>

#include "../snek_object_t.h"
#include "../vm/index.h"

// Forward declare the snek_object_t struct at the top of the file.
// It will need to be used in **a circular dependency**.

typedef enum SnekObjectKind
{
	INTEGER,
	FLOAT,
	STRING,
	VECTOR3,
	ARRAY,
} snek_object_kind_t;

typedef struct
{
	size_t size;
	snek_object_t **elements;
} snek_array_t;

typedef struct SnekVector
{
	snek_object_t *x;
	snek_object_t *y;
	snek_object_t *z;
} snek_vector_t;

typedef union SnekObjectData
{
	int v_int;
	float v_float;
	char *v_string;
	// By embedding v_vector3 directly, you're avoiding unnecessary indirection and saving memory.
	// Just malloc once for obj, and you're golden! 🌟
	// This keeps your memory usage more efficient and avoids unnecessary allocations!
	snek_vector_t v_vector3;
	snek_array_t v_array;
} snek_object_data_t;

typedef struct SnekObject
{
	snek_object_kind_t kind;
	snek_object_data_t data;
	int refcount;
} snek_object_t;

snek_object_t *_new_snek_object(vm_t *vm);

snek_object_t *new_snek_integer(vm_t *vm, int value);
snek_object_t *new_snek_float(vm_t *vm, float value);
snek_object_t *new_snek_string(vm_t *vm, char *value);
snek_object_t *new_snek_vector3(vm_t *vm, snek_object_t *x, snek_object_t *y, snek_object_t *z);
snek_object_t *new_snek_array(vm_t *vm, size_t size);

bool snek_array_set(snek_object_t *snek_obj, size_t index, snek_object_t *value);
snek_object_t *snek_array_get(snek_object_t *snek_obj, size_t index);

snek_object_t *snek_add(vm_t *vm, snek_object_t *a, snek_object_t *b);

void refcount_free(snek_object_t *obj);
void refcount_inc(snek_object_t *obj);
void refcount_dec(snek_object_t *obj);
#endif // SNEKLANG_SNEKOBJECT_INDEX_H

void snek_object_free(snek_object_t *obj);