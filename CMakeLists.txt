# godfather_recomp - ReXGlue Recompiled Project
#
# The SDK package provides rexglue_project and the rexglue_setup_* functions.

cmake_minimum_required(VERSION 3.25)
project(godfather_recomp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (REXSDK_DIR)
  add_subdirectory("${REXSDK_DIR}" rexglue-sdk)
else ()
  find_package(rexglue 0.11.0 REQUIRED CONFIG)
endif ()
rexglue_project(godfather_recomp OUTPUT_DIR generated/default)

# Host sources. src/main.cpp stays on the executable.
set(GODFATHERRECOMP_HOST_SOURCES src/godfather_recomp_hooks.cpp)

# OBJECT and never STATIC, an archive drops the REX_EXPORT symbols.
add_library(godfather_recomp_common OBJECT ${GODFATHERRECOMP_HOST_SOURCES})
rexglue_setup_host_library(godfather_recomp_common)

if (WIN32)
  add_executable(godfather_recomp WIN32 src/main.cpp)
else ()
  add_executable(godfather_recomp src/main.cpp)
endif ()

rexglue_setup_target(godfather_recomp)
target_link_libraries(godfather_recomp PRIVATE godfather_recomp_common)
