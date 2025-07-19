//
// Created by Anirudh Agrawal on 7/19/25.
//

#include "TradeProcessor.h"

#include <iostream>
#include <stdexcept>
#include <__ostream/basic_ostream.h>

TradeProcessor::TradeProcessor(std::string_view mode) : mode_(mode == "lifo" ? Mode::LIFO : Mode::FIFO) {}

TradeProcessor::~TradeProcessor() {
    if (not buy_orders_.empty() or not sell_orders_.empty()) {
        std::cerr << "Total buy and sell should have matched" << std::endl;
    }
}

std::optional<double> ProcessLIFO(Trade trade, auto& resting, auto& aggressive, double sign) {
    double pnl = 0;
    int traded = 0;
    while (trade.quantity > 0 and not resting.empty()) {
        auto& other = resting.back();
        auto matched = std::min(other.quantity, trade.quantity);
        other.quantity -= matched;
        trade.quantity -= matched;
        traded += matched;

        pnl += matched * (trade.price - other.price) * sign;

        if (other.quantity == 0) {
            resting.pop_back();
        }
    }
    if (trade.quantity > 0) {
        // Enqueue the remaining order
        aggressive.push_back(trade);
    }
    if (traded) {
        return pnl;
    }
    return std::nullopt;
}

std::optional<double> ProcessFIFO(Trade trade, auto& resting, auto& aggressive, const double sign) {
    auto itr = resting.begin();
    double pnl = 0;
    int traded = 0;

    for (; itr != resting.end() and trade.quantity > 0; ) {
        auto matched = std::min(itr->quantity, trade.quantity);
        trade.quantity -= matched;
        itr->quantity -= matched;
        pnl += matched * (trade.price - itr->price) * sign;
        traded += matched;
        itr += (itr->quantity == 0);
    }
    if (trade.quantity > 0) {
        aggressive.emplace_back(trade);
    }
    // Check and remove the final traded orders.
        if (traded) {
            resting.erase(resting.begin(), itr);
            return pnl;
        }
    return std::nullopt;
}

void TradeProcessor::Process(Trade trade) {
    std::optional<double> pnl;
    if (trade.side == Side::BUY) {
        if (mode_ == Mode::FIFO) {
            pnl = ProcessFIFO(trade, sell_orders_, buy_orders_, -1);
        } else {
            pnl = ProcessLIFO(trade, sell_orders_, buy_orders_, -1);
        }
    } else {
        if (mode_ == Mode::FIFO) {
            pnl = ProcessFIFO(trade, buy_orders_, sell_orders_, 1);
        } else {
            pnl = ProcessLIFO(trade, buy_orders_, sell_orders_, 1);
        }
    }

    // TODO(anirudh): Can there be traded but with zero pnl ?
    if (pnl) {
        PublishPnl(trade.timestamp, trade.symbol, *pnl);
    }
}

void TradeProcessor::PublishPnl(uint32_t timestamp, std::string_view symbol, double pnl) {
    // TODO(anirudh): Fix this poor man's csv writer.
    std::cout << timestamp << "," << symbol << "," << pnl << std::endl;
}
