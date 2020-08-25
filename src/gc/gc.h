//
// Created by Thomas Bradford on 17.08.20.
//

#ifndef ALE_SRC_GC_GC_H_
#define ALE_SRC_GC_GC_H_

#include "reflist.h"
#include "refspan.h"
#include "type.h"
#include "typedefs.h"

struct GC {
  RefSpan *refs;
  RefList *pinned;
  RefList *freed;
};

GC *GCInit();
Ref *GCNew(GC *gc, Type *type);
Ref *GCNewSized(GC *gc, Type *type, Size_t size);

#endif// ALE_SRC_GC_GC_H_
