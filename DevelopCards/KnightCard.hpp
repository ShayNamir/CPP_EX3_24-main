#ifndef KNIGHTCARD_HPP
#define KNIGHTCARD_HPP

#include "DevCard.hpp"

namespace ariel {
    class KnightCard : public DevCard {
    public:
        KnightCard();
        ~KnightCard() override;

        std::string getTypeName() const override{ return "Knight";};
        int getType() const override { return KNIGHT; }
    };

}

#endif // KNIGHTCARD_HPP