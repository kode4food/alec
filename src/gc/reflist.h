#pragma once

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
