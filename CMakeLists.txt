cmake_minimum_required(VERSION 3.4.1)
project(calculator)


include_directories(src/main/include)
aux_source_directory(src/main/cpp dir_srcs)
aux_source_directory(src/test/cpp dir_test_srcs)
set(MAIN ${dir_srcs})
set(TEST ${dir_srcs} ${dir_test_srcs})


add_executable(main ${MAIN})
add_executable(test ${TEST})
