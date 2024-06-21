#ifndef ROADBUILDINGCARD_HPP
#define ROADBUILDINGCARD_HPP

#include "DevCard.hpp"

namespace ariel {

    class RoadBuildingCard : public DevCard {
    public:
        RoadBuildingCard();
        ~RoadBuildingCard() override;

        std::string getTypeName() const override{ return "Road Building";};
        int getType() const override { return ROAD_BUILDING; }
    };

}

#endif // ROADBUILDINGCARD_HPP