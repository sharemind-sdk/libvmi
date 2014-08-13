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

FOREACH(dir IN LISTS CMAKE_PREFIX_PATH)
  INCLUDE_DIRECTORIES(BEFORE SYSTEM "${dir}/include")
ENDFOREACH()
INCLUDE_DIRECTORIES(BEFORE SYSTEM "${CMAKE_CURRENT_SOURCE_DIR}/../")

ADD_COMPILE_OPTIONS(
  "-O2"
  "$<$<STREQUAL:$<CONFIGURATION>,Release>:-DNDEBUG>"
  "$<$<STREQUAL:$<CONFIGURATION>,Release>:-fomit-frame-pointer>"
)

# Find boost - seems to be required since the variables aren't populated otherwise
FIND_PACKAGE(Boost REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})

SET(CMAKE_C_FLAGS "-std=c99 -Wall -Wextra -fstrict-aliasing -Wstrict-aliasing=1 -fwrapv -Wabi -Wbad-function-cast -Wc++-compat -Wformat -Wswitch-default -Wunused -Wfloat-equal -Wshadow -Wpointer-arith -Wcast-qual -Wstrict-prototypes -Wconversion -Wsign-conversion -Wunused-macros")

INCLUDE(CheckCCompilerFlag)
MACRO(FLAGS_MAGIC flags)
    CHECK_C_COMPILER_FLAG("-${flags}" SHAREMIND_HAS_CFLAGS__${flags})
    IF(SHAREMIND_HAS_CFLAGS__${flags})
        SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -${flags}")
    ENDIF(SHAREMIND_HAS_CFLAGS__${flags})
ENDMACRO(FLAGS_MAGIC)
FLAGS_MAGIC("Weverything")
FLAGS_MAGIC("Wlogical-op")

SET(LIBVMI_INSTALL_DEFINITIONS "-D__STDC_LIMIT_MACROS")
ADD_DEFINITIONS("${LIBVMI_INSTALL_DEFINITIONS}")


################################################################################
# libvmi
################################################################################

SET(SHAREMIND_LIBVMI_HEADERS "src/instr.h")

IF(NOT SHAREMIND_LIBVMI_LINKING_MODE)
    SET(SHAREMIND_LIBVMI_LINKING_MODE SHARED)
ENDIF()

ADD_LIBRARY("libvmi" ${SHAREMIND_LIBVMI_LINKING_MODE}
            "src/instr.c" ${SHAREMIND_LIBVMI_HEADERS})
ADD_DEPENDENCIES(libvmi m4_instruction_structs_h m4_instruction_index_h)

SET(LIBVMI_VERSION "0.1.0.0")
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
ADD_CUSTOM_TARGET("include_sharemind_libvmi_in_files_in_IDE" SOURCES ${sharemind_libvmi_in_files})
SET(LIBVMI_INSTALL_LINK_LIBRARIES "-L${CMAKE_INSTALL_PREFIX}/lib" "-lsharemind_vmi")
SET(LIBVMI_INSTALL_INCLUDE_DIRS "${CMAKE_INSTALL_PREFIX}/include")

CONFIGURE_FILE("${CMAKE_CURRENT_SOURCE_DIR}/SharemindLibvmiConfig.cmake.in"
               "${CMAKE_CURRENT_BINARY_DIR}/SharemindLibvmiConfig.cmake" @ONLY)
CONFIGURE_FILE("${CMAKE_CURRENT_SOURCE_DIR}/SharemindLibvmiConfigVersion.cmake.in"
               "${CMAKE_CURRENT_BINARY_DIR}/SharemindLibvmiConfigVersion.cmake" @ONLY)
INSTALL(FILES "${CMAKE_CURRENT_BINARY_DIR}/SharemindLibvmiConfig.cmake"
              "${CMAKE_CURRENT_BINARY_DIR}/SharemindLibvmiConfigVersion.cmake"
        DESTINATION "lib/SharemindLibvmi")
