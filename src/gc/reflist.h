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

/**
 * Deallocates an entire RefList chain, but doesn't touch any of
 * the Refs or their Entries. Those are managed by RefSpans, and
 * will be destroyed by calling RefSpanDestroy.
 *
 * @param list The first RefList in the chain
 */
void RefListDestroy(RefList *list);

#ifdef __cplusplus
}
#endif
