#ifndef MONOPOLYCARD_HPP
#define MONOPOLYCARD_HPP

#include "DevCard.hpp"

namespace ariel {

    class MonopolyCard : public DevCard {
    public:
        MonopolyCard();
        ~MonopolyCard() override;

        int getTypeName() const override;
    };

}

#endif // MONOPOLYCARD_HPP