#pragma once

#include "catch.hpp"
#include "gc/log.h"
#include "gc/ref.h"

void TestConsumer(LogEntry *entry, void *context) {
  LogEntry *target = (LogEntry *) context;
  *target = *entry;
}

SCENARIO("Log appends correctly") {
  GIVEN("A newly instantiated Log") {
    Log *log = LogAlloc();
    REQUIRE(log != NULL);

    WHEN("Log entries are added") {
      Ref ref;
      LogEntry entry;
      LogCreated(log, &ref);
      LogRead(log, &ref, &ref);

      THEN("The first should come back as a Creation") {
        bool consumed = LogConsume(log, TestConsumer, &entry);
        REQUIRE(consumed);
        REQUIRE(entry.tag == kRefCreated);
        REQUIRE(entry.target == &ref);

        AND_THEN("The second should come back as a Read") {
          consumed = LogConsume(log, TestConsumer, &entry);
          REQUIRE(consumed);
          REQUIRE(entry.tag == kRefRead);
          REQUIRE(entry.target == &ref);

          AND_THEN("The log should be empty") {
            consumed = LogConsume(log, TestConsumer, &entry);
            REQUIRE_FALSE(consumed);
          }
        }
      }
    }

    LogFree(log);
  }
}
