//
// Created by Thomas Bradford on 17.08.20.
//

#include "gc.h"

#include <stdio.h>
#include <stdlib.h>

#include "entry.h"
#include "reflist.h"
#include "refspan.h"

GC *GCInit() {
  return calloc(1, sizeof(GC));
}

static Ref *AllocRef(GC *gc, Entry *entry) {
  // Anything free available?
  RefList *freed = gc->freed;
  if (freed) {
    Ref *ref = freed->ref;
    gc->freed = freed->next;
    *ref = (Ref){
        .status = kInitialStatus,
        .entry = entry,
    };
    return ref;
  }

  // Find a span to allocate from
  RefSpan *span = gc->refs;
  if (!span || span->count == span->capacity) {
    gc->refs = span = RefSpanAlloc(kDefaultSpanSize, span);
  }

  // Allocate from the span
  int idx = span->count++;
  Ref *ref = &(span->refs[idx]);
  *ref = (Ref){
      .gc = (struct GC *) gc,
      .status = kInitialStatus,
      .entry = entry,
  };
  return ref;
}

static void FreeRef(Ref *ref) {
  GC *gc = REF_GC(ref);
  gc->freed = RefListAdd(gc->freed, ref);
}

static void Collect(GC *gc) {
}

static Entry *AllocEntry(GC *gc, Type *type, GCSize_t size) {
  GCSize_t total_size = sizeof(Entry) + size;
  Entry *entry = calloc(1, total_size);
  if (!entry) {
    Collect(gc);
    entry = calloc(1, total_size);
    if (!entry) {
      fprintf(stderr, "out of memory\n");
      exit(-1);
    }
  }
  *entry = (Entry){
      .type = type,
      .size = size,
  };
  return entry;
}

Ref *GCNew(GC *gc, Type *type) {
  return GCNewSized(gc, type, type->default_size);
}

Ref *GCNewSized(GC *gc, Type *type, GCSize_t size) {
  Entry *entry = AllocEntry(gc, type, size);
  Ref *ref = AllocRef(gc, entry);
  return ref;
}

Ref *RefPin(Ref *ref) {
  GC *gc = REF_GC(ref);
  gc->pinned = RefListAdd(gc->pinned, ref);
  return ref;
}

Ref *RefUnpin(Ref *ref) {
  GC *gc = REF_GC(ref);
  gc->pinned = RefListRemove(gc->pinned, ref);
  return ref;
}

Ref *RefMark(Ref *ref) {
  GC *gc = REF_GC(ref);
  return ref;
}
