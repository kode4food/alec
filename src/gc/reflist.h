#pragma once

#include "ref.h"

#ifdef __cplusplus
extern "C" {
#endif

struct RefList {
  Ref *ref;
  RefList *next;
};

RefList *RefListAdd(RefList *list, Ref *ref);
RefList *RefListRemove(RefList *list, Ref *ref);
void RefListDestroy(RefList *list);

#ifdef __cplusplus
}
#endif
