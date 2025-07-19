include(GoogleTest)

add_executable(tests test_trade_processor.cpp)
target_link_libraries(tests PRIVATE
        libpnl_calculator
        GTest::gtest_main
)

gtest_discover_tests(tests)
