set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")

include(TOCBaseProject)

macro(add_linker_flags)
  foreach(flag ${ARGN})
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${flag}")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${flag}")
  endforeach()
endmacro()

add_linker_flags(-ldl)

set(TOC_USE_C++X0 TRUE)
set(NEEDED_BOOST_LIBS thread system)

cmake_minimum_required(VERSION 2.6)
setup_toc_build_env_lib(toc 0 2 1-SNAPSHOT)

add_toc_test(DBDriverTest1)
add_toc_test(LoggerTest1)
add_toc_test(MessageTest1)
add_toc_test(StringTest1)
add_toc_test(VersionTest1)
