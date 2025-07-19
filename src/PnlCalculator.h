//
// Created by Anirudh Agrawal on 7/19/25.
//

#ifndef PNL_CALCULTOR_H
#define PNL_CALCULTOR_H

#include "CsvReader.h"
#include "string_view"
#include "TradeProcessor.h"


// This is the main class acting as a mediator between all components for this standard utility
class PnlCalculator {
public:
    PnlCalculator(std::string_view input_file, std::string_view mode);

    void Run();

private:
    static Trade ParseTrade(std::vector<std::string> tokens);

    CsvReader reader_;
    std::unordered_map<std::string, TradeProcessor> symbol_to_processor_;
    std::string mode_;
};


#endif //PNL_CALCULTOR_H
