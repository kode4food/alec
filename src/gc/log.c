#include "log.h"

Log *LogAlloc(GC *gc) {
  return calloc(1, sizeof(Log));
}

void LogFree(Log *log) {
  for (LogEntry *curr = log->head; curr;) {
    LogEntry *next = curr->next;
    free(curr);
    curr = next;
  }
  free(log);
}

static void LogAppend(Log *log, LogEntry *entry) {
  LogEntry *tail = log->tail;
  if (!tail) {
    log->head = entry;
    log->tail = entry;
    return;
  }
  tail->next = entry;
  log->tail = entry;
}

void LogTraced(Log *log, Ref *target, Ref *existing) {
  LogEntry *entry = malloc(sizeof(LogEntry));
  *entry = (LogEntry){
      .tag = kRefTraced,
      .target = target,
      .existing = existing,
  };
  LogAppend(log, entry);
}

void LogCreated(Log *log, Ref *target) {
  LogEntry *entry = malloc(sizeof(LogEntry));
  *entry = (LogEntry){
      .tag = kRefCreated,
      .target = target,
  };
  LogAppend(log, entry);
}

void LogRead(Log *log, Ref *target, Ref *existing) {
  LogEntry *entry = malloc(sizeof(LogEntry));
  *entry = (LogEntry){
      .tag = kRefRead,
      .target = target,
      .existing = existing,
  };
  LogAppend(log, entry);
}

void LogWritten(Log *log, Ref *target, Ref *existing, Ref *replaced) {
  LogEntry *entry = malloc(sizeof(LogEntry));
  *entry = (LogEntry){
      .tag = kRefWritten,
      .target = target,
      .existing = existing,
      .replaced = replaced,
  };
  LogAppend(log, entry);
}

bool LogConsume(Log *log, LogConsumer consumer, void *context) {
  LogEntry *head = log->head;
  if (!head) {
    return false;
  }
  LogEntry *new_head = log->head = head->next;
  if (!new_head) {
    log->tail = NULL;
  }
  consumer(head, context);
  free(head);
  return true;
}
