#pragma once
#ifndef _OOC_OWNER_PTR_H_
#define _OOC_OWNER_PTR_H_

#include "utils.h"
#include "sp_pre.h"

#include <malloc.h>
#include <stdio.h>

// type annotator
#define Owner(Type) owner*
#define MutRef(Type) mut_ref*
#define ImmutRef(Type) immut_ref*

typedef struct owner owner;
struct owner;

Owner(T) own(Obj(T) raw_ptr, bool readonly _Default_(false), disposer ptr_disposer _Nullable_ _Default_(default_disposer));

void delete_owner(Owner(T) o);


typedef struct mut_ref mut_ref;
struct mut_ref;

typedef struct immut_ref immut_ref;
struct immut_ref;

// returns `NULL` if the owner is not mutable or has a mutable reference
MutRef(T) borrow_mut(Owner(T) _owner);

// returns `NULL` if the owner has a mutable reference
ImmutRef(T) borrow_immut(Owner(T) _owner);

#endif
