#ifndef YEAROFPLENTYCARD_HPP
#define YEAROFPLENTYCARD_HPP

#include "DevCard.hpp"

namespace ariel {

    class YearOfPlentyCard : public DevCard {
    public:
        YearOfPlentyCard();
        ~YearOfPlentyCard() override;

        std::string getTypeName() const override{ return "Year of Plenty";};
        int getType() const override { return YEAR_OF_PLENTY; }
    };

}

#endif // YEAROFPLENTYCARD_HPP