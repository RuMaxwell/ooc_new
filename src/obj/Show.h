#pragma once
#ifndef _OOC_OBJ_SHOW_H_
#define _OOC_OBJ_SHOW_H_

#include "../new.h"

struct Show_proto {
    interface_id* id;
    char* (*show)(Ptr(T) this);
};

char* show(Ptr(T) this);

interface_id _Show_id = {};
interface_id* Show_id = &_Show_id;

#endif
