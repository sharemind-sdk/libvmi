#
# This file is a part of the Sharemind framework.
# Copyright (C) Cybernetica AS
#
# All rights are reserved. Reproduction in whole or part is prohibited
# without the written consent of the copyright owner. The usage of this
# code is subject to the appropriate license agreement.
#

CMAKE_MINIMUM_REQUIRED(VERSION "2.8")
CMAKE_POLICY(SET CMP0015 NEW)
PROJECT("SHAREMIND_LIBVMI" "C")

IF(NOT SHAREMIND_LIB_DIR)
    MESSAGE(FATAL_ERROR "SHAREMIND_LIB_DIR not defined!")
ENDIF(NOT SHAREMIND_LIB_DIR)

IF(NOT SHAREMIND_INCLUDE_DESTINATION)
    MESSAGE(FATAL_ERROR "SHAREMIND_INCLUDE_DESTINATION not defined!")
ENDIF(NOT SHAREMIND_INCLUDE_DESTINATION)

IF(NOT SHAREMIND_GEN_DIR)
    MESSAGE(FATAL_ERROR "SHAREMIND_GEN_DIR not defined!")
ENDIF(NOT SHAREMIND_GEN_DIR)

IF(NOT SHAREMIND_EXT_VM_GLOBALS_DIR)
    SET(SHAREMIND_EXT_VM_GLOBALS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../ext/vm_globals")
ENDIF(NOT SHAREMIND_EXT_VM_GLOBALS_DIR)
IF(NOT EXISTS "${SHAREMIND_EXT_VM_GLOBALS_DIR}/include/sharemind/CMakeLists.txt")
    MESSAGE(FATAL "SHAREMIND_EXT_VM_GLOBALS_DIR is invalid!")
ENDIF()

IF(NOT SHAREMIND_EXT_VM_M4_DIR)
    SET(SHAREMIND_EXT_VM_M4_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../ext/vm_m4")
ENDIF(NOT SHAREMIND_EXT_VM_M4_DIR)
IF(NOT EXISTS "${SHAREMIND_EXT_VM_M4_DIR}/src/sharemind/CMakeLists.txt")
    MESSAGE(FATAL "SHAREMIND_EXT_VM_M4_DIR is invalid!")
ENDIF()

INCLUDE_DIRECTORIES(BEFORE SYSTEM "${CMAKE_CURRENT_SOURCE_DIR}/../sharemind/.."
                                  "${SHAREMIND_GEN_DIR}"
                                  "${SHAREMIND_EXT_VM_GLOBALS_DIR}/include")

IF(NOT SHAREMIND_VM_M4_SOURCE_DIR)
    ADD_SUBDIRECTORY("${SHAREMIND_EXT_VM_M4_DIR}/src/sharemind" "${SHAREMIND_EXT_DIR}/vm_m4")
ENDIF(NOT SHAREMIND_VM_M4_SOURCE_DIR)

IF(NOT M4_DIR_B)
    SET(M4_DIR_B "${SHAREMIND_GEN_DIR}/sharemind/m4")
ENDIF(NOT M4_DIR_B)

SET(CMAKE_C_FLAGS "-std=gnu99 -Wall -Wextra -O2 -fstrict-aliasing -Wstrict-aliasing=1 -fwrapv -Wabi -Wbad-function-cast -Wc++-compat -Wformat -Wswitch-default -Wunused -Wfloat-equal -Wshadow -Wpointer-arith -Wcast-qual -Wstrict-prototypes -Wconversion -Wsign-conversion -Wlogical-op -Wunused-macros")
SET(CMAKE_CXX_FLAGS "-std=gnu++98 -Wall -Wextra -O2 -fstrict-aliasing -Wstrict-aliasing=1 -fwrapv -Wabi -Wformat -Wswitch-default -Wunused -Wfloat-equal -Wshadow -Wpointer-arith -Wcast-qual -Wconversion -Wsign-conversion -Wlogical-op -Wunused-macros")
ADD_DEFINITIONS("-D_XOPEN_SOURCE=500" "-D__STDC_LIMIT_MACROS")


################################################################################
# libvmi
################################################################################

ADD_LIBRARY("libvmi" SHARED "libvmi/instr.c")
ADD_DEPENDENCIES(libvmi m4_instruction_structs_h m4_instruction_index_h)
SET_TARGET_PROPERTIES("libvmi" PROPERTIES
                      OUTPUT_NAME "sharemind_vmi"
                      LIBRARY_OUTPUT_DIRECTORY "${SHAREMIND_LIB_DIR}"
                      VERSION "0.1.0.0"
                      SOVERSION "0.1")
INSTALL(DIRECTORY "libvmi/"
        DESTINATION "${SHAREMIND_INCLUDE_DESTINATION}/libvmi"
        FILES_MATCHING PATTERN "*.h")

INSTALL(TARGETS "libvmi"
        RUNTIME DESTINATION "bin"
        LIBRARY DESTINATION "lib"
        PUBLIC_HEADER DESTINATION "include")
