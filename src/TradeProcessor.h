//
// Created by Anirudh Agrawal on 7/19/25.
//

#ifndef TRADEPROCESSOR_H
#define TRADEPROCESSOR_H

#include <cstdint>
#include <vector>

enum class Mode {
    LIFO = 0,
    FIFO = 1
};

enum class Side {
    BUY = 0,
    SELL = 1
};

struct Trade {
    uint32_t timestamp;
    std::string symbol;
    Side side;
    double price;
    // Assuming quantity is an integer, I don't think the spec said anything about it.
    int quantity;
};
static_assert(sizeof(Trade) == 56);

class TradeProcessor {
public:
    explicit TradeProcessor(std::string_view mode);
    ~TradeProcessor();

    void Process(Trade trade);

private:
    static void PublishPnl(uint32_t timestamp, std::string_view symbol, double pnl);

    // NOTE: Based on the spec it seems some sort of short selling is allowed
    std::vector<Trade> buy_orders_;
    std::vector<Trade> sell_orders_;
    Mode mode_;
};



#endif //TRADEPROCESSOR_H
