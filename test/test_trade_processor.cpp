//
// Created by Anirudh Agrawal on 7/19/25.
//

#include "TradeProcessor.h"

#include "gtest/gtest.h"

class TestPublisher : public PnlPublisherI {
public:
    using Callback = std::function<void(uint32_t, std::string_view, double)>;
    TestPublisher(Callback cb) : cb_(std::move(cb)) {}

    void Publish(uint32_t timestamp, std::string_view symbol, double pnl) noexcept final {
    cb_(timestamp, symbol, pnl);
    }


    Callback cb_;
};

class TradeProcessorTest {
public:
    TradeProcessorTest(std::string_view mode) : publisher_([this](uint32_t t, std::string_view s, double p) {
        last_timestamp_ = t;
        last_symbol_ = s;
        last_pnl_ = p;
    }),
    tp(mode, "TFS", publisher_){}


    uint32_t last_timestamp_ = 0;
    std::string last_symbol_;
    double last_pnl_ = 0;
    TestPublisher publisher_;
    TradeProcessor tp;
};



TEST(TradeProcessor, SingleTradeFIFO) {
    TradeProcessorTest obj("fifo");

    obj.tp.Process(Order{.timestamp = 101, .quantity = 10, .side = Side::BUY, .price = 45.0});
    obj.tp.Process(Order{.timestamp = 102, .quantity = 10, .side = Side::SELL, .price = 50.0});

    EXPECT_EQ(obj.last_timestamp_, 102);
    EXPECT_EQ(obj.last_symbol_, "TFS");
    EXPECT_EQ(obj.last_pnl_, 50.0);
}
