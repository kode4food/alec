//
// Created by Thomas Bradford on 19.08.20.
//

#ifndef ALE_SRC_GC_REFLIST_H_
#define ALE_SRC_GC_REFLIST_H_

#include "ref.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct RefList RefList;

struct RefList {
  Ref *ref;
  RefList *next;
};

RefList *RefListAdd(RefList *list, Ref *ref);
RefList *RefListRemove(RefList *list, Ref *ref);

#ifdef __cplusplus
}
#endif

#endif// ALE_SRC_GC_REFLIST_H_
