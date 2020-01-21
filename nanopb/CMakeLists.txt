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

# Add include directories for target
target_include_directories(nanopb
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# Export target
ament_export_interfaces(export_nanopb HAS_LIBRARY_TARGET)

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
