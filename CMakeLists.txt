#
# This file is a part of the Sharemind framework.
# Copyright (C) Cybernetica AS
#
# All rights are reserved. Reproduction in whole or part is prohibited
# without the written consent of the copyright owner. The usage of this
# code is subject to the appropriate license agreement.
#

CMAKE_MINIMUM_REQUIRED(VERSION "2.8.12")
PROJECT("SHAREMIND_LIBVMI" "C")

SET(LIBVMI_VERSION "0.1.0.0")

INCLUDE("${CMAKE_CURRENT_SOURCE_DIR}/config.local" OPTIONAL)
INCLUDE("${CMAKE_CURRENT_BINARY_DIR}/config.local" OPTIONAL)

FOREACH(dir IN LISTS CMAKE_PREFIX_PATH)
  INCLUDE_DIRECTORIES(BEFORE SYSTEM "${dir}/include")
ENDFOREACH()

FIND_PACKAGE(Boost REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})

ADD_COMPILE_OPTIONS(
  "-std=c99" "-O2" "-fwrapv" "-pthread" "-Wall" "-Wextra" "-Wunused" "-Wabi"
  "-Wstrict-aliasing=1" "-Wbad-function-cast" "-Wformat" "-Wswitch-default"
  "-Wfloat-equal" "-Wshadow" "-Wpointer-arith" "-Wcast-qual"
  "-Wstrict-prototypes" "-Wconversion" "-Wsign-conversion" "-Wunused-macros"
  "$<$<NOT:$<STREQUAL:$<CONFIGURATION>,Release>>:-ggdb>"
  "$<$<NOT:$<STREQUAL:$<CONFIGURATION>,Release>>:-fno-omit-frame-pointer>"
  "$<$<STREQUAL:$<CONFIGURATION>,Release>:-DNDEBUG>"
  "$<$<STREQUAL:$<CONFIGURATION>,Release>:-fomit-frame-pointer>"
)

INCLUDE(CheckCCompilerFlag)
FUNCTION(CHECK_ADD_COMPILER_FLAG flag)
    STRING(SUBSTRING "${flag}" 1 -1 FlagName)
    CHECK_C_COMPILER_FLAG("${flag}" C_COMPILER_HAS_${FlagName}_FLAG)
    IF(C_COMPILER_HAS_${FlagName}_FLAG)
        ADD_COMPILE_OPTIONS("${flag}")
    ENDIF()
ENDFUNCTION()
CHECK_ADD_COMPILER_FLAG("-Weverything")
CHECK_ADD_COMPILER_FLAG("-Wlogical-op")

SET(LIBVMI_INSTALL_DEFINITIONS "-D__STDC_LIMIT_MACROS")
ADD_DEFINITIONS("${LIBVMI_INSTALL_DEFINITIONS}")

SET(SHAREMIND_LIBVMI_HEADERS "src/instr.h")

IF(NOT SHAREMIND_LIBVMI_LINKING_MODE)
    SET(SHAREMIND_LIBVMI_LINKING_MODE SHARED)
ENDIF()

ADD_LIBRARY("libvmi" ${SHAREMIND_LIBVMI_LINKING_MODE}
            "src/instr.c" ${SHAREMIND_LIBVMI_HEADERS})
ADD_DEPENDENCIES(libvmi m4_instruction_structs_h m4_instruction_index_h)

SET_TARGET_PROPERTIES("libvmi" PROPERTIES
                      OUTPUT_NAME "sharemind_vmi"
                      VERSION "${LIBVMI_VERSION}"
                      SOVERSION "0.1")

FIND_PROGRAM(LIBVMI_STRIP strip)
IF(NOT LIBVMI_STRIP)
    MESSAGE(WARNING "\"strip\" not found.")
ELSE()
    ADD_CUSTOM_COMMAND(TARGET "libvmi" POST_BUILD COMMAND
                       "${LIBVMI_STRIP}" --strip-all "$<TARGET_FILE:libvmi>"
                       || "${LIBVMI_STRIP}" "$<TARGET_FILE:libvmi>"
                       || "${CMAKE_COMMAND}" -E echo "STRIP FAILED!!!" || true)
ENDIF()

INSTALL(TARGETS "libvmi"
        LIBRARY DESTINATION "lib"
        ARCHIVE DESTINATION "lib")

INSTALL(FILES ${SHAREMIND_LIBVMI_HEADERS}
        DESTINATION "include/sharemind/libvmi")

# Install cmake files:
FILE(GLOB_RECURSE sharemind_libvmi_in_files "${CMAKE_CURRENT_SOURCE_DIR}/*.in")
ADD_CUSTOM_TARGET("include_sharemind_libvmi_in_files_in_IDE"
                  SOURCES ${sharemind_libvmi_in_files})
SET(LIBVMI_INSTALL_LINK_LIBRARIES "-L${CMAKE_INSTALL_PREFIX}/lib"
                                  "-lsharemind_vmi")
SET(LIBVMI_INSTALL_INCLUDE_DIRS "${CMAKE_INSTALL_PREFIX}/include")

CONFIGURE_FILE("${CMAKE_CURRENT_SOURCE_DIR}/SharemindLibvmiConfig.cmake.in"
               "${CMAKE_CURRENT_BINARY_DIR}/SharemindLibvmiConfig.cmake" @ONLY)
CONFIGURE_FILE(
    "${CMAKE_CURRENT_SOURCE_DIR}/SharemindLibvmiConfigVersion.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/SharemindLibvmiConfigVersion.cmake" @ONLY)
INSTALL(FILES "${CMAKE_CURRENT_BINARY_DIR}/SharemindLibvmiConfig.cmake"
              "${CMAKE_CURRENT_BINARY_DIR}/SharemindLibvmiConfigVersion.cmake"
        DESTINATION "lib/SharemindLibvmi")
