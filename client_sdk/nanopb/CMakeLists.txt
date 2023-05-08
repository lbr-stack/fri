cmake_minimum_required(VERSION 3.16.3)
project(nanopb
    LANGUAGES C
)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

find_package(ament_cmake REQUIRED)

# Define target
add_library(nanopb
    src/pb_decode.c
    src/pb_encode.c
)

if(MSVC)
    target_compile_options(nanopb
        PRIVATE
            -DPB_SYSTEM_HEADER=<nanopb/pb_syshdr_win.h>
            -DPB_FIELD_16BIT
            -DWIN32
            -DHAVE_STDINT_H
            -DHAVE_STDBOOL_H
    )
else()
    target_compile_options(nanopb
        PRIVATE
            -O2
            -Wall
            -DHAVE_SOCKLEN_T
            -DPB_SYSTEM_HEADER=<nanopb/pb_syshdr.h>
            -DPB_FIELD_16BIT
            -DHAVE_STDINT_H
            -DHAVE_STDDEF_H
            -DHAVE_STDBOOL_H
            -DHAVE_STDLIB_H
            -DHAVE_STRING_H 
    ) 
endif()

# Add include directories for target
target_include_directories(nanopb
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# Export for downstream usage, see https://docs.ros.org/en/foxy/Guides/Ament-CMake-Documentation.html
ament_export_targets(export_nanopb HAS_LIBRARY_TARGET)

install(
    DIRECTORY include/
    DESTINATION include
)

install(
    TARGETS nanopb
    EXPORT export_nanopb
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

ament_package()
