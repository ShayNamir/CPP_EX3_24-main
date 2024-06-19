#ifndef VICTORYPOINTCARD_HPP
#define VICTORYPOINTCARD_HPP

#include "DevCard.hpp"

namespace ariel {

    class VictoryPointCard : public DevCard {
    public:
        VictoryPointCard();
        ~VictoryPointCard() override;

        int getTypeName() const override;
    };

}

#endif // VICTORYPOINTCARD_HPP