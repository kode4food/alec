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

void RefSpanDestroy(RefSpan *span) {
  for (RefSpan *curr = span; curr;) {
    Ref *ref = &(curr->refs[0]);
    for (int i = 0; i < curr->count; i++, ref++) {
      if (ref->status != kInit) {
        free(ref->entry);
      }
    }
    RefSpan *next = curr->next;
    free(curr);
    curr = next;
  }
}
