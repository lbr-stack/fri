cmake_minimum_required(VERSION 3.1...3.15)

### CMake support for KUKA's Fast Robot Interface library.
if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(apps LANGUAGES CXX)

### Following are some exemplary executables.
### IOAccess
add_executable(ioaccess IOAccess/IOAccessApp.cpp IOAccess/IOAccessClient.cpp)
target_include_directories(ioaccess
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/IOAccess
)

find_package(FRI 1.0.0 REQUIRED) # very nice
target_link_libraries(ioaccess FRI::FRI)

### LBRClientTemplate
add_executable(lbrclienttemplate LBRClientTemplate/MyLBRApp.cpp LBRClientTemplate/MyLBRClient.cpp)
target_include_directories(lbrclienttemplate
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/LBRClientTemplate
)

target_link_libraries(lbrclienttemplate FRI::FRI)

### LBRJointSineOverlay
add_executable(lbrjointsineoverlay LBRJointSineOverlay/LBRJointSineOverlayApp.cpp LBRJointSineOverlay/LBRJointSineOverlayClient.cpp)
target_include_directories(lbrjointsineoverlay
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/LBRJointSineOverlay
)

target_link_libraries(lbrjointsineoverlay FRI::FRI)

### LBRTorqueSineOverlay
add_executable(lbrtorquesineoverlay LBRTorqueSineOverlay/LBRTorqueSineOverlayApp.cpp LBRTorqueSineOverlay/LBRTorqueSineOverlayClient.cpp)
target_include_directories(lbrtorquesineoverlay
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/LBRTorqueSineOverlay
)

target_link_libraries(lbrtorquesineoverlay FRI::FRI)

### LBRWrenchSineOverlay
add_executable(lbrwrenchsineoverlay LBRWrenchSineOverlay/LBRWrenchSineOverlayApp.cpp LBRWrenchSineOverlay/LBRWrenchSineOverlayClient.cpp)
target_include_directories(lbrwrenchsineoverlay
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/LBRWrenchSineOverlay
)

target_link_libraries(lbrwrenchsineoverlay FRI::FRI)

### SimulatedTransformationProvider
add_executable(simulatedtransformationprovider SimulatedTransformationProvider/SimulatedTransformationProviderApp.cpp SimulatedTransformationProvider/SimulatedTransformationProviderClient.cpp)
target_include_directories(simulatedtransformationprovider
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/SimulatedTransformationProvider
)

target_link_libraries(simulatedtransformationprovider FRI::FRI)

### TransformationProvider
add_executable(transformationprovider TransformationProvider/TransformationProviderApp.cpp TransformationProvider/TransformationProviderClient.cpp)
target_include_directories(transformationprovider
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/TransformationProvider
)

target_link_libraries(transformationprovider FRI::FRI)