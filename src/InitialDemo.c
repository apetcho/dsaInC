#include "initialDemo.h"

#include<stdlib.h>
#include<stdarg.h>
#include<string.h>
#include<assert.h>
#include<stdio.h>

// -*-------------------------------------------------------------------*-
// -*- Integer                                                         -*-
// -*-------------------------------------------------------------------*-
typedef struct {
    SWZTrait_t *traits;
    int value;
} Integer;

Object* new_int(int value);
// -*-
static void _print_integer(const Object *obj);
static Object* _clone_integer(const Object *obj);
static void _destroy_integer(Object *obj);

static SWZTrait_t _integerTrait = {
    .clone = _clone_integer,
    .print = _print_integer,
    .destroy = _destroy_integer,
};

// -*-
static void _print_integer(const Object *obj){
    fprintf(stdout, "%d", ((const Integer*)obj)->value);
}

static Object* _clone_integer(const Object *obj){
    return new_int(((Integer*)obj)->value);
}

static void _destroy_integer(Object *obj){
    free(obj);
}

// -*-
Object* new_int(int value){
    Integer *self = malloc(sizeof(*self));
    assert(self);
    self->traits = &_integerTrait;
    return (Object*)self;
}

// -*-------------------------------------------------------------------*-
// -*- String                                                          -*-
// -*-------------------------------------------------------------------*-
typedef struct {
    SWZTrait_t *traits;
    char *str;
} String;
Object* new_string(const char *str);

static void _print_string(const Object*);
static Object* _clone_string(const Object*);
static void _destroy_string(Object*);

static SWZTrait_t _stringTraits = {
    .clone = _clone_string,
    .print = _print_string,
    .destroy = _destroy_string,
};

// -*-
static char* _intern_str(const char *str){
    char *rv = malloc(strlen(str)+1);
    assert(rv);
    strcpy(rv, str);
    return rv;
}

// -*-
static void _print_string(const Object *obj){
    fputs(((String*)obj)->str, stdout);
}

static Object* _clone_string(const Object *obj){
    return new_string(((String*)obj)->str);
}

static void _destroy_string(Object *obj){
    String *self = (String*)obj;
    free(self->str);
    free(self);
}

Object* new_string(const char *str){
    String *self = malloc(sizeof(*self));
    assert(self);
    self->traits = &_stringTraits;
    self->str = _intern_str(str);

    return (Object*)self;
}

// -*-------------------------------------------------------------------*-
// -*- Stack                                                           -*-
// -*-------------------------------------------------------------------*-
struct StackNode{
    struct StackNode *next;
    Object *obj;
};

// -*-
Stack_t* stack_create(){
    Stack_t *stack = malloc(sizeof(*stack));
    assert(stack);
    *stack = NULL;
    return stack;
}

// -*-
void stack_destroy(Stack_t *stack){
    Object *obj;
    while(!stack_empty(stack)){
        obj = stack_pop(stack);
        //obj->traits->destroy(obj);
        obj_destroy(obj);
    }
    free(stack);
}

// -*-
void stack_push(Stack_t *stack, Object* obj){
    struct StackNode *node = malloc(sizeof(*node));
    node->next = *stack;
    //node->obj = obj->traits->clone(obj);
    node->obj = obj_clone(obj);
    *stack = node;
}

// -*-
Object* stack_pop(Stack_t *stack){
    assert(!stack_empty(stack));
    struct StackNode *node = *stack;
    Object *obj = node->obj;
    *stack = node->next;
    free(node);
    return obj;
}

// -*-
bool stack_empty(Stack_t *stack){
    return *stack == NULL;
}

void stack_print(const Stack_t *stack){
    for(struct StackNode const* node = *stack; node; node = node->next){
        obj_print(node->obj);
        putchar(' ');
    }
    putchar('\n');
}

// -*--
static Object* _new_int(va_list arg){
    int value = va_arg(arg, int);

    return new_int(value);
}

static Object* _new_str(va_list arg){
    const char* str = va_arg(arg, const char*);
    return new_string(str);
}

Object* obj_new(enum Type type, ...){
    Object* obj;
    va_list arg;
    switch(type){
    case TYPE_INT:
        va_start(arg, type);
        obj = _new_int(arg);
        va_end(arg);
        break;
    case TYPE_STR:
        va_start(arg, type);
        obj = _new_str(arg);
        va_end(arg);
        break;
    default:
        fprintf(stderr, "\x1b[31mError\x1b[0m: Unknown type\n");
        abort();
        break; // never reached
    }

    return obj;
}

Object* obj_clone(const Object *obj){
    assert(obj);
    return obj->traits->clone(obj);
}

void obj_print(const Object *obj){
    if(obj == NULL){ printf("(null)"); }
    obj->traits->print(obj);
}

void obj_destroy(Object *obj){
    if(!obj){ return; }
    obj->traits->destroy(obj);
}
