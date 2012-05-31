#  Copyright (c) by Karol Herbst <projects@karolherbst.de>
#
#
#   This program is free software; you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation; either version 2 of the License, or
#   (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with this program; if not, write to the Free Software
#   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
#

###############################################################################
#
# arguments:
#
# NEEDED_BOOST_LIBS         : a string with all needed boost libs
# NEEDED_BOOST_LIBS_TEST    : same as NEEDED_BOOST_LIBS just for tests
# TOC_CMAKE_ROOT            : specify where cmake is installed
#                             (default: ${CMAKE_ROOT})
# TOC_INCLUDE_DIR           : where is the folder with the public headers
#                             (default: include )
# TOC_PCH_FILE              : the name of the pch file (default: headers.pch)
# TOC_PREFIX                : top of the installation (default: /usr/local )
#                             NOTE: will be overwritten by CMAKE_INSTALL_PREFIX
# TOC_SRC_DIR               : where are the sources (default: src )
# TOC_TEST_DIR              : where is the test evnironment (default: test )
# TOC_USE_C++X0             : using the new C++ standart?
# TOC_USE_PCH               : using pch? (needs a pch file in the src dir)
#                             this will also search for TESTNAME.pch files
#
# functions:
#
# add_toc_test(name)        : add test to cmake. Sources are located in
#                             test/${name}*.{c, cpp, ...}
# add_toc_dependencie       : add a dependency (auto include and link)
#
# variables this script will set:
#
# TOC_INCLUDE_DIR           : will include ./include to project
# TOC_SOURCES               : glob with all sources
# TOC_HEADERS               : glob with all headers to install
# TOC_PROJECT_NAME          : name of the project
# TOC_TEST_ENABLED          : guess what
#
###############################################################################

###############################################################################
#
# here are patches from various sources
#
###############################################################################

MACRO (ADD_PCH_RULE  _header_filename _src_list)
    
ENDMACRO(ADD_PCH_RULE _header_filename _src_list)

###############################################################################
#
# free functions
#
###############################################################################

function(__toc__internel__set_project_version MAJOR MINOR PATCH)
  if(NOT PROJECT_NAME OR "${PROJECT_NAME}" STREQUAL "Project")
    message(FATAL_ERROR "EE PROJECT_NAME MUST be defined before calling set_project_version()")
  endif()
  set(CPACK_PACKAGE_VERSION_MAJOR ${MAJOR})
  set(CPACK_PACKAGE_VERSION_MINOR ${MINOR})
  set(CPACK_PACKAGE_VERSION_PATCH ${PATCH})
  set(CPACK_PACKAGE_VERSION "${MAJOR}.${MINOR}.${PATCH}")
  set(CPACK_SOURCE_PACKAGE_FILE_NAME "${PROJECT_NAME}-${CPACK_PACKAGE_VERSION}")
  set(PROJECT_VERSION "${CPACK_PACKAGE_VERSION}" PARENT_SCOPE)
  set(PROJECT_VERSION_MAJOR "${MAJOR}" PARENT_SCOPE)
  set(PROJECT_VERSION_MINOR "${MINOR}" PARENT_SCOPE)
  set(PROJECT_VERSION_PATCH "${PATCH}" PARENT_SCOPE)
  set(CPACK_IGNORE_FILES "CMakeCache.txt;install_manifest.txt;/Testing/;/Makefile$;\\\\.tar.gz$;\\\\.so[.0-9]*$;/build/;/_CPack_Packages/;/CMakeFiles/;/CVS/;/\\\\.svn/;/\\\\.git/;\\\\.swp$;\\\\.#;/#")
  set(CPACK_SOURCE_IGNORE_FILES ${CPACK_IGNORE_FILES})
  set(CPACK_SOURCE_GENERATOR TGZ ZIP)
  set(CPACK_SOURCE_TOPLEVEL_TAG "")
  include(CPack)
endfunction(__toc__internel__set_project_version)

