#pragma once
#ifndef _OOC_OBJ_SHOW_H_
#define _OOC_OBJ_SHOW_H_

#include "../new.h"
#include "../throw.h"

struct Show_proto {
    interface_id* id;
    char* (*show)(Ptr(T) this);
};

// interface pointer actually stored in class
typedef struct Show_proto* Show_object;

interface_id _Show_id = {};
interface_id* Show_id = &_Show_id;

char* show(Ptr(T) this);

#endif
