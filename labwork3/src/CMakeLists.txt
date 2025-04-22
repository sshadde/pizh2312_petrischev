set(SOURCES
    main.cpp
    args_parser.cpp
    bmp_writer.cpp
    sandpile.cpp
)

add_executable(sandpile ${SOURCES})

target_include_directories(sandpile PRIVATE ${CMAKE_SOURCE_DIR}/lib)
