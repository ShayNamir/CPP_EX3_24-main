/*
ID:207192246
Mail: ShayNamir@gmail.com
*/
#ifndef DevCard_HPP
#define DevCard_HPP
#include "Player.hpp"

#define KNIGHT 0
#define VICTORY_POINT 1
#define ROAD_BUILDING 2
#define MONOPOLY 3
#define YEAR_OF_PLENTY 4

namespace ariel {
    class DevCard {
    private:
        int type;
        bool used;

    public:
        DevCard(int type);
        ~DevCard();
        int getType() const;
        std::string getTypeName() const;
        bool isUsed() const;
        int useDevelopmentCard();
    };
}

#endif // DevCard_HPP
