#ifndef ROADBUILDINGCARD_HPP
#define ROADBUILDINGCARD_HPP

#include "DevCard.hpp"

namespace ariel {

    class RoadBuildingCard : public DevCard {
    public:
        RoadBuildingCard();
        ~RoadBuildingCard() override;

        int getTypeName() const override;
    };

}

#endif // ROADBUILDINGCARD_HPP