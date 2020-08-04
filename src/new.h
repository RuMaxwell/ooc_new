#pragma once
#ifndef _OOC_NEW_H_
#define _OOC_NEW_H_

#include "interface.h"
#include "utils.h"

#include <malloc.h>
#include <stdarg.h>
#include <stdio.h>

#define CLASS_NAME_MAX_LEN 64


typedef struct class class;
struct class {
    size_t size;
    char* name;
    size_t interface_count;
    Ptr(interface)* implements;

    void* (*constr)(void* raw, va_list* app);
    void* (*destr)(void* this);
};

Ptr(type)       new             (class* type, ...);
void            delete          (Ptr(T) this);
class*          type_of         (Ptr(T) this);
const char*     typename        (Ptr(T) this);
bool            instanceof      (Ptr(T) this, class* type);
Ptr(interface)  get_interface   (Ptr(T) this, interface_id* i);

#endif
