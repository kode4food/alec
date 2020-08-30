#!/bin/bash
make -C build all test
fswatch -o src tests | while read filename
do
  make -C build all test
done
