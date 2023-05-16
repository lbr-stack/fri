### CMake support for KUKA's Fast Robot Interface library
cmake_minimum_required(VERSION 3.18)

project(FRI VERSION 2.0.0
        DESCRIPTION "KUKA's Fast Robot Interface."
        LANGUAGES C CXX)

set(FRI_VERSION 1.15)
set(FRI_CLIENT_SDK_NAME FRI-Client-SDK_Cpp)
set(FRI_ARCHIVE ${FRI_CLIENT_SDK_NAME}_v${FRI_VERSION}.zip)
set(NANOPB_VERSION 0.2.8)

option(BUILD_FRI_APPS "Build FRI example applications" OFF)

file(ARCHIVE_EXTRACT
    INPUT ${CMAKE_CURRENT_SOURCE_DIR}/${FRI_ARCHIVE}
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/${FRI_CLIENT_SDK_NAME}
)

# add nanopb target
message(STATUS "Building nanopb version ${NANOPB_VERSION}")

set(NANOPB_SOURCES
    ${FRI_CLIENT_SDK_NAME}/src/nanopb-${NANOPB_VERSION}/pb_decode.c
    ${FRI_CLIENT_SDK_NAME}/src/nanopb-${NANOPB_VERSION}/pb_encode.c
)

add_library(nanopb SHARED
    ${NANOPB_SOURCES}
)

target_include_directories(nanopb
    PUBLIC
        $<INSTALL_INTERFACE:include/nanopb-${NANOPB_VERSION}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${FRI_CLIENT_SDK_NAME}/src/nanopb-${NANOPB_VERSION}>
)

# add fri target
message(STATUS "Building FRI version ${FRI_VERSION}")

file(GLOB_RECURSE FRI_SOURCES RELATIVE ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}/${FRI_CLIENT_SDK_NAME}/src/base/*.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/${FRI_CLIENT_SDK_NAME}/src/client_lbr/*.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/${FRI_CLIENT_SDK_NAME}/src/client_trafo/*.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/${FRI_CLIENT_SDK_NAME}/src/connection/*.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/${FRI_CLIENT_SDK_NAME}/src/protobuf/*.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/${FRI_CLIENT_SDK_NAME}/src/protobuf/*.c
    ${CMAKE_CURRENT_BINARY_DIR}/${FRI_CLIENT_SDK_NAME}/src/protobuf_gen/*.pb.c
)

add_library(fri SHARED
    ${FRI_SOURCES}
)

if(MSVC)
    target_compile_options(fri
        PRIVATE
            -DPB_SYSTEM_HEADER="pb_syshdr_win.h"
            -DPB_FIELD_16BIT
            -DWIN32
            -DHAVE_STDINT_H
            -DHAVE_STDBOOL_H
    )
else()
    target_compile_options(fri
        PRIVATE
            -Ofast
            -DHAVE_SOCKLEN_T
            -DPB_SYSTEM_HEADER="pb_syshdr.h"
            -DPB_FIELD_16BIT
            -DHAVE_STDINT_H
            -DHAVE_STDDEF_H
            -DHAVE_STDBOOL_H
            -DHAVE_STDLIB_H
            -DHAVE_STRING_H
    ) 
endif()

target_include_directories(fri
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${FRI_CLIENT_SDK_NAME}/include>
    PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}/${FRI_CLIENT_SDK_NAME}/src/base
        ${CMAKE_CURRENT_BINARY_DIR}/${FRI_CLIENT_SDK_NAME}/src/protobuf
        ${CMAKE_CURRENT_BINARY_DIR}/${FRI_CLIENT_SDK_NAME}/src/protobuf_gen
)

target_link_libraries(fri
    PRIVATE
        nanopb
)

# build examples
if (BUILD_FRI_APPS)
    function(build_fri_example NAME)
        file(GLOB_RECURSE ${NAME}_SOURCES RELATIVE ${CMAKE_CURRENT_BINARY_DIR}
            ${CMAKE_CURRENT_BINARY_DIR}/${FRI_CLIENT_SDK_NAME}/example/${NAME}/*.cpp
        )

        add_executable(${NAME}App
            ${${NAME}_SOURCES}
        )

        target_include_directories(${NAME}App
            PRIVATE
                ${CMAKE_CURRENT_BINARY_DIR}/${FRI_CLIENT_SDK_NAME}/example/${NAME}
        )

        target_link_libraries(${NAME}App
            PRIVATE
                fri
        )
    endfunction()

    build_fri_example(IOAccess)
    build_fri_example(LBRJointSineOverlay)
    build_fri_example(LBRTorqueSineOverlay)
    build_fri_example(LBRWrenchSineOverlay)
    build_fri_example(SimulatedTransformationProvider)
    build_fri_example(TransformationProvider)
endif(BUILD_FRI_APPS)
