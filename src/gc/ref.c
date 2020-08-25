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
  Entry *entry = ref->entry;
  Marker marker = entry->type->marker;
  if (marker) {
    GC *gc = REF_GC(ref);
    ref->status = kPendingStatus;
    marker(gc, entry->data);
  }
  ref->status = kMarkedStatus;
  return ref;
}
