//
// Created by Thomas Bradford on 25.08.20.
//

#ifndef ALE_SRC_GC_TYPEDEFS_H_
#define ALE_SRC_GC_TYPEDEFS_H_

#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef uint8_t Byte_t;
typedef size_t Size_t;
typedef Byte_t GCData_t;

// Circular References
typedef struct GC GC;
typedef struct Ref Ref;

#ifdef __cplusplus
}
#endif

#endif//ALE_SRC_GC_TYPEDEFS_H_
