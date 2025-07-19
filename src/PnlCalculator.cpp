//
// Created by Anirudh Agrawal on 7/19/25.
//

#include "PnlCalculator.h"

#include <iostream>

PnlCalculator::PnlCalculator(std::string_view input_file, std::string_view mode) : reader_(input_file),
                                                                                   mode_(mode) {}

void PnlCalculator::Run() {
     for (auto line = reader_.GetNext(); line; line = reader_.GetNext()) {
         auto event = ParseTrade(*line);
         if (auto itr = symbol_to_processor_.find(event.symbol); itr != symbol_to_processor_.end()) {
             itr->second.Process(static_cast<Order>(event));
         } else {
             [[maybed_unused]] auto [new_itr, inserted] = symbol_to_processor_.emplace(event.symbol, TradeProcessor(mode_, event.symbol, publisher_));
             new_itr->second.Process(static_cast<Order>(event));
         }
    }
}

Event PnlCalculator::ParseTrade(std::vector<std::string> tokens) {

    if (tokens.size() != 5) {
        throw std::runtime_error("TradeProcessor::Process: wrong number of arguments");
    }

    Event trade;
    trade.timestamp = std::stoul(tokens[0]);
    trade.symbol = std::move(tokens[1]);
    trade.side = tokens[2][0] == 'B' ? Side::BUY : Side::SELL;
    trade.price = std::stod(tokens[3]);
    trade.quantity = std::stoi(tokens[4]);
    return trade;
}






