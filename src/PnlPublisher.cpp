//
// Created by Anirudh Agrawal on 7/19/25.
//

#include "PnlPublisher.h"

#include <iostream>

PnlPublisher::~PnlPublisher() noexcept = default;

void PnlPublisher::Publish(uint32_t timestamp, std::string_view symbol, double pnl) noexcept {
    std::cout << timestamp << "," << symbol << "," << pnl << std::endl;
}
