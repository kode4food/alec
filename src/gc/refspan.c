#include "refspan.h"

#include "ref.h"

const Size_t kDefaultSpanSize = 1024;

RefSpan *RefSpanAlloc(Size_t capacity, RefSpan *next) {
  Size_t total_size = sizeof(RefSpan) + (capacity * sizeof(Ref));
  RefSpan *span = malloc(total_size);
  *span = (RefSpan){
      .count = 0,
      .capacity = capacity,
      .next = next,
  };
  return span;
}

RefSpan *RefSpanAllocDefault(RefSpan *next) {
  return RefSpanAlloc(kDefaultSpanSize, next);
}

static void FreeEntries(RefSpan *span) {
  Ref *ref = &(span->refs[0]);
  for (int i = 0; i < span->count; i++, ref++) {
    void *entry = ref->entry;
    if (ref->status != kInit && entry) {
      free(entry);
      ref->entry = NULL;
    }
  }
  span->count = 0;
}

void RefSpanDestroy(RefSpan *span) {
  for (RefSpan *curr = span; curr;) {
    FreeEntries(curr);
    RefSpan *next = curr->next;
    free(curr);
    curr = next;
  }
}
