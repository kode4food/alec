#pragma once

#include "ref.h"
#include "typedefs.h"

#ifdef __cplusplus
extern "C" {
#endif

struct GC {
  GCStatus_t white;
  GCStatus_t black;
  RefSpan *refs;
  RefList *pinned;
  RefList *freed;
  Log *log;
};

GC *GCInit();
Ref *GCNew(GC *gc, Type *type);
Ref *GCNewSized(GC *gc, Type *type, Size_t size);
Size_t GCCollect(GC *gc);
void GCDestroy(GC *gc);

#ifdef __cplusplus
}
#endif
