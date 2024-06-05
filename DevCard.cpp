/*
ID:207192246
Mail: ShayNamir@gmail.com
*/
#include "DevCard.hpp"
#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>

using namespace ariel;
using namespace std;

DevCard::DevCard(int type) {
    this->type = type;
    this->used = false;
}

DevCard::~DevCard() {}

int DevCard::getType() const {
    return type;
}

bool DevCard::isUsed() const {
    return used;
}

int DevCard::useDevelopmentCard(){
    this->used = true;
    return this->type;
}
string DevCard::getTypeName() const {
    switch (this->type) {
        case KNIGHT:
            return "Knight";
        case VICTORY_POINT:
            return "Victory Point";
        case ROAD_BUILDING:
            return "Road Building";
        case MONOPOLY:
            return "Monopoly";
        case YEAR_OF_PLENTY:
            return "Year of Plenty";
        default:
            return "Unknown";
    }
}

