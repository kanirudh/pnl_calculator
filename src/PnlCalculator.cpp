//
// Created by Anirudh Agrawal on 7/19/25.
//

#include "PnlCalculator.h"

#include <iostream>

PnlCalculator::PnlCalculator(std::string_view input_file, std::string_view mode) : reader_(input_file),
                                                                                   mode_(mode) {}

void PnlCalculator::Run() {
    // TODO(anirudh): Implement this.
     for (auto line = reader_.GetNext(); line; line = reader_.GetNext()) {
         auto trade = ParseTrade(*line);
         //std::cout << trade.symbol << trade.timestamp << trade.price << trade.quantity << std::endl;
         if (auto itr = symbol_to_processor_.find(trade.symbol); itr != symbol_to_processor_.end()) {
             itr->second.Process(trade);
         } else {
             // TODO(anirudh): TradeProcessor should take symbol in trade constructor.
             [[maybed_unused]] auto [new_itr, inserted] = symbol_to_processor_.emplace(trade.symbol, TradeProcessor(mode_));
             new_itr->second.Process(trade);
         }
    }
}

Trade PnlCalculator::ParseTrade(std::vector<std::string> tokens) {

    if (tokens.size() != 5) {
        throw std::runtime_error("TradeProcessor::Process: wrong number of arguments");
    }

    Trade trade;
    trade.timestamp = std::stoul(tokens[0]);
    trade.symbol = std::move(tokens[1]);
    trade.side = tokens[2][0] == 'B' ? Side::BUY : Side::SELL;
    trade.price = std::stod(tokens[3]);
    trade.quantity = std::stoi(tokens[4]);
    return trade;
}






