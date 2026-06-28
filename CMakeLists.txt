cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
find_package(Threads REQUIRED)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
endif()

set(SFML_BUILD_AUDIO OFF CACHE BOOL "Build SFML's Audio module" FORCE)
set(SFML_BUILD_NETWORK OFF CACHE BOOL "Build SFML's Network module" FORCE)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.1.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(fracv src/main.cpp
        src/models/Mandelbrot.h
        src/VisualComputer.h
        src/models/Julia.h
        src/models/BurningShip.h)
target_compile_features(fracv PRIVATE cxx_std_17)

if(MSVC)
    target_compile_options(fracv PRIVATE /O2 /Oi /Ot /fp:fast /arch:AVX2)
else()
    target_compile_options(fracv PRIVATE -O3 -march=native -ffast-math)
endif()

target_link_libraries(fracv PRIVATE SFML::Graphics Threads::Threads)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT fracv)
