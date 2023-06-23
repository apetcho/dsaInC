#ifndef SWZLAB_H
#define SWZLAB_H

#include<stddef.h>
#include<stdarg.h>

enum Type{
    TYPE_INT,
    TYPE_DOUBLE,
    TYPE_STRING,
    //TYPE_OBJECT,
};

/*
typedef struct Allocator{
    size_t allocSize;
    void* (*fn_alloc)(size_t);
    void* (*fn_realloc)(void*, size_t);
    void (*fn_dealloc)(void*);
} Allocator;
*/

// -*-
typedef struct Object{
    const struct SWZTrait_t *traits;
} Object;

typedef struct SWZTrait_t {
    Object* (*clone)(const Object*);
    char* (*format)(const char*, const Object*);
    void (*print)(const Object*);
    void (*destroy)(Object*);
    // unsigned int (*hash)(const Object*);          // -> unsigned int value
    // bool (*equal)(const Object*, const Object*);  // -> true or false
    // int (*compare)(const Object*, const Object*); // -> -1 or 0 or 1
} SWZTrait_t;

// -*-----------------------------------------------------------------*-
// -*- SWZLab Object API                                             -*-
// -*-----------------------------------------------------------------*-
Object* swz_new(enum Type, ...);
Object* swz_clone(const Object* obj);
char* swz_format(const char *fmt, const Object *obj);
void swz_print(const Object *obj);
void swz_println(const Object *obj);
void swz_destroy(Object *obj);

/*
enum OptionType { None, Some };
typedef struct {
    enum OptionType type;
    union{
        Object *none;
        Object *some;
    };
} Option;
enum ResultType { Err, Ok};
typedef struct {
    enum ResultType type;
    union{
        Object *err;
        Object *ok;
    };
} Result_t;
enum MatchType { RESULT, OPTION};
typedef struct {
    enum MatchType type;
    union{
        Result_t result;
        Option_t option;
    };
} Match_t;
Object* obj_match(Match_t match);
*/
// -*-
// void obj_unwrap_result(Result_t *result, void *out);
// void obj_unwrap_option(Option_t *option, void *out);

// -*-------------------------------------------------------------------*-
// -*- Number API                                                      -*-
// -*-------------------------------------------------------------------*-
/*
...
*/

// -*-------------------------------------------------------------------*-
// -*- String API                                                      -*-
// -*-------------------------------------------------------------------*-
/*
...
*/

// -*-------------------------------------------------------------------*-
// -*- List API                                                        -*-
// -*-------------------------------------------------------------------*-
/*
typedef struct List *List;
swz_li
...
*/

#endif
