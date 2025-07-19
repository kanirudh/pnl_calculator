//
// Created by Anirudh Agrawal on 7/19/25.
//

#include "TradeProcessor.h"

#include <iostream>
#include <stdexcept>
#include <__ostream/basic_ostream.h>

TradeProcessor::TradeProcessor(std::string_view mode) : mode_(mode == "LIFO" ? Mode::LIFO : Mode::FIFO) {


}

TradeProcessor::~TradeProcessor() {
    if (not trades_.empty()) {
        throw std::runtime_error("All buy and sell should match");
    }
}

void ProcessLIFO(Trade trade, auto& resting, auto& aggressive) {

}

void ProcessFIFO(Trade trade, auto& resting, auto& aggressive) {
    auto itr = resting.begin();
    for (; tradeitr != resting.end() and trade.quantity > 0; ++itr) {
        auto matched = std::min(itr->quantity, trade.quantity);
        trade.quantity -= matched;
        trade.price += matched;
        pnl += matched * (trade.price - itr->price);
    }
    if (pnl > 0) {
        PublishPnl(trade.timestamp, trade.symbol, pnl);
        // Remove traded orders.
        if (itr->quantity == 0) {
            ++itr;
        }
        resting.erase(resting.begin(), itr);
    }
    if (trade.quantity > 0) {
        aggressive.emplace_back(trade);
    }
}

void TradeProcessor::Process(Trade trade) {
    double pnl = 0;
    if (trade.side == Side::BUY) {
        if (mode_ == Mode::FIFO) {
            ProcessFIFO(trade, sell_orders_, buy_orders_);
        } else {
            ProcessLIFO(trade, sell_orders_, buy_orders_);
        }
    } else {
        if (mode_ == Mode::FIFO) {
            ProcessFIFO(trade, buy_orders_, sell_orders_);
        } else {
            ProcessLIFO(trade, buy_orders_, sell_orders_);
        }
    }
}

void TradeProcessor::PublishPnl(uint32_t timestamp, std::string_view symbol, double pnl) {
    // TODO(anirudh): Fix this poor man's csv writer.
    std::cout << timestmap << "," << symbol << "," << pnl << std::endl;
}