macro(__toc__internel__setup_install_paths)
  if(WIN32)
    set(CMAKE_INSTALL_PREFIX ""               CACHE PATH "Install prefix")
    set(BIN_INSTALL_DIR      .                CACHE PATH "Binary install dir")
    set(LIB_INSTALL_DIR      .                CACHE PATH "Library install dir")
    set(LIBEXEC_INSTALL_DIR  .                CACHE PATH "Private executable install dir")
    set(INCLUDE_INSTALL_DIR  include          CACHE PATH "Include install dir")
    set(SYSCONF_INSTALL_DIR  .                CACHE PATH "Configuration install dir")
    set(SHARE_INSTALL_DIR    .                CACHE PATH "Data install dir")
  else(WIN32)
    set(CMAKE_INSTALL_PREFIX ${TOC_PREFIX}    CACHE PATH "Install prefix")
    set(BIN_INSTALL_DIR      bin              CACHE PATH "Binary install dir")
    set(LIB_INSTALL_DIR      lib${LIB_SUFFIX} CACHE PATH "Library install dir")
    set(LIBEXEC_INSTALL_DIR  libexec          CACHE PATH "Private executable install dir")
    set(INCLUDE_INSTALL_DIR  include          CACHE PATH "Include install dir")
    set(SYSCONF_INSTALL_DIR  /etc             CACHE PATH "Configuration install dir")
    set(SHARE_INSTALL_DIR    share            CACHE PATH "Data install dir")
  endif(WIN32)
endmacro(__toc__internel__setup_install_paths)

macro(__toc__internal__setup_file_install)
  install(FILES ${TOC_HEADERS}
        DESTINATION "${CMAKE_INSTALL_PREFIX}/${INCLUDE_INSTALL_DIR}/${TOC_PROJECT_NAME}/")
  install(TARGETS ${TOC_PROJECT_NAME}
        DESTINATION "${CMAKE_INSTALL_PREFIX}/${LIB_INSTALL_DIR}/")

  configure_file(${CMAKE_MODULE_PATH}/FindTocPackage.cmake.in ${CMAKE_BINARY_DIR}/Find${TOC_PROJECT_NAME}.cmake @ONLY)
  install(FILES ${CMAKE_BINARY_DIR}/Find${TOC_PROJECT_NAME}.cmake DESTINATION ${CMAKE_ROOT}/Modules)
endmacro(__toc__internal__setup_file_install)

macro(toc_option opt desc init)
  option(${opt} ${desc} ${init})
  list(APPEND TOC_ARG_LIST ${opt})
endmacro(toc_option)

## here we can set compiler/plattform specific settings
macro(__toc__internel__check_arguments)
  if(NOT DEFINED TOC_SRC_DIR)
    set(TOC_SRC_DIR "src")
  endif()
  
  if(NOT DEFINED TOC_INCLUDE_DIR)
    set(TOC_INCLUDE_DIR "include")
  endif()
  
  if(NOT DEFINED TOC_TEST_DIR)
    set(TOC_TEST_DIR "test")
  endif()
  
  if(NOT DEFINED TOC_PREFIX)
    set(TOC_PREFIX "/usr/local")
  endif()
  
  if(NOT DEFINED TOC_PCH_FILE)
    set(TOC_PCH_FILE "headers.pch")
  endif()
  
  if(NOT DEFINED TOC_USE_C++X0)
    set(TOC_USE_C++X0 false)
  endif()
  
  if(NOT DEFINED TOC_USE_PCH)
    set(TOC_USE_PCH false)
  endif()

  if(NOT DEFINED TOC_CMAKE_ROOT)
    set(TOC_CMAKE_ROOT ${CMAKE_ROOT})
  endif()

  message("II project argument list:")
  # formatting ??
  foreach(arg IN LISTS TOC_ARG_LIST)
    message("II ${arg}: ${${arg}}")
    if(${arg})
      add_definitions(-D${arg})
    endif()
  endforeach(arg)
endmacro(__toc__internel__check_arguments)

