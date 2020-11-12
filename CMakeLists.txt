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
PROJECT(SharemindLibVmi VERSION 0.4.0 LANGUAGES "CXX")

INCLUDE("${CMAKE_CURRENT_SOURCE_DIR}/config.local" OPTIONAL)
INCLUDE("${CMAKE_CURRENT_BINARY_DIR}/config.local" OPTIONAL)

FIND_PACKAGE(SharemindCMakeHelpers 1.6 REQUIRED)

FIND_PACKAGE(SharemindCxxHeaders 0.8.0 REQUIRED)
FIND_PACKAGE(SharemindVmM4 0.5.0 REQUIRED)


# LibVmi:
FILE(GLOB_RECURSE SharemindLibVmi_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")
FILE(GLOB_RECURSE SharemindLibVmi_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
SharemindAddSharedLibrary(LibVmi
    OUTPUT_NAME "sharemind_vmi"
    SOURCES ${SharemindLibVmi_SOURCES} ${SharemindLibVmi_HEADERS}
)
TARGET_INCLUDE_DIRECTORIES(LibVmi
    INTERFACE
        # $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src> # TODO
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>
    )
TARGET_LINK_LIBRARIES(LibVmi
    PRIVATE
        Sharemind::VmM4
    PUBLIC
        Sharemind::CxxHeaders
    )
INSTALL(FILES ${SharemindLibVmi_HEADERS}
        DESTINATION "include/sharemind/libvmi"
        COMPONENT "dev")
SharemindCreateCMakeFindFilesForTarget(LibVmi
    DEPENDENCIES
        "SharemindCxxHeaders 0.8.0"
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
        "libsharemind-vmi (= ${SharemindLibVmi_DEB_lib_PACKAGE_VERSION})"
        "libsharemind-cxxheaders-dev (>= 0.8.0)"
        "libc6-dev (>= 2.19)"
)
SharemindAddComponentPackage("debug"
    NAME "libsharemind-vmi-dbg"
    DESCRIPTION "Sharemind VM Instructions library debug symbols"
    DEB_SECTION "debug"
    DEB_DEPENDS "libsharemind-vmi (= ${SharemindLibVmi_DEB_lib_PACKAGE_VERSION})"
)
SharemindPackagingFinalize()
