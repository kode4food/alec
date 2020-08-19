//
// Created by Thomas Bradford on 17.08.20.
//

#include <stdbool.h>
#include <stdlib.h>

#include "gc.h"
#include "reflist.h"
#include "refspan.h"

GC *InitGC() {
  GC *gc = malloc(sizeof(GC));
  gc->black = GC_Gray - 1;
  gc->white = GC_Gray + 1;
  gc->refs = gcAllocRefSpan(defaultSpanSize);
  gc->pinned = NULL;
  gc->freed = NULL;
  return gc;
}

GCRef *gcRefAlloc(GC *gc) {

}

void gcRefFree(GCRef *ref) {

}

GCRef *GCMalloc(GC *gc, GCRefType *type, GCSize_t size) {
  GCData_t data = malloc(size);
  if (!data) {
    // Mark and Sweep
  }
  GCRef *ref = gcRefAlloc(gc);
  ref->type = type;
  ref->data = data;
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
