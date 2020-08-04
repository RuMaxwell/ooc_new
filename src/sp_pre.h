#pragma once
#ifndef _OOC_SP_PRE_H_
#define _OOC_SP_PRE_H_

typedef void (*disposer)(void*);

void default_disposer(void* ptr);

#endif
