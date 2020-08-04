#pragma once
#ifndef _OOC_SHARED_PTR_H_
#define _OOC_SHARED_PTR_H_

#include "utils.h"

#include <malloc.h>
#include <stdio.h>

#define SharedPtr(Type) shared_ptr*
#define WeakPtr(Type) weak_ptr*

typedef struct shared_ptr shared_ptr;
struct shared_ptr;

typedef struct weak_ptr weak_ptr;
struct weak_ptr;

SharedPtr(T) new_shared(Ptr(T) ptr, disposer ptr_disposer);

SharedPtr(T) shared_ref(SharedPtr(T) sp);

WeakPtr(T) weak_ref(SharedPtr(T) sp);

void remove_shared(SharedPtr(T) sp);

void remove_weak(WeakPtr(T) wp);

#endif
