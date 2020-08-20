//
// Created by Thomas Bradford on 19.08.20.
//

#include "reflist.h"

#include <stdlib.h>

struct GCRefListScanResult emptyRefListScanResult;

bool gcRefListContains(GCRefList *list, GCRef *ref) {
  for (GCRefList *curr = list; curr; curr = curr->next) {
    if (curr->ref == ref) {
      return true;
    }
  }
  return false;
}

GCRefList *gcRefListAdd(GCRefList *list, GCRef *ref) {
  GCRefList *newList = malloc(sizeof(GCRefList));
  newList->next = list;
  newList->ref = ref;
  return newList;
}

struct GCRefListScanResult emptyRefListScanResult;

struct GCRefListScanResult gcRefListScan(GCRefList *list, GCRef *ref) {
  for (GCRefList *prev, *curr = list; curr; prev = curr, curr = curr->next) {
    if (curr->ref == ref) {
      struct GCRefListScanResult result;
      result.prev = prev;
      result.curr = curr;
      return result;
    }
  }
  return emptyRefListScanResult;
}

GCRefList *gcRefListRemove(GCRefList *list, GCRef *ref) {
  struct GCRefListScanResult result = gcRefListScan(list, ref);
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
