//
// Created by Thomas Bradford on 17.08.20.
//

#ifndef ALE_SRC_GC_GC_H_
#define ALE_SRC_GC_GC_H_

#include "ref.h"
#include "reflist.h"
#include "refspan.h"

typedef struct {
  RefSpan *refs;
  RefList *pinned;
  RefList *freed;
} GC;

GC *GCInit();
Ref *GCNew(GC *gc, Type *type);
Ref *GCNewSized(GC *gc, Type *type, GCSize_t size);
Ref *RefPin(Ref *ref);
Ref *RefUnpin(Ref *ref);
Ref *RefMark(Ref *ref);

#endif// ALE_SRC_GC_GC_H_
