//
// Created by Anirudh Agrawal on 7/19/25.
//

#include "PnlCalculator.h"

PnlCalculator::PnlCalculator(std::string_view input_file, std::string_view mode) : reader_(input_file),
    mode_(mode == "lifo" ? MODE::LIFO : MODE::FIFO) {
}

void PnlCalculator::Run() {
    // TODO(anirudh): Implement this.
    while (reader_.GetNext()) {
    }
}


