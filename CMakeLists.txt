####################################################################
# cmake support for KUKA's Fast Robot Interface (FRI) client library
####################################################################
cmake_minimum_required(VERSION 3.18)

project(FRIClient VERSION 1.0.0
        DESCRIPTION "KUKA's Fast Robot Interface client library."
        LANGUAGES C CXX)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type." FORCE)
endif()

######################
# variable definitions
######################
set(FRIClient_SDK_NAME "FRI-Client-SDK_Cpp")
option(BUILD_FRI_APPS "Build FRIClient example applications" OFF)

#########################################
# extract the FRIClient from the zip file
#########################################
file(ARCHIVE_EXTRACT
    INPUT ${CMAKE_CURRENT_SOURCE_DIR}/${FRIClient_SDK_NAME}.zip
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/${FRIClient_SDK_NAME}
)

#######################
# find library versions
#######################
# try to find nanopb version
file(GLOB NANOPB_HEADER_PATH ${CMAKE_CURRENT_BINARY_DIR}/${FRIClient_SDK_NAME}/src/nanopb-*/pb.h)
file(READ ${NANOPB_HEADER_PATH} NANOPB_HEADER)
string(REGEX MATCH "NANOPB_VERSION nanopb-([0-9]*).([0-9]*).([0-9]*)" _ ${NANOPB_HEADER})

set(NANOPB_VERSION_MAJOR ${CMAKE_MATCH_1})
set(NANOPB_VERSION_MINOR ${CMAKE_MATCH_2})
set(NANOPB_VERSION_PATCH ${CMAKE_MATCH_3})
set(NANOPB_VERSION ${NANOPB_VERSION_MAJOR}.${NANOPB_VERSION_MINOR}.${NANOPB_VERSION_PATCH})

message("Found nanopb of version: " ${NANOPB_VERSION})

# #13: Windows support
# if (MSVC)
#     set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
# endif()

# try to find FRIClient version
file(READ ${CMAKE_CURRENT_BINARY_DIR}/${FRIClient_SDK_NAME}/include/friClientIf.h FRI_CLIENT_IF_HEADER)
string(REGEX MATCH "version \\{([0-9]+)\\.([0-9]+)" _ ${FRI_CLIENT_IF_HEADER})

set(FRI_CLIENT_VERSION_MAJOR ${CMAKE_MATCH_1})
set(FRI_CLIENT_VERSION_MINOR ${CMAKE_MATCH_2})
set(FRI_CLIENT_VERSION ${FRI_CLIENT_VERSION_MAJOR}.${FRI_CLIENT_VERSION_MINOR})

if (NOT FRI_CLIENT_VERSION STREQUAL "1.15")
    message(FATAL_ERROR "Expected FRIClient version 1.15, found: " ${FRI_CLIENT_VERSION})
endif()

message("Found FRIClient of version: " ${FRI_CLIENT_VERSION})

# create version header
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/friClientVersion.h.in ${CMAKE_CURRENT_BINARY_DIR}/${FRIClient_SDK_NAME}/include/friClientVersion.h
)

