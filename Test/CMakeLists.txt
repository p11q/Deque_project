find_package(GTest PATHS "/home/user/Projects/C++/Deque_tests/dep/OUT")

add_executable(g_tests g_test.cpp)

target_link_libraries(g_tests PUBLIC GTest::gtest_main)

target_include_directories(g_tests PUBLIC "/home/user/Projects/C++/Deque_tests/dep/OUT/include"
                                            "/home/user/Projects/C++/Deque_tests/includes")


