cmake_minimum_required(VERSION 3.10.2)
project(nanopb
    LANGUAGES C
)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
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

# Export target
install(
    TARGETS nanopb
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

ament_export_include_directories(include)
ament_export_libraries(nanopb)

install(
    DIRECTORY include/
    DESTINATION include
)

ament_package()
