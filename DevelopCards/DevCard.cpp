#include "DevCard.hpp"

namespace ariel {

    DevCard::DevCard(): used(false) {}

    DevCard::~DevCard() {}

    bool DevCard::isUsed() const {
        return used;
    }

    void DevCard::useDevelopmentCard() {
        this->used = true;
    }

}