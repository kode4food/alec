#pragma once

#include "ref.h"
#include "typedefs.h"

#ifdef __cplusplus
extern "C" {
#endif

struct RefSpan {
  Size_t count;
  Size_t capacity;
  RefSpan *next;
  Ref refs[];
};

RefSpan *RefSpanAlloc(Size_t capacity, RefSpan *next);
RefSpan *RefSpanAllocDefault(RefSpan *next);

/**
 * Deallocates an entire chain of RefSpans, and frees all of the
 * entries that their Refs point to. This is a destructive function
 * that assumes the collector is being shut-down and doesn't care
 * about whether or not its Refs are being tracked.
 *
 * @param span The first RefSpan in the chain
 */
void RefSpanDestroy(RefSpan *span);

#ifdef __cplusplus
}
#endif
