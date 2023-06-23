#include "swzlab.h"
#include<stdarg.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<stdio.h>

// -*----------------------------------------------------------------*-
// -*- Integer                                                      -*-
// -*----------------------------------------------------------------*-
static Object* _clone_int(const Object*);
static char* _format_int(const char*, const Object*);
static void _print_int(const Object*);
static void _destroy_int(Object*);

SWZTrait_t _integerTrait = {
    .clone = _clone_int,
    .format = _format_int,
    .print = _print_int,
    .destroy = _destroy_int,
};

static Object* _new_int(va_list arg){
    //! @todo
    return 0;
}

static Object* _clone_int(const Object *obj){
    //! @todo
    return 0;
}

static char* _format_int(const char *fmt, const Object *obj){
    //! @todo
    return 0;
}

static void _print_int(const Object *obj){
    //! @todo
    return;
}

static void _destroy_int(Object *obj){
    //! @todo
    return;
}

// -*----------------------------------------------------------------*-
// -*- Double                                                      -*-
// -*----------------------------------------------------------------*-
static Object* _clone_double(const Object*);
static char* _format_double(const char*, const Object*);
static void _print_double(const Object*);
static void _destroy_double(Object*);

SWZTrait_t _doubleTrait = {
    .clone = _clone_double,
    .format = _format_double,
    .print = _print_double,
    .destroy = _destroy_double,
};

static Object* _new_double(va_list arg){
    //! @todo
    return 0;
}

static Object* _clone_double(const Object *obj){
    //! @todo
    return 0;
}

static char* _format_double(const char *fmt, const Object *obj){
    //! @todo
    return 0;
}

static void _print_double(const Object *obj){
    //! @todo
    return;
}

static void _destroy_double(Object *obj){
    //! @todo
    return;
}


// -*----------------------------------------------------------------*-
// -*- String                                                       -*-
// -*----------------------------------------------------------------*-
static Object* _clone_str(const Object*);
static char* _format_str(const char*, const Object*);
static void _print_str(const Object*);
static void _destroy_str(Object*);

SWZTrait_t _strTrait = {
    .clone = _clone_str,
    .format = _format_str,
    .print = _print_str,
    .destroy = _destroy_str,
};

static Object* _new_str(va_list arg){
    //! @todo
    return 0;
}

static Object* _clone_str(const Object *obj){
    //! @todo
    return 0;
}

static char* _format_str(const char *fmt, const Object *obj){
    //! @todo
    return 0;
}

static void _print_str(const Object *obj){
    //! @todo
    return;
}

static void _destroy_str(Object *obj){
    //! @todo
    return;
}


// -*----------------------------------------------------------------*-
// -*- PUBLIC API                                                   -*-
// -*----------------------------------------------------------------*-
Object* swz_new(enum Type type, ...){
    va_list arg;
    Object *obj;
    switch(type){
    case TYPE_INT:
        va_start(arg, type);
        obj = _new_int(arg);
        va_end(arg);
        break;
    case TYPE_DOUBLE:
        va_start(arg, type);
        obj = _new_double(arg);
        va_end(arg);
        break;
    case TYPE_STRING:
        va_start(arg, type);
        obj = _new_str(arg);
        va_end(arg);
        break;
    default:
        fputs("Error: Type not supported", stderr);
        abort();
    }

    return obj;
}

Object* swz_clone(const Object* obj){
    assert(obj);
    return obj->traits->clone(obj);
}

char* swz_format(const char *fmt, const Object *obj){
    return obj->traits->format(fmt, obj);
}

// -*-
void swz_print(const Object *obj){
    obj->traits->print(obj);
}

void swz_println(const Object *obj){
    swz_print(obj);
    fprintf(stdout, "\n");
}

void swz_destroy(Object *obj){
    obj->traits->destroy(obj);
}
