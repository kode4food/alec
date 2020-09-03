#include "gc.h"

#include <stdio.h>
#include <stdlib.h>

#include "entry.h"
#include "reflist.h"
#include "refspan.h"
#include "type.h"
#include "typedefs.h"

// Currently stop the world, but the tri-color abstraction is there to
// support concurrent tracing in the future

GC *GCInit() {
  GC *gc = calloc(1, sizeof(GC));
  gc->black = kFlipper1;
  gc->white = kFlipper2;
  return gc;
}

static Ref *AllocFreedRef(GC *gc, Entry *entry) {
  // Anything free available?
  RefList *freed = gc->freed;
  if (!freed) {
    return NULL;
  }

  Ref *ref = freed->ref;
  gc->freed = freed->next;
  // Initial status for a new reference is grey, so that it isn't
  // inadvertently collected before it's properly wired in place
  *ref = (Ref){
      .gc = gc,
      .status = gc->white,
      .entry = entry,
  };
  return ref;
}

static Ref *AllocSpannedRef(GC *gc, Entry *entry) {
  // Find a span to allocate from
  RefSpan *span = gc->refs;
  if (!span || span->count == span->capacity) {
    gc->refs = span = RefSpanAllocDefault(span);
  }

  // Allocate from the span
  int idx = span->count++;
  Ref *ref = &(span->refs[idx]);
  *ref = (Ref){
      .gc = gc,
      .status = gc->white,
      .entry = entry,
  };
  return ref;
}

static Ref *AllocRef(GC *gc, Entry *entry) {
  Ref *ref = AllocFreedRef(gc, entry);
  if (!ref) {
    ref = AllocSpannedRef(gc, entry);
  }
  return ref;
}

static void MarkedPinnedRefs(GC *gc) {
  for (RefList *curr = gc->pinned; curr; curr = curr->next) {
    RefMark(curr->ref);
  }
}

static RefList *MakeListOfStatus(GC *gc, GCStatus_t status) {
  RefList *list = NULL;
  for (RefSpan *span = gc->refs; span; span = span->next) {
    for (int i = 0; i < span->count; i++) {
      Ref *ref = &span->refs[i];
      if (ref->status == status) {
        list = RefListAdd(list, ref);
      }
    }
  }
  return list;
}

static void Finalize(GC *gc, RefList *white) {
  for (RefList *curr = white; curr; curr = curr->next) {
    Entry *entry = curr->ref->entry;
    Finalizer finalizer = entry->type->finalizer;
    if (finalizer) {
      finalizer(gc, entry->data);
    }
  }
}

static Size_t FreeRefs(__unused GC *gc, RefList *white) {
  Size_t freed = 0;
  for (RefList *curr = white; curr; curr = curr->next) {
    Ref *ref = curr->ref;
    freed = freed + ref->entry->size;
    RefFree(ref);
  }
  return freed;
}

static void FlipStatus(GC *gc) {
  // When a collection is complete, we flip the marking values so we
  // don't have to reset all the remaining references
  GCStatus_t hold = gc->black;
  gc->black = gc->white;
  gc->white = hold;
}

Size_t GCCollect(GC *gc) {
  // First perform a complete marking scan starting at the pinned
  // references, then build a list of all the references with white
  // status. After that, finalize those references and free them
  MarkedPinnedRefs(gc);
  RefList *white = MakeListOfStatus(gc, gc->white);
  Finalize(gc, white);
  Size_t freed = FreeRefs(gc, white);
  FlipStatus(gc);
  return freed;
}

static Entry *AllocEntry(GC *gc, Type *type, Size_t size) {
  Size_t total_size = sizeof(Entry) + size;
  Entry *entry = calloc(1, total_size);
  if (!entry) {
    GCCollect(gc);
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

Ref *GCNewSized(GC *gc, Type *type, Size_t size) {
  Entry *entry = AllocEntry(gc, type, size);
  Ref *ref = AllocRef(gc, entry);
  return ref;
}

void GCDestroy(GC *gc) {
  RefSpanDestroy(gc->refs);
  RefListDestroy(gc->freed);
  RefListDestroy(gc->pinned);
  free(gc);
}
