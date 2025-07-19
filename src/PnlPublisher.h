//
// Created by Anirudh Agrawal on 7/19/25.
//

#ifndef PNLPUBLISHER_H
#define PNLPUBLISHER_H

#include "PnlPublisherI.h"

class PnlPublisher : public PnlPublisherI {
public:
    ~PnlPublisher() noexcept final;
    void Publish(uint32_t timestamp, std::string_view symbol, double pnl) noexcept final;
};

#endif //PNLPUBLISHER_H
