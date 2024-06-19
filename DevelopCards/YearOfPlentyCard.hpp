#ifndef YEAROFPLENTYCARD_HPP
#define YEAROFPLENTYCARD_HPP

#include "DevCard.hpp"

namespace ariel {

    class YearOfPlentyCard : public DevCard {
    public:
        YearOfPlentyCard();
        ~YearOfPlentyCard() override;

        int getTypeName() const override;
    };

}

#endif // YEAROFPLENTYCARD_HPP