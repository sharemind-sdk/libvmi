#
# This file is a part of the Sharemind framework.
# Copyright (C) Cybernetica AS
#
# All rights are reserved. Reproduction in whole or part is prohibited
# without the written consent of the copyright owner. The usage of this
# code is subject to the appropriate license agreement.
#

CMAKE_MINIMUM_REQUIRED(VERSION "2.8")
PROJECT("SHAREMIND_LIBVMI" "C")

FOREACH(dir IN LISTS CMAKE_PREFIX_PATH)
  INCLUDE_DIRECTORIES(BEFORE SYSTEM "${dir}/include")
ENDFOREACH()

# Find boost - seems to be required since the variables aren't populated otherwise
FIND_PACKAGE(Boost REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})

SET(CMAKE_C_FLAGS "-std=c99 -Wall -Wextra -O2 -fstrict-aliasing -Wstrict-aliasing=1 -fwrapv -Wabi -Wbad-function-cast -Wc++-compat -Wformat -Wswitch-default -Wunused -Wfloat-equal -Wshadow -Wpointer-arith -Wcast-qual -Wstrict-prototypes -Wconversion -Wsign-conversion -Wunused-macros")

INCLUDE(CheckCCompilerFlag)
MACRO(FLAGS_MAGIC flags)
    CHECK_C_COMPILER_FLAG("-${flags}" SHAREMIND_HAS_CFLAGS__${flags})
    IF(SHAREMIND_HAS_CFLAGS__${flags})
        SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -${flags}")
    ENDIF(SHAREMIND_HAS_CFLAGS__${flags})
ENDMACRO(FLAGS_MAGIC)
FLAGS_MAGIC("Weverything")
FLAGS_MAGIC("Wlogical-op")


ADD_DEFINITIONS("-D_XOPEN_SOURCE=500" "-D__STDC_LIMIT_MACROS")


################################################################################
# libvmi
################################################################################

SET(SHAREMIND_LIBVMI_HEADERS "libvmi/instr.h")

IF(NOT SHAREMIND_LIBVM_LINKING_MODE)
    SET(SHAREMIND_LIBVM_LINKING_MODE SHARED)
ENDIF()

ADD_LIBRARY("libvmi" ${SHAREMIND_LIBVM_LINKING_MODE}
            "libvmi/instr.c" ${SHAREMIND_LIBVMI_HEADERS})
ADD_DEPENDENCIES(libvmi m4_instruction_structs_h m4_instruction_index_h)
SET_TARGET_PROPERTIES("libvmi" PROPERTIES
                      OUTPUT_NAME "sharemind_vmi"
                      VERSION "0.1.0.0"
                      SOVERSION "0.1")

INSTALL(TARGETS "libvmi"
        LIBRARY DESTINATION "lib"
        ARCHIVE DESTINATION "lib")

INSTALL(FILES ${SHAREMIND_LIBVMI_HEADERS}
        DESTINATION "include/sharemind/libvmi")
