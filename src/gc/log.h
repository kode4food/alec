#pragma once

#include <stdbool.h>

#include "typedefs.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  // Collector Entries
  kRefTraced,
  // Mutator Entries
  kRefCreated,
  kRefRead,
  kRefWritten,
} LogTag_t;

struct LogEntry {
  LogTag_t tag;
  Ref *target;
  Ref *existing;
  Ref *replaced;
  struct LogEntry *prev;
  struct LogEntry *next;
};

struct Log {
  LogEntry *head;
  LogEntry *tail;
};

typedef void (*LogConsumer)(LogEntry *entry, void *ctx);

Log *LogAlloc();
void LogTraced(Log *log, Ref *target, Ref *existing);
void LogCreated(Log *log, Ref *target);
void LogRead(Log *log, Ref *target, Ref *existing);
void LogWritten(Log *log, Ref *target, Ref *existing, Ref *replaced);
bool LogConsume(Log *log, LogConsumer consumer, void *ctx);
void LogFree(Log *log);

#ifdef __cplusplus
}
#endif
