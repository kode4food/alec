set(gc_source_files
        entry.c entry.h gc.c gc.h log.c log.h ref.c ref.h reflist.c
        reflist.h refspan.c refspan.h type.c type.h typedefs.h)
add_library(gc ${gc_source_files})
