//
// Created by Thomas Bradford on 19.08.20.
//

#ifndef ALE_SRC_GC_REF_H_
#define ALE_SRC_GC_REF_H_

#include <stdint.h>

#include "entry.h"

typedef uint8_t GCColor_t;

const GCColor_t GC_Gray = 1;

typedef struct {
  struct GC *gc;
  GCColor_t color;
  GCEntry entry;
} GCRef;

#define RefGC(ref) ((GC *) (ref->gc))
#define DeRef(ref) (ref->entry.data)

#endif// ALE_SRC_GC_REF_H_
