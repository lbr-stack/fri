cmake_minimum_required(VERSION 3.1...3.15)

### CMake support for KUKA's Fast Robot Interface library
if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(apps LANGUAGES CXX)

add_executable(ioaccess IOAccess/IOAccessApp.cpp IOAccessClient.cpp)
target_include_directories(ioaccess
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/IOAccess
)

find_package(FRI 1.0.0 REQUIRED)
target_link_libraries(ioaccess FRI::FRI)