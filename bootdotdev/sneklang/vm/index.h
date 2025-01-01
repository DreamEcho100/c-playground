#ifndef VM_UTILS_H
#define VM_UTILS_H

#include "../stack/index.h"
#include "../snek_object_t.h"

typedef struct VirtualMachine
{
	stack_t *frames;
	stack_t *objects;
} vm_refcount_v_t;

typedef struct StackFrame
{
	stack_t *references;
} frame_t;

vm_refcount_v_t *vm_new();
void vm_free(vm_refcount_v_t *vm);

void vm_frame_push(vm_refcount_v_t *vm, frame_t *frame);
frame_t *vm_new_frame(vm_refcount_v_t *vm);

void frame_free(frame_t *frame);

void vm_track_object(vm_refcount_v_t *vm, snek_object_refcount_v_t *obj);

void frame_reference_object(frame_t *frame, snek_object_refcount_v_t *obj);

void mark(vm_refcount_v_t *vm);

void trace(vm_refcount_v_t *vm);
void trace_blacken_object(stack_t *gray_objects, snek_object_refcount_v_t *obj);
void trace_mark_object(stack_t *gray_objects, snek_object_refcount_v_t *obj);

/** This is the function that runs the GC. */
void vm_collect_garbage(vm_refcount_v_t *vm);
void sweep(vm_refcount_v_t *vm);

#endif // VM_UTILS_H