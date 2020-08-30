#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "gc.h"
#include "ref.h"

typedef enum {
  // Collector Entries
  kRefTraced,
  // Mutator Entries
  kRefCreated,
  kRefRead,
  kRefWritten,
} LogTag_t;

typedef struct LogEntry {
  LogTag_t tag;
  Ref *target;
  Ref *existing;
  Ref *replaced;
  struct LogEntry *prev;
  struct LogEntry *next;
} LogEntry;

typedef struct Log {
  LogEntry *head;
  LogEntry *tail;
} Log;

typedef void (*LogConsumer)(LogEntry *entry, void *ctx);

Log *LogAlloc();
void LogFree(Log *log);
void LogTraced(Log *log, Ref *target, Ref *existing);
void LogCreated(Log *log, Ref *target);
void LogRead(Log *log, Ref *target, Ref *existing);
void LogWritten(Log *log, Ref *target, Ref *existing, Ref *replaced);
bool LogConsume(Log *log, LogConsumer consumer, void *ctx);

#ifdef __cplusplus
}
#endif
