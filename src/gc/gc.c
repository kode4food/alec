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
  return calloc(1, sizeof(GC));
}

static GCRef *allocRef(GC *gc, GCEntry *entry) {
  // Anything free available?
  GCRefList *freed = gc->freed;
  if (freed) {
    GCRef *ref = freed->ref;
    gc->freed = freed->next;
    *ref = (GCRef){
        .status = GCInitialStatus,
        .entry = entry,
    };
    return ref;
  }

  // Find a span to allocate from
  GCRefSpan *span = gc->refs;
  if (!span || span->count == span->capacity) {
    gc->refs = span = gcAllocRefSpan(defaultSpanSize, span);
  }

  // Allocate from the span
  int idx = span->count++;
  GCRef *ref = &(span->refs[idx]);
  *ref = (GCRef){
      .gc = gc,
      .status = GCInitialStatus,
      .entry = entry,
  };
  return ref;
}

static void refFree(GCRef *ref) {
  GC *gc = RefGC(ref);
  gc->freed = gcRefListAdd(gc->freed, ref);
}

static void collectGarbage(GC *gc) {
}

static GCEntry *allocEntry(GC *gc, GCType *type, GCSize_t size) {
  GCSize_t totalSize = sizeof(GCEntry) + size;
  GCEntry *entry = calloc(1, totalSize);
  if (!entry) {
    collectGarbage(gc);
    entry = calloc(1, totalSize);
    if (!entry) {
      fprintf(stderr, "out of memory\n");
      exit(-1);
    }
  }
  *entry = (GCEntry){
      .type = type,
      .size = size,
  };
  return entry;
}

GCRef *GCMalloc(GC *gc, GCType *type, GCSize_t size) {
  GCEntry *entry = allocEntry(gc, type, size);
  GCRef *ref = allocRef(gc, entry);
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
