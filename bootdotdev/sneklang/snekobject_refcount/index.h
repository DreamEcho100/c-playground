#ifndef SNEKLANG_SNEKOBJECT_REFCOUNT_V_INDEX_H
#define SNEKLANG_SNEKOBJECT_REFCOUNT_V_INDEX_H

#include <stdbool.h>

#include "../snek_object_t.h"
#include "../vm/index.h"

// Forward declare the snek_object_t struct at the top of the file.
// It will need to be used in **a circular dependency**.

typedef enum SnekObjectKind_refcount_v
{
	INTEGER,
	FLOAT,
	STRING,
	VECTOR3,
	ARRAY,
} snek_object_kind_refcount_v_t;

typedef struct
{
	size_t size;
	snek_object_refcount_v_t **elements;
} snek_array_refcount_v_t;

typedef struct SnekVector
{
	snek_object_refcount_v_t *x;
	snek_object_refcount_v_t *y;
	snek_object_refcount_v_t *z;
} snek_vector_refcount_v_t;

typedef union SnekObjectData_refcount_v
{
	int v_int;
	float v_float;
	char *v_string;
	// By embedding v_vector3 directly, you're avoiding unnecessary indirection and saving memory.
	// Just malloc once for obj, and you're golden! 🌟
	// This keeps your memory usage more efficient and avoids unnecessary allocations!
	snek_vector_refcount_v_t v_vector3;
	snek_array_refcount_v_t v_array;
} snek_object_data_refcount_v_t;

typedef struct SnekObject_refcount_v
{
	snek_object_kind_refcount_v_t kind;
	snek_object_data_refcount_v_t data;
	int refcount;
} snek_object_refcount_v_t;

snek_object_refcount_v_t *_new_snek_object_refcount_v(vm_refcount_v_t *vm);

snek_object_refcount_v_t *new_snek_integer_refcount_v(vm_refcount_v_t *vm, int value);
snek_object_refcount_v_t *new_snek_float_refcount_v(vm_refcount_v_t *vm, float value);
snek_object_refcount_v_t *new_snek_string_refcount_v(vm_refcount_v_t *vm, char *value);
snek_object_refcount_v_t *new_snek_vector3_refcount_v(vm_refcount_v_t *vm, snek_object_refcount_v_t *x, snek_object_refcount_v_t *y, snek_object_refcount_v_t *z);
snek_object_refcount_v_t *new_snek_array_refcount_v(vm_refcount_v_t *vm, size_t size);

int snek_length_refcount_v(snek_object_refcount_v_t *obj);

bool snek_array_set_refcount_v(snek_object_refcount_v_t *snek_obj, size_t index, snek_object_refcount_v_t *value);
snek_object_refcount_v_t *snek_array_get_refcount_v(snek_object_refcount_v_t *snek_obj, size_t index);

snek_object_refcount_v_t *snek_add_refcount_v(vm_refcount_v_t *vm, snek_object_refcount_v_t *a, snek_object_refcount_v_t *b);

void refcount_free(snek_object_refcount_v_t *obj);
void refcount_inc(snek_object_refcount_v_t *obj);
void refcount_dec(snek_object_refcount_v_t *obj);
void snek_object_free_refcount_v(snek_object_refcount_v_t *obj);

#endif // SNEKLANG_SNEKOBJECT_REFCOUNT_V_INDEX_H
