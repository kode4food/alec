//
// Created by Thomas Bradford on 25.08.20.
//

#ifndef ALE_SRC_GC_TYPE_H_
#define ALE_SRC_GC_TYPE_H_

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

#endif//ALE_SRC_GC_TYPE_H_
