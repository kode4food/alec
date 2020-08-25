//
// Created by Thomas Bradford on 19.08.20.
//

#ifndef ALE_SRC_GC_REFLIST_H_
#define ALE_SRC_GC_REFLIST_H_

#include <stdbool.h>
#include <stdlib.h>

#include "ref.h"

typedef struct RefList RefList;

struct RefList {
  Ref *ref;
  RefList *next;
};

const RefList *kEmptyRefList = NULL;

RefList *RefListAdd(RefList *list, Ref *ref);
RefList *RefListRemove(RefList *list, Ref *ref);

#endif// ALE_SRC_GC_REFLIST_H_
