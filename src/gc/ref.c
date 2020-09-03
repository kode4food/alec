#include "ref.h"

#include "gc.h"
#include "reflist.h"
#include "refspan.h"
#include "type.h"

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
  GC *gc = REF_GC(ref);
  *ref = (Ref){
      .gc = gc,
      .status = kInit,
      .entry = NULL,
  };
  gc->freed = RefListAdd(gc->freed, ref);
}
