/* DO_NOT_USE */

/* full garbage collected smart pointer with ref count (and mark-sweep?) */

#pragma once
#ifndef _OOC_AUTO_PTR_H_
#define _OOC_AUTO_PTR_H_

#include "utils.h"

#include <malloc.h>
#include <stdio.h>

#define AutoPtr(Type) auto_ptr*

typedef struct auto_ptr auto_ptr;
struct auto_ptr;

Ptr(T) automize(Ptr(T) ptr);

// manually delete an auto pointer
void deactivate(Ptr(T) ptr);

#endif
