enable_testing()

add_executable(unit_tests unit_tests.cpp)
target_link_libraries( unit_tests
  GTest::gtest_main
)
target_include_directories( unit_tests
    PUBLIC ${CMAKE_SOURCE_DIR}/include
)

include(GoogleTest)
gtest_discover_tests(unit_tests)
