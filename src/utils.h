#pragma once
#ifndef _OOC_UTILS_H_
#define _OOC_UTILS_H_

/* parameter annotators */
// declares a param accepts `NULL`.
#define _Nullable_
// declares a param reject `NULL`.
#define _NonNull_
// declares a value to be passed if the user does not sure what to put into.
#define _Default_(x)

/* type annotators */
// any pointer type
#define Ptr(Type) void*

#define bool int
#define false ((bool)0)
#define true ((bool)!0)

#endif
