include(TOCBaseProject)

set(TOC_USE_C++X0 TRUE)

cmake_minimum_required(VERSION 2.6)
setup_toc_build_env_lib(toc 0 2 1-SNAPSHOT)

add_toc_test(LoggerTest1)
add_toc_test(MessageTest1)
add_toc_test(StringTest1)
