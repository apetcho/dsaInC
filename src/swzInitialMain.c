#include "initialDemo.h"
#include<stdlib.h>
#include<stdio.h>

#define N   3

// -*---------------*-
// -*- MAIN DRIVER -*-
// -*---------------*-
int main(int argc, char **argv){
    char text[] = "hi";
    Object *obj;
    int n = N;
    if(argc >= 2){ n = atoi(argv[1]); }

    Stack_t* stack = stack_create();
    for(int i=0; i < n; i++){
        text[0] = 'a' + i;
        //obj = new_string(text);
        obj = obj_new(TYPE_STR, text);
        stack_push(stack, obj);
        //obj->traits->destroy(obj);
        obj_destroy(obj);
        stack_print(stack);
        //obj = new_int(i);
        obj = obj_new(TYPE_INT, i);
        stack_push(stack, obj);
        //obj->traits->destroy(obj);
        obj_destroy(obj);
        stack_print(stack);
    }

    while(!stack_empty(stack)){
        obj = stack_pop(stack);
        putchar('[');
        //obj->traits->print(obj);
        obj_print(obj);
        //obj->traits->destroy(obj);
        obj_destroy(obj);
        fputs("] ", stdout);
        stack_print(stack);
    }

    stack_destroy(stack);

    return 0;
}
