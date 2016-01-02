cmake_minimum_required (VERSION 3.0)
if (NOT CMAKE_VERSION VERSION_LESS "3.1")
    cmake_policy (SET CMP0054 OLD)
endif ()
if (NOT CMAKE_VERSION VERSION_LESS "3.3")
    cmake_policy (SET CMP0063 NEW)
    set (HONOR_VISIBILITY TRUE)
else ()
    set (HONOR_VISIBILITY FALSE)
endif ()
project (Epoxy VERSION 1.3.1 LANGUAGES C)
set (EPOXY_TARGET_NAME epoxy)
set (TARGET_VER 1.3.1_emscripten)
set (TARGET_ABI_VER 0)
set (TARGET_OUTPUT_NAME "${EPOXY_TARGET_NAME}")

include (GNUInstallDirs)
include (CMakeDependentOption)

set (COMPILER_ID_MSVC MSVC)
set (COMPILER_ID_GCC GNU)
set (COMPILER_ID_CLANG Clang)

if ((CMAKE_C_COMPILER_ID STREQUAL COMPILER_ID_GCC) OR (CMAKE_C_COMPILER_ID STREQUAL COMPILER_ID_CLANG))
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99")
elseif (NOT CMAKE_VERSION VERSION_LESS "3.1")
    set (CMAKE_C_STANDARD_REQUIRED TRUE)
    set (CMAKE_C_STANDARD "99")
endif ()

if ((CMAKE_C_COMPILER_ID STREQUAL COMPILER_ID_GCC) OR (CMAKE_C_COMPILER_ID STREQUAL COMPILER_ID_CLANG))
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-strict-aliasing -Wall -Wextra")
elseif (CMAKE_C_COMPILER_ID STREQUAL COMPILER_ID_MSVC)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W3")
endif ()

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

#find_package (X11)
find_package (PythonInterp)
#find_package (EGL)
#find_package (GLESv1)
#find_package (GLESv2)
find_package (OpenGL)

option (EPOXY_REBUILD_FROM_SPECS "Rebuild the auto-generated sources and headers from the specs" TRUE)
if (EPOXY_REBUILD_FROM_SPECS AND NOT PYTHONINTERP_FOUND)
    message (FATAL_ERROR "You've set \"EPOXY_REBUILD_FROM_SPECS\" to \"TRUE\", which requires a python interpreter, but one couldn't be found.")
endif ()

set (EPOXY_BUILD_SHARED ON)

set (EPOXY_SUPPORT_EGL OFF)
set (EPOXY_SUPPORT_GLX OFF)

configure_file ("include/epoxy/config.h.in" "include/epoxy/config.h")

set (EPOXY_INCLUDE_DIRS  "${CMAKE_CURRENT_SOURCE_DIR}/include"
                         "${CMAKE_CURRENT_BINARY_DIR}/include"
                         "${CMAKE_CURRENT_SOURCE_DIR}/src")

add_subdirectory (src)
