#
# Copyright (C) 2015 Cybernetica
#
# Research/Commercial License Usage
# Licensees holding a valid Research License or Commercial License
# for the Software may use this file according to the written
# agreement between you and Cybernetica.
#
# GNU General Public License Usage
# Alternatively, this file may be used under the terms of the GNU
# General Public License version 3.0 as published by the Free Software
# Foundation and appearing in the file LICENSE.GPL included in the
# packaging of this file.  Please review the following information to
# ensure the GNU General Public License version 3.0 requirements will be
# met: http://www.gnu.org/copyleft/gpl-3.0.html.
#
# For further information, please contact us at sharemind@cyber.ee.
#

CMAKE_MINIMUM_REQUIRED(VERSION "3.0")
PROJECT(SharemindLibVmi VERSION "0.1.0" LANGUAGES "C")

INCLUDE("${CMAKE_CURRENT_SOURCE_DIR}/config.local" OPTIONAL)
INCLUDE("${CMAKE_CURRENT_BINARY_DIR}/config.local" OPTIONAL)

FIND_PACKAGE(SharemindCMakeHelpers REQUIRED)

SharemindSetProjectVersion()

FIND_PACKAGE(SharemindVmM4 REQUIRED)

SharemindSetC99CompileOptions()

FILE(GLOB_RECURSE SharemindLibVmi_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")
FILE(GLOB_RECURSE SharemindLibVmi_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")

SharemindAddSharedLibrary("libvmi"
    OUTPUT_NAME "sharemind_vmi"
    SOURCES ${SharemindLibVmi_SOURCES} ${SharemindLibVmi_HEADERS}
    INCLUDE_DIRECTORIES
        ${SharemindVmM4_INCLUDE_DIRS}
    LEGACY_DEFINITIONS
        ${SharemindVmM4_DEFINITIONS}
)

INSTALL(FILES ${SharemindLibVmi_HEADERS}
        DESTINATION "include/sharemind/libvmi"
        COMPONENT "dev")

# Install cmake files:
SharemindCreateCMakeFindFiles(
    INCLUDE_DIRS
        "${CMAKE_INSTALL_PREFIX}/include"
    LIBRARIES
        "-L${CMAKE_INSTALL_PREFIX}/lib"
        "-lsharemind_vmi"
)

# Packaging:
SharemindSetupPackaging()
SharemindAddComponentPackage("lib"
    NAME "libsharemind-vmi"
    DESCRIPTION "Sharemind VM Instructions library"
    DEB_SECTION "libs"
    DEB_DEPENDS "libc6 (>= 2.19)"
)
SharemindAddComponentPackage("dev"
    NAME "libsharemind-vmi-dev"
    DESCRIPTION "Sharemind VM Instructions library development headers"
    DEB_SECTION "libdevel"
    DEB_DEPENDS
        "libsharemind-vmi (= ${SharemindLibVmi_VERSION})"
        "libsharemind-cheaders-dev (>= 0.1.0)"
        "libc6-dev (>= 2.19)"
)
SharemindAddComponentPackage("debug"
    NAME "libsharemind-vmi-dbg"
    DESCRIPTION "Sharemind VM Instructions library debug symbols"
    DEB_SECTION "debug"
    DEB_DEPENDS "libsharemind-vmi (= ${SharemindLibVmi_VERSION})"
)
SharemindPackagingFinalize()
