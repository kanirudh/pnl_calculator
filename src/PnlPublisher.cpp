//
// Created by Anirudh Agrawal on 7/19/25.
//

#include "PnlPublisher.h"

#include <iostream>
#include <iomanip>

PnlPublisher::~PnlPublisher() noexcept = default;

void PnlPublisher::Publish(uint32_t timestamp, std::string_view symbol, double pnl) noexcept {
    std::cout << timestamp << "," << symbol << ",";
    std::cout << std::fixed << std::setprecision(2) << pnl << "\n";
}
