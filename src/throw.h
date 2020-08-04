#pragma once
#ifndef _OOC_THROW_H_
#define _OOC_THROW_H_

#define try         do{ jmp_buf ex_buf__; switch( setjmp(ex_buf__) ){ case 0: while(1){
#define catch(x)    break; case x:
#define finally     break; } default:
#define yrt         } }while(0)
#define throw(x)    longjmp(ex_buf__, x)

#include <stdio.h>
#include <stdlib.h>

#define panicf(fmt, ...)    do { fprintf(stderr, fmt, ## __VA_ARGS__); exit(1); } while (0)

#endif
