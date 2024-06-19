#ifndef KNIGHTCARD_HPP
#define KNIGHTCARD_HPP

#include "DevCard.hpp"

namespace ariel {
    class KnightCard : public DevCard {
    public:
        KnightCard();
        ~KnightCard() override;

        int getTypeName() const override;
    };

}

#endif // KNIGHTCARD_HPP