//
// Created by Thomas Bradford on 17.08.20.
//

#include "gc.h"

#include <stdio.h>
#include <stdlib.h>

#include "object.h"
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

GCRef *gcAllocRef(GC *gc) {
  return NULL;
}

void gcRefFree(GCRef *ref) {
}

void gcCollectGarbage(GC *gc) {
}

GCBuffer_p gcAllocContent(GC *gc, GCSize_t size) {
  GCBuffer_p content = malloc(size);
  if (!content) {
    gcCollectGarbage(gc);
    content = malloc(size);
    if (!content) {
      fprintf(stderr, "out of memory\n");
      exit(-1);
    }
  }
  return content;
}

GCRef *GCMalloc(GC *gc, GCType *type, GCSize_t size) {
  GCBuffer_p content = gcAllocContent(gc, size);
  GCRef *ref = gcAllocRef(gc);
  ref->object = (GCObject){
      .type = type,
      .size = size,
      .buffer = content,
  };
  return ref;
}

GCRef *GCPin(GCRef *ref) {
  GC *gc = RefCollector(ref);
  gc->pinned = gcRefListAdd(gc->pinned, ref);
  return ref;
}

GCRef *GCUnpin(GCRef *ref) {
  GC *gc = RefCollector(ref);
  gc->pinned = gcRefListRemove(gc->pinned, ref);
  return ref;
}

GCRef *GCMark(GCRef *ref) {
  GC *gc = RefCollector(ref);
  return ref;
}
