//
// Created by Thomas Bradford on 17.08.20.
//

#ifndef ALE_SRC_GC_GC_H_
#define ALE_SRC_GC_GC_H_

#include "ref.h"
#include "reflist.h"
#include "refspan.h"

typedef struct {
  GCRefSpan *refs;
  GCRefList *pinned;
  GCRefList *freed;
} GC;

GC *CreateGC();
GCRef *GCMalloc(GC *gc, GCType *type, GCSize_t size);
GCRef *GCPin(GCRef *ref);
GCRef *GCUnpin(GCRef *ref);
GCRef *GCMark(GCRef *ref);

#endif// ALE_SRC_GC_GC_H_
