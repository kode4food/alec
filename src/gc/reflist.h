//
// Created by Thomas Bradford on 19.08.20.
//

#ifndef ALE_SRC_GC_REFLIST_H_
#define ALE_SRC_GC_REFLIST_H_

#include <stdbool.h>
#include "ref.h"

typedef struct GCRefList GCRefList;

struct GCRefList {
  GCRef *ref;
  GCRefList *next;
};

typedef struct {
  GCRefList *prev, *curr;
} GCRefListScanResult;

bool gcRefListContains(GCRefList *list, GCRef *ref);
GCRefList *gcRefListAdd(GCRefList *list, GCRef *ref);
struct GCRefListScanResult gcRefListScan(GCRefList *list, GCRef *ref);
GCRefList *gcRefListRemove(GCRefList *list, GCRef *ref);

#endif // ALE_SRC_GC_REFLIST_H_
