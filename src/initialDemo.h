#ifndef INITIAL_DEMO_H
#define INITIAL_DEMO_H

#include<stdbool.h>
// -*-
typedef struct {
    const struct SWZTrait_t *traits;
} Object;

typedef struct SWZTrait_t {
    Object* (*clone)(const Object*);
    void (*print)(const Object*);
    void (*destroy)(Object*);
} SWZTrait_t;

// -*--------------*-
// -*- Object API -*-
// -*--------------*-
enum Type { TYPE_INT, TYPE_STR };
Object* obj_new(enum Type type, ...);
Object* obj_clone(const Object *obj);
void obj_print(const Object *obj);
void obj_destroy(Object *obj);

// -*-----------*-
// -*- Integer -*-
// -*-----------*-
//Object* new_int(int value);

// -*----------*-
// -*- String -*-
// -*----------*-
//Object* new_string(const char *str);

// -*---------*-
// -*- Stack -*-
// -*---------*-
typedef struct StackNode *Stack_t;

Stack_t* stack_create();
void stack_destroy(Stack_t*);
void stack_push(Stack_t *stack, Object* obj);
Object* stack_pop(Stack_t *stack);
bool stack_empty(Stack_t *stack);
void stack_print(const Stack_t *stack);


#endif
