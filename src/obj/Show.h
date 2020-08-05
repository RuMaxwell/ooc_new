#pragma once
#ifndef _OOC_OBJ_SHOW_H_
#define _OOC_OBJ_SHOW_H_

#include "../new.h"
#include "../throw.h"

typedef struct Show_proto Show;
struct Show_proto {
    interface_id* id;
    char* (*show)(Obj(T) this);
};

// interface pointer actually stored in class
typedef Show* Show_object;

interface_id Show_id;

char* show(Obj(T) this);

#endif
