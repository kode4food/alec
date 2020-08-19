//
// Created by Thomas Bradford on 19.08.20.
//

#ifndef ALE_SRC_GC_REFLIST_H_
#define ALE_SRC_GC_REFLIST_H_

#include <stdbool.h>
#include "types.h"
#include "ref.h"

struct GCRefList {
  GCRef *ref;
  GCRefList *next;
};

struct GCRefListScanResult {
  GCRefList *prev, *curr;
};

bool gcRefListContains(GCRefList *list, GCRef *ref);
GCRefList *gcRefListAdd(GCRefList *list, GCRef *ref);
struct GCRefListScanResult gcRefListScan(GCRefList *list, GCRef *ref);
GCRefList *gcRefListRemove(GCRefList *list, GCRef *ref);

#endif // ALE_SRC_GC_REFLIST_H_
