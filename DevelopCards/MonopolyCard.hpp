#ifndef MONOPOLYCARD_HPP
#define MONOPOLYCARD_HPP

#include "DevCard.hpp"

namespace ariel {

    class MonopolyCard : public DevCard {
    public:
        MonopolyCard();
        ~MonopolyCard() override;

        std::string getTypeName() const override{ return "Monopoly";};
        int getType() const override { return MONOPOLY; }
    };

}

#endif // MONOPOLYCARD_HPP