add_library(libpnl_calculator STATIC PnlCalculator.cpp CsvReader.cpp TradeProcessor.cpp
        PnlPublisher.cpp
        PnlPublisher.h)
target_include_directories(libpnl_calculator PUBLIC ${CMAKE_SOURCE_DIR}/src)

add_executable(pnl_calculator main.cpp)
target_link_libraries(pnl_calculator PRIVATE libpnl_calculator)