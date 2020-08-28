//
// Created by Thomas Bradford on 19.08.20.
//

#include "reflist.h"

const RefList *kEmptyRefList = NULL;

typedef struct {
  RefList *prev;
  RefList *curr;
} RefListScanResult;

static RefListScanResult emptyRefListScanResult = {
    .prev = NULL,
    .curr = NULL,
};

static RefListScanResult Scan(RefList *list, Ref *ref) {
  RefList *prev = NULL;
  RefList *curr = list;
  while (curr) {
    if (curr->ref == ref) {
      RefListScanResult result;
      result.prev = prev;
      result.curr = curr;
      return result;
    }
    prev = curr;
    curr = curr->next;
  }
  return emptyRefListScanResult;
}

RefList *RefListAdd(RefList *list, Ref *ref) {
  RefList *newList = malloc(sizeof(RefList));
  *newList = (RefList){
      .next = list,
      .ref = ref,
  };
  return newList;
}

RefList *RefListRemove(RefList *list, Ref *ref) {
  RefListScanResult result = Scan(list, ref);
  if (result.curr) {
    RefList *next = result.curr->next;
    free(result.curr);
    if (!result.prev) {
      return next;
    }
    result.prev->next = next;
  }
  return list;
}
