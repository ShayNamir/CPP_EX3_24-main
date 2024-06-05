/*
ID:207192246
Mail: ShayNamir@gmail.com
*/
#ifndef SPOT_HPP
#define SPOT_HPP
#include <string>
#include "Player.hpp"

#define NOTHING -1
#define ROAD 0
#define SETTLEMENT 1
#define CITY 2

namespace ariel {
    class Spot {
    private:
        int owner;
        int structure; // 0: nothing, 1: settlement, 2: city
        bool isCollect;

    public:
        // Constructor
        Spot();

        int getOwner() const;
        void setOwner(int playerNum);
        void placeRoad(int playerNum);
        void placeSettlement(int playerNum);
        void placeCity();

        int getStructure() const;
        bool isAround(int playerNum) const;
        void setStructure(const int& structure);
        void collect();

        bool isTaken() const;
        bool isTakenBy(int playerNum) const;
        bool isCollectable() const;
    };
}

#endif // SPOT_HPP
