//
// Created by Thomas Bradford on 19.08.20.
//

#ifndef ALE_SRC_GC_REF_H_
#define ALE_SRC_GC_REF_H_

#include "types.h"

const GCColor_t GC_Gray = 1;

struct GCRef {
  struct GC *gc;
  GCRefType *type;
  GCColor_t color;
  GCSize_t size;
  GCData_t data;
};

#define DeRef(ref) (ref->data)

#endif // ALE_SRC_GC_REF_H_
