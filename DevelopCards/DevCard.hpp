#ifndef DEVCARD_HPP
#define DEVCARD_HPP
#define KNIGHT 0
#define VICTORY_POINT 1
#define ROAD_BUILDING 2
#define MONOPOLY 3
#define YEAR_OF_PLENTY 4

#include <string>

namespace ariel {

    class DevCard {
    private:
        bool used;

    public:
        DevCard();
        virtual ~DevCard();
        
        bool isUsed() const;
        void useDevelopmentCard();

        // Pure virtual function to get the type name of the card
        virtual int getTypeName()const = 0;
    };

}

#endif