//
// Created by Anirudh Agrawal on 7/19/25.
//

#ifndef PNL_CALCULTOR_H
#define PNL_CALCULTOR_H

#include "CsvReader.h"
#include "string_view"

enum class MODE {
    LIFO = 0,
    FIFO = 1
};

// This is the main class acting as a mediator between all components for this standard utility
class PnlCalculator {
public:
    PnlCalculator(std::string_view input_file, std::string_view mode);

    void Run();

private:
    CsvReader reader_;
    MODE mode_;
};


#endif //PNL_CALCULTOR_H
