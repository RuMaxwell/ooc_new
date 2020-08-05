#pragma once
#ifndef _OOC_NEW_H_
#define _OOC_NEW_H_

#include "interface.h"
#include "throw.h"
#include "utils.h"

#include <malloc.h>
#include <stdarg.h>
#include <stdio.h>


typedef struct class class;
struct class {
    size_t size;
    char* name;
    INod* implements;

    void* (*constr)(void* raw, va_list* app);
    void* (*destr)(void* this);
};

Obj(type)       new             (class* type, ...);
void            delete          (Obj(T) this);
class*          type_of         (Obj(T) this);
const char*     typename        (Obj(T) this);
bool            instanceof      (Obj(T) this, class* type);
Obj(interface)  get_interface   (Obj(T) this, interface_id* i);

#endif
