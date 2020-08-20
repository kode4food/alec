//
// Created by Thomas Bradford on 17.08.20.
//

#include "gc.h"

#include <stdlib.h>

#include "data.h"
#include "reflist.h"
#include "refspan.h"

GC *InitGC() {
  GC *gc = malloc(sizeof(GC));
  *gc = (GC){
      .black = GC_Gray - 1,
      .white = GC_Gray + 1,
      .refs = gcAllocRefSpan(defaultSpanSize),
      .pinned = NULL,
      .freed = NULL,
  };
  return gc;
}

GCRef *gcRefAlloc(GC *gc) {
}

void gcRefFree(GCRef *ref) {
}

GCRef *GCMalloc(GC *gc, GCType *type, GCSize_t size) {
  GCContent_p content = malloc(size);
  if (!content) {
    // Mark and Sweep
  }
  GCRef *ref = gcRefAlloc(gc);
  ref->data = (GCData){
      .type = type,
      .size = size,
      .content = content,
  };
  return ref;
}

GCRef *GCPin(GCRef *ref) {
  GC *gc = ref->gc;
  gc->pinned = gcRefListAdd(gc->pinned, ref);
  return ref;
}

GCRef *GCUnpin(GCRef *ref) {
  GC *gc = ref->gc;
  gc->pinned = gcRefListRemove(gc->pinned, ref);
  return ref;
}

GCRef *GCMark(GCRef *ref) {
  GC *gc = ref->gc;
  return ref;
}
