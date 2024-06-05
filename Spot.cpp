/*
ID:207192246
Mail: ShayNamir@gmail.com
*/
#include "Spot.hpp"
#include "Player.hpp"
#include <iostream>

namespace ariel{
    // Constructor
    Spot::Spot() {
        //this->owner = Player();
        this->structure = NOTHING;
        this->isCollect = false;
    }

    int Spot::getOwner() const{
        return this->owner;
    }

    void Spot::setOwner(int playerNum){
        this->owner = playerNum;
    }
    void Spot::collect(){
        this->isCollect = true;
    }

    int Spot::getStructure() const{
        return this->structure;
    }
    bool Spot::isCollectable() const{
        return this->isCollect;
    }

    void Spot::setStructure(const int& structure){
        this->structure = structure;
    }

    bool Spot::isTaken() const{
        return this->structure != NOTHING;
    }
    bool Spot::isTakenBy(int playerNum) const{
        if(this->isTaken())
            return this->owner==playerNum;
        return false;
    }
    void Spot::placeRoad(int playerNum){
        if (this->isTaken())
            throw std::invalid_argument("The spot is already taken");
        this->setOwner(playerNum);
        this->setStructure(ROAD);
    }
    void Spot::placeSettlement(int playerNum){
        if (this->isTaken())
            throw std::invalid_argument("The spot is already taken");
        this->setOwner(playerNum);
        this->setStructure(SETTLEMENT);
    }
    void Spot::placeCity(){
        this->setStructure(CITY);
        cout<<"City placed "<<endl;
        cout<<"My structure is: "<<this->getStructure()<<endl;
    }
    bool Spot::isAround(int playerNum) const{
        bool ans=isTaken();
        //cout<<"Enter Spot::isAround, isTaken="<<ans<<endl;
        if(ans)// If the spot is taken
            return getOwner()==playerNum;
        //cout<<"Return false"<<endl;
        return false;
    }
}