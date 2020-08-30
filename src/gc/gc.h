#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "reflist.h"
#include "refspan.h"
#include "type.h"
#include "typedefs.h"

struct GC {
  GCStatus_t white;
  GCStatus_t black;
  RefSpan *refs;
  RefList *pinned;
  RefList *freed;
};

GC *GCInit();
Ref *GCNew(GC *gc, Type *type);
Ref *GCNewSized(GC *gc, Type *type, Size_t size);
Size_t GCCollect(GC *gc);

#ifdef __cplusplus
}
#endif
