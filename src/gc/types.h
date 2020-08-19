//
// Created by Thomas Bradford on 19.08.20.
//

#ifndef ALE_SRC_GC_TYPES_H_
#define ALE_SRC_GC_TYPES_H_

#include <stdint.h>

typedef uint8_t GCColor_t;
typedef uint8_t* GCData_t;
typedef uint64_t GCSize_t;

typedef struct GC GC;
typedef struct GCRef GCRef;
typedef struct GCRefList GCRefList;
typedef struct GCRefListScanResult GCRefListScanResult;
typedef struct GCRefSpan GCRefSpan;
typedef struct GCRefType GCRefType;

#endif // ALE_SRC_GC_TYPES_H_
