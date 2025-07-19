add_executable(pnl_calculator main.cpp PnlCalculator.cpp CsvReader.cpp
        TradeProcessor.cpp
        )
target_include_directories(pnl_calculator PRIVATE ${CMAKE_SOURCE_DIR}/src)