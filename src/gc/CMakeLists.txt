set(gc_src
        entry.c entry.h gc.c gc.h log.c log.h ref.c ref.h reflist.c
        reflist.h refspan.c refspan.h type.c type.h typedefs.h)
add_library(gc ${gc_src})

if(BUILD_TESTING)
    add_subdirectory(__tests__)
endif()
