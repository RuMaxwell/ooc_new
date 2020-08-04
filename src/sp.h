#pragma once
#ifndef _OOC_SP_H_
#define _OOC_SP_H_

#include "sp_pre.h"
#include "owner.h"
#include "shared_ptr.h"
#include "auto_ptr.h"

// #define Unique_ptr(Type) unique_ptr*

// typedef struct unique_ptr unique_ptr;
// struct unique_ptr {
//     void* ptr;
// };

// a unified interface to dereference a synchronized smart pointer
void* deref(void* sp);

#endif
