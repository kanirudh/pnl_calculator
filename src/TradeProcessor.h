//
// Created by Anirudh Agrawal on 7/19/25.
//

#ifndef TRADEPROCESSOR_H
#define TRADEPROCESSOR_H

#include <cstdint>
#include <vector>

#include "PnlPublisherI.h"

enum class Mode {
    LIFO = 0,
    FIFO = 1
};

enum class Side {
    BUY = 0,
    SELL = 1
};

struct Order {
    uint32_t timestamp;
    int quantity;
    Side side;
    double price;
    // Assuming quantity is an integer, I don't think the spec said anything about it.
};
static_assert(sizeof(Order) == 24);

class TradeProcessor {
public:
    explicit TradeProcessor(std::string_view mode, std::string_view symbol, PnlPublisherI& publisher);
    ~TradeProcessor();

    void Process(Order trade);

private:
    // NOTE: Based on the spec it seems some sort of short selling is allowed
    std::vector<Order> buy_orders_;
    std::vector<Order> sell_orders_;
    PnlPublisherI& publisher_;
    std::string symbol_;
    Mode mode_;
};



#endif //TRADEPROCESSOR_H
