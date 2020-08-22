//
// Created by Thomas Bradford on 17.08.20.
//

#include "gc.h"

#include <stdio.h>
#include <stdlib.h>

#include "entry.h"
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

static GCRef *allocRef(GC *gc) {
  GCRefList *freed = gc->freed;
  if (freed) {
    GCRef *ref = freed->ref;
    gc->freed = freed->next;
    return ref;
  }
  return NULL;
}

static void refFree(GCRef *ref) {
}

static void collectGarbage(GC *gc) {
}

static void *allocData(GC *gc, GCSize_t size) {
  void *ptr = malloc(size);
  if (!ptr) {
    collectGarbage(gc);
    ptr = malloc(size);
    if (!ptr) {
      fprintf(stderr, "out of memory\n");
      exit(-1);
    }
  }
  return ptr;
}

GCRef *GCMalloc(GC *gc, GCType *type, GCSize_t size) {
  void *ptr = allocData(gc, size);
  GCRef *ref = allocRef(gc);
  ref->entry = (GCEntry){
      .type = type,
      .size = size,
      .ptr = ptr,
  };
  return ref;
}

GCRef *GCPin(GCRef *ref) {
  GC *gc = RefGC(ref);
  gc->pinned = gcRefListAdd(gc->pinned, ref);
  return ref;
}

GCRef *GCUnpin(GCRef *ref) {
  GC *gc = RefGC(ref);
  gc->pinned = gcRefListRemove(gc->pinned, ref);
  return ref;
}

GCRef *GCMark(GCRef *ref) {
  GC *gc = RefGC(ref);
  return ref;
}
