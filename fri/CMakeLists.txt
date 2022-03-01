cmake_minimum_required(VERSION 2.8.3)
project(fri)

find_package(catkin REQUIRED COMPONENTS nanopb)

catkin_package(
    INCLUDE_DIRS include
    CATKIN_DEPENDS nanopb
    LIBRARIES fri
)

# Define target
add_library(fri
    src/friClientApplication.cpp
    src/friCommandMessageEncoder.cpp
    src/friLBRClient.cpp
    src/friLBRCommand.cpp
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
        ${catkin_INCLUDE_DIRS}
)

# Link against dependencies
target_link_libraries(fri
    PUBLIC
        ${nanopb_LIBRARIES}
)

# Install
install(
    TARGETS fri
    ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
    LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
)

install(
    DIRECTORY include/${PROJECT_NAME}
    DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
)

