//
// Created by Thomas Bradford on 19.08.20.
//

#include <stdlib.h>
#include "refspan.h"

GCRefSpan *gcAllocRefSpan(GCSize_t capacity) {
  GCRefSpan *span = malloc(sizeof(GCRefSpan) + (capacity * sizeof(GCRef)));
  span->count = 0;
  span->capacity = capacity;
  return span;
}