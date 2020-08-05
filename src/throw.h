#pragma once
#ifndef _OOC_THROW_H_
#define _OOC_THROW_H_

#include <setjmp.h>

#define try         do{ jmp_buf ex_buf__; switch( setjmp(ex_buf__) ){ case 0: while(1){
#define catch(x)    break; case x:
#define finally     break; } default:
#define yrt         } }while(0)
#define throw(x)    longjmp(ex_buf__, x)

#include <stdio.h>
#include <stdlib.h>

// must setjmp(panic_buf) just before the end of main
jmp_buf panic_buf;

#define panicf(fmt, ...)    do { fprintf(stderr, fmt, ## __VA_ARGS__); longjmp(panic_buf, 1); exit(0); } while (0)

#endif
