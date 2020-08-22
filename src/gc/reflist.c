//
// Created by Thomas Bradford on 19.08.20.
//

#include "reflist.h"

#include <stdlib.h>

typedef struct {
  GCRefList *prev;
  GCRefList *curr;
} GCRefListScanResult;

static GCRefListScanResult emptyRefListScanResult = {
    .prev = NULL,
    .curr = NULL,
};

static GCRefListScanResult refListScan(GCRefList *list, GCRef *ref) {
  for (GCRefList *prev, *curr = list; curr; prev = curr, curr = curr->next) {
    if (curr->ref == ref) {
      GCRefListScanResult result;
      result.prev = prev;
      result.curr = curr;
      return result;
    }
  }
  return emptyRefListScanResult;
}

GCRefList *gcRefListAdd(GCRefList *list, GCRef *ref) {
  GCRefList *newList = malloc(sizeof(GCRefList));
  newList->next = list;
  newList->ref = ref;
  return newList;
}

GCRefList *gcRefListRemove(GCRefList *list, GCRef *ref) {
  GCRefListScanResult result = refListScan(list, ref);
  if (!result.curr) {
    return list;
  }
  GCRefList *next = result.curr->next;
  free(result.curr);
  if (!result.prev) {
    return next;
  }
  result.prev->next = next;
  return list;
}