macro(__toc__internal__set_build_paths)
  include_directories(
    ${TOC_INCLUDE_DIR}
  )
  
  file(GLOB TOC_HEADERS ${CMAKE_SOURCE_DIR}/${TOC_INCLUDE_DIR}/${TOC_PROJECT_NAME}/*.h
                        ${CMAKE_SOURCE_DIR}/${TOC_INCLUDE_DIR}/${TOC_PROJECT_NAME}/*.hh
                        ${CMAKE_SOURCE_DIR}/${TOC_INCLUDE_DIR}/${TOC_PROJECT_NAME}/*.hpp)
  file(GLOB TOC_SOURCES ${CMAKE_SOURCE_DIR}/${TOC_SRC_DIR}/*.c
                        ${CMAKE_SOURCE_DIR}/${TOC_SRC_DIR}/*.C
                        ${CMAKE_SOURCE_DIR}/${TOC_SRC_DIR}/*.cc
                        ${CMAKE_SOURCE_DIR}/${TOC_SRC_DIR}/*.cpp
                        ${CMAKE_SOURCE_DIR}/${TOC_SRC_DIR}/*.cxx ${TOC_HEADERS})
endmacro(__toc__internal__set_build_paths)

macro(__toc__internel__setup_compiler)
  if(TOC_USE_C++X0)
    message("II Using the new C++ Standart")
    add_definitions(-std=c++0x)
  endif()
endmacro(__toc__internel__setup_compiler)

macro(__toc__internel__setup_project PNAME)
  project(${PNAME})
  set(TOC_PROJECT_NAME ${PNAME})
  add_definitions(-DMAKE_${PNAME})
endmacro(__toc__internel__setup_project)

macro(setup_toc_build_env PNAME MAJOR MINOR PATCH)
  message("II TOC based project")
  message("II II for infos, WW for warnings, EE for errors, DD for debug")
  __toc__internel__check_arguments()
  __toc__internel__setup_project(${PNAME})
  __toc__internel__set_project_version(${MAJOR} ${MINOR} ${PATCH})
  __toc__internel__setup_compiler()
  __toc__internal__set_build_paths()
  
  set(Boost_USE_STATIC_LIBS        OFF)
  set(Boost_USE_MULTITHREADED      ON)
  set(Boost_USE_STATIC_RUNTIME     OFF)
  set(Boost_USE_STLPORT            OFF)
  find_package(Boost COMPONENTS ${NEEDED_BOOST_LIBS} REQUIRED)
  
  include_directories(
    ${Boost_INCLUDE_DIRS}
    ${TOC_INCLUDE_DIR}
  )
  if(TOC_USE_PCH)
    message("II Using PCH file")
    add_pch_rule(${TOC_SRC_DIR}/${TOC_PCH_FILE} ${TOC_SOURCES})
  endif()
endmacro(setup_toc_build_env)

macro(setup_toc_build_env_lib PNAME MAJOR MINOR PATCH)
  setup_toc_build_env(${PNAME} ${MAJOR} ${MINOR} ${PATCH})
  
  add_library(${PNAME} SHARED ${TOC_SOURCES})
  __toc__internel__setup_install_paths()
  __toc__internal__setup_file_install()
endmacro(setup_toc_build_env_lib)

macro(setup_toc_build_env_header PNAME MAJOR MINOR PATCH)
  setup_toc_build_env(${PNAME} ${MAJOR} ${MINOR} ${PATCH})
  __toc__internel__setup_install_paths()
  __toc__internal__setup_file_install()
endmacro(setup_toc_build_env_header)

macro(setup_toc_build_env_test)
  ENABLE_TESTING()
  find_package(Boost 1.42 COMPONENTS ${NEEDED_BOOST_LIBS_TEST} prg_exec_monitor test_exec_monitor unit_test_framework REQUIRED)
  include_directories(
    ${Boost_INCLUDE_DIRS}
  )
  set(TOC_TEST_ENABLED)
endmacro(setup_toc_build_env_test)

macro(add_toc_test TESTNAME)
  if(NOT TOC_TEST_ENABLED)
    setup_toc_build_env_test()
  endif()
  include_directories(
    ${TOC_SRC_DIR}
  )
  file(GLOB ${TESTNAME}_SRC ${TOC_TEST_DIR}/${TESTNAME}*.c
                            ${TOC_TEST_DIR}/${TESTNAME}*.C
                            ${TOC_TEST_DIR}/${TESTNAME}*.cc
                            ${TOC_TEST_DIR}/${TESTNAME}*.cpp
                            ${TOC_TEST_DIR}/${TESTNAME}*.cxx)
  if(TOC_USE_PCH)
    add_pch_rule(${TOC_TEST_DIR}/${TESTNAME}.pch ${TESTNAME}_SRC)
  endif()
  add_executable(${TOC_PROJECT_NAME}${TESTNAME} ${${TESTNAME}_SRC})
  target_link_libraries(${TOC_PROJECT_NAME}${TESTNAME}
    ${TOC_PROJECT_NAME}
    ${Boost_LIBRARIES}
  )

  ADD_TEST(${TOC_PROJECT_NAME}${TESTNAME} ${OUTPUT_DIR}/${TOC_PROJECT_NAME}${TESTNAME})
endmacro(add_toc_test)
