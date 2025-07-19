//
// Created by Anirudh Agrawal on 7/19/25.
//

#ifndef PNLPUBLISHERI_H
#define PNLPUBLISHERI_H

#include <string_view>

class PnlPublisherI {
public:
    virtual ~PnlPublisherI() noexcept = default;
    virtual void Publish(uint32_t timestamp, std::string_view symbol, double pnl) noexcept = 0;

};

#endif //PNLPUBLISHERI_H
