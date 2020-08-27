//
// Created by Thomas Bradford on 19.08.20.
//

#include "ref.h"

#include "gc.h"

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
  if (ref->status == kGrey) {
    return ref;
  }
  Entry *entry = ref->entry;
  Marker marker = entry->type->marker;
  if (marker) {
    ref->status = kGrey;
    marker(gc, entry->data);
  }
  ref->status = gc->black;
  return ref;
}

void RefFree(Ref *ref) {
  free(ref->entry);
  *ref = (Ref){
      .status = kInit,
      .entry = NULL,
  };
  GC *gc = REF_GC(ref);
  gc->freed = RefListAdd(gc->freed, ref);
}
