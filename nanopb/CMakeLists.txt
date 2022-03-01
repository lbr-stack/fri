cmake_minimum_required(VERSION 2.8.3)
project(nanopb)

find_package(catkin REQUIRED)

catkin_package(
    INCLUDE_DIRS include
    LIBRARIES nanopb
)

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

# Install
install(
    TARGETS nanopb
    ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
    LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
)

install(
    DIRECTORY include/${PROJECT_NAME}
    DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
)
