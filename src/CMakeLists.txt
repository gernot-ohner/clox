set(LIB_SOURCES
        chunk.c
        debug.c
        memory.c
        value.c
        vm.c
        )

set(MAIN_SOURCES
        main.c
        )

set(HEADERS
        ${CONFIG_HEADER}
        common.h
        chunk.h
        debug.h
        memory.h
        value.h
        vm.h
        )

add_library(clox STATIC ${LIB_SOURCES} ${HEADERS})

add_executable(main ${HEADERS} ${MAIN_SOURCES})
target_link_libraries(main clox)

install(TARGETS clox
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

#TODO I don't understand what this does or how to adjust it to my project
#install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/money.h DESTINATION include)
