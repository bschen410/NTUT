# Add test executable
add_executable(
    unit_tests
    ut_main.cpp
    ut_hello.h
)

target_link_libraries(
    unit_tests
    sample_lib
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(unit_tests)