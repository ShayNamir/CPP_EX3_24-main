#ifndef VICTORYPOINTCARD_HPP
#define VICTORYPOINTCARD_HPP

#include "DevCard.hpp"

namespace ariel {

    class VictoryPointCard : public DevCard {
    public:
        VictoryPointCard();
        ~VictoryPointCard() override;

        std::string getTypeName() const override{ return "Victory Point";};
        int getType() const override { return VICTORY_POINT; }
    };

}

#endif // VICTORYPOINTCARD_HPP