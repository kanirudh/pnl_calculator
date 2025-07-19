//
// Created by Anirudh Agrawal on 7/19/25.
//

#include "PnlCalculator.h"

PnlCalculator::PnlCalculator(std::string_view input_file, std::string_view mode) : reader_(input_file),
processor_(mode) {}

void PnlCalculator::Run() {
    // TODO(anirudh): Implement this.
     for (auto line = reader_.GetNext(); not line; line = reader_.GetNext()) {
        processor_.Process(ParserTrade(*line));
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






