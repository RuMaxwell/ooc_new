#pragma once
#ifndef _OOC_INTERFACE_H_
#define _OOC_INTERFACE_H_

#include "utils.h"

#define __TRIVIAL__ char _;

typedef struct interface_id interface_id;
struct interface_id {
    __TRIVIAL__
};

typedef struct interface_node INod;
struct interface_node {
    Obj(interface) interface;
    INod* next;
};

#endif
