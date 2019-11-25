cmake_minimum_required(VERSION 3.1...3.15)

### CMake support for KUKA's Fast Robot Interface library
if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(libfri VERSION 1.0.0
        DESCRIPTION "KUKA's Fast Robot Interface."
        LANGUAGES C CXX)

### Append CMAKE_MODULE_PATH by custom find file
list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_SOURCE_DIR}/cmake)

### Third party dependency
add_subdirectory(third_party/nanopb)

### Add the Fast Robot Interface libray
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

target_include_directories(fri
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(fri
    PRIVATE
        NanoPB::nanopb # ALIAS library https://cmake.org/cmake/help/v3.10/command/add_library.html#alias-libraries
)

### Install instructions
include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/fri)

install(TARGETS fri
    EXPORT fri-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

### Set exported target's name to FRI
set_target_properties(fri PROPERTIES EXPORT_NAME FRI)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

### Export target to a script
install(EXPORT fri-targets
    FILE FRITargets.cmake
    NAMESPACE FRI::
    DESTINATION ${INSTALL_CONFIGDIR}
)

### Create a ConfigVersion.cmake file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/FRIConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(${CMAKE_CURRENT_LIST_DIR}/cmake/FRIConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/FRIConfig.cmake
    INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)

### Install the config, configversion and custom find modules
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/FRIConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/FRIConfigVersion.cmake
    DESTINATION ${INSTALL_CONFIGDIR}
)

### Export target from the build tree
export(EXPORT fri-targets FILE ${CMAKE_CURRENT_BINARY_DIR}/FRITargets.cmake NAMESPACE FRI)

### Register package in user's package registry
export(PACKAGE FRI)