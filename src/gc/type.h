#pragma once

#include "typedefs.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*Marker)(GC* gc, void* ptr);
typedef void (*Finalizer)(GC* gc, void* ptr);

typedef struct Type {
  Size_t default_size;
  Marker marker;
  Finalizer finalizer;
} Type;

#ifdef __cplusplus
}
#endif
