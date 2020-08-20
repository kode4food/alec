cmake_minimum_required(VERSION 3.17)

set(gc_source_files
        object.h
        gc.c gc.h
        ref.c ref.h
        reflist.c reflist.h
        refspan.c refspan.h)

add_library(gc ${gc_source_files})