#################################
# define FRIClient library target
#################################
message(STATUS "Configuring FRIClient version ${FRI_CLIENT_VERSION}")
file(GLOB_RECURSE NANOPB_SOURCES RELATIVE ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}/${FRIClient_SDK_NAME}/src/nanopb-${NANOPB_VERSION}/*.c
)

file(GLOB_RECURSE PROTOBUF_SOURCES RELATIVE ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}/${FRIClient_SDK_NAME}/src/protobuf/*.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/${FRIClient_SDK_NAME}/src/protobuf/*.c
    ${CMAKE_CURRENT_BINARY_DIR}/${FRIClient_SDK_NAME}/src/protobuf_gen/*.pb.c
)

file(GLOB_RECURSE FRI_SOURCES RELATIVE ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}/${FRIClient_SDK_NAME}/src/base/*.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/${FRIClient_SDK_NAME}/src/client_lbr/*.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/${FRIClient_SDK_NAME}/src/client_trafo/*.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/${FRIClient_SDK_NAME}/src/connection/*.cpp
)
    
# add nanopb library target under common namespace
add_library(nanopb SHARED
    ${NANOPB_SOURCES}
)

# add protocol buffers and utilities under common namespace
add_library(protobuf SHARED
    ${PROTOBUF_SOURCES}
)

# add FRI library target
add_library(FRIClient SHARED
    ${FRI_SOURCES}
)

add_library(FRIClient::nanopb ALIAS nanopb) # alias for anyone adding this as a submodule
add_library(FRIClient::protobuf ALIAS protobuf) # alias for anyone adding this as a submodule
add_library(FRIClient::FRIClient ALIAS FRIClient) # alias for anyone adding this as a submodule

target_include_directories(nanopb
    PUBLIC
        $<INSTALL_INTERFACE:${FRIClient_SDK_NAME}/src/nanopb-${NANOPB_VERSION}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${FRIClient_SDK_NAME}/src/nanopb-${NANOPB_VERSION}>
)

target_include_directories(protobuf
    PUBLIC
        $<INSTALL_INTERFACE:${FRIClient_SDK_NAME}/src/protobuf_gen>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${FRIClient_SDK_NAME}/src/protobuf_gen>
        $<INSTALL_INTERFACE:${FRIClient_SDK_NAME}/src/protobuf>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${FRIClient_SDK_NAME}/src/protobuf>
)

target_include_directories(FRIClient
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${FRIClient_SDK_NAME}/include>
    PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}/${FRIClient_SDK_NAME}/src/base
)

target_link_libraries(protobuf
    PRIVATE
        nanopb
)

target_link_libraries(FRIClient
    PRIVATE
        nanopb
        protobuf
)

if(MSVC)
    target_compile_options(nanopb
        PRIVATE
            -DPB_SYSTEM_HEADER="pb_syshdr_win.h"
            -DPB_FIELD_16BIT
            -DWIN32
            -DHAVE_STDINT_H
            -DHAVE_STDBOOL_H
    )
    target_compile_options(protobuf
        PRIVATE
            -DPB_FIELD_16BIT
    )
    target_compile_options(FRIClient
        PRIVATE
            -DWIN32
    )
else()
    target_compile_options(nanopb
        PRIVATE
            -Wall
            -O2
            -DPB_SYSTEM_HEADER="pb_syshdr.h"
            -DPB_FIELD_16BIT
            -DHAVE_STDINT_H
            -DHAVE_STDDEF_H
            -DHAVE_STDBOOL_H
            -DHAVE_STDLIB_H
            -DHAVE_STRING_H
    )
    target_compile_options(protobuf
        PRIVATE
            -Wall
            -O2
            -DPB_FIELD_16BIT
    )
    target_compile_options(FRIClient
        PRIVATE
            -Wall
            -O2
            -DHAVE_SOCKLEN_T
    ) 
endif()

#################
# install targets
#################
include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/FRIClientConfigVersion.cmake"
    VERSION ${FRI_CLIENT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(TARGETS nanopb protobuf FRIClient
    EXPORT FRIClientTargets
    LIBRARY DESTINATION lib
    INCLUDES DESTINATION include
)

install(
    DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${FRIClient_SDK_NAME}/src/protobuf_gen/
    DESTINATION include
    FILES_MATCHING
        PATTERN *.h
)

install(
    DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${FRIClient_SDK_NAME}/src/protobuf/
    DESTINATION include
    FILES_MATCHING
        PATTERN *.h
)

install(
    DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${FRIClient_SDK_NAME}/src/nanopb-${NANOPB_VERSION}/
    DESTINATION include
    FILES_MATCHING
        PATTERN *.h
)

install(
    DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${FRIClient_SDK_NAME}/include/
    DESTINATION include
)

install(EXPORT FRIClientTargets
    FILE FRIClientConfig.cmake
    NAMESPACE FRIClient::
    DESTINATION lib/cmake/FRIClient
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/FRIClientConfigVersion.cmake
    DESTINATION lib/cmake/FRIClient
)

################
# build examples
################
if (BUILD_FRI_APPS)
    function(build_fri_example NAME)
        file(GLOB_RECURSE ${NAME}_SOURCES RELATIVE ${CMAKE_CURRENT_BINARY_DIR}
            ${CMAKE_CURRENT_BINARY_DIR}/${FRIClient_SDK_NAME}/example/${NAME}/*.cpp
        )

        add_executable(${NAME}App
            ${${NAME}_SOURCES}
        )

        target_include_directories(${NAME}App
            PRIVATE
                ${CMAKE_CURRENT_BINARY_DIR}/${FRIClient_SDK_NAME}/example/${NAME}
        )

        target_link_libraries(${NAME}App
            PRIVATE
                FRIClient
        )
    endfunction()

    build_fri_example(IOAccess)
    build_fri_example(LBRJointSineOverlay)
    build_fri_example(LBRTorqueSineOverlay)
    build_fri_example(LBRWrenchSineOverlay)
    build_fri_example(SimulatedTransformationProvider)
    build_fri_example(TransformationProvider)
endif(BUILD_FRI_APPS)
