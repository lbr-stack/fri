cmake_minimum_required(VERSION 3.10.2)
project(fri
    LANGUAGES C CXX
)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

find_package(ament_cmake REQUIRED)
find_package(nanopb REQUIRED)

# Define target
add_library(fri
    src/friClientApplication.cpp
    src/friCommandMessageEncoder.cpp
    src/friLBRClient.cpp
    src/friLBRCommand.cpp
    src/friLBRState.cpp
    src/friLBRState.cpp
    src/FRIMessages.pb.c
    src/friMonitoringMessageDecoder.cpp
    src/friTransformationClient.cpp
    src/friUdpConnection.cpp
    src/pb_frimessages_callbacks.c
)

# Add compile options
if(MSVC)
    target_compile_options(fri
        PRIVATE
            -DPB_SYSTEM_HEADER=<nanopb/pb_syshdr_win.h>
            -DPB_FIELD_16BIT
            -DWIN32
            -DHAVE_STDINT_H
            -DHAVE_STDBOOL_H
    )
else()
    target_compile_options(fri
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
target_include_directories(fri
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Link against dependencies
ament_target_dependencies(fri nanopb)

# Export target
install(
    TARGETS fri
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    INCLUDES DESTINATION include
)

ament_export_include_directories(include)
ament_export_libraries(fri)
ament_export_dependencies(nanopb)

install(
    DIRECTORY include/
    DESTINATION include
)



ament_package()
