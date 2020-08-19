//
// Created by Thomas Bradford on 19.08.20.
//

#ifndef ALE_SRC_GC_TYPE_H_
#define ALE_SRC_GC_TYPE_H_

#include "types.h"

typedef void (*GCMarker)(GCData_t data);

struct GCRefType {
  GCMarker marker;
};

#endif // ALE_SRC_GC_REFTYPE_H_
