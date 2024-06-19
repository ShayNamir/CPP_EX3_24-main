#include "KnightCard.hpp"

namespace ariel {

    KnightCard::KnightCard() : DevCard(){}

    KnightCard::~KnightCard() {}

    int KnightCard::getTypeName() const {
        return KNIGHT;
    }

}