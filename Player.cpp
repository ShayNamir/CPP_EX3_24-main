/*
ID:207192246
Mail: ShayNamir@gmail.com
*/
#include "Player.hpp"
#include "Catan.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>


using namespace std;
namespace ariel {
    int ariel::Player::playerCount = 0;
    // Constructor
    //Default constructor
    Player::Player() {
        // Uses the other constructor
        Player("Diffult_Player");
    }
    Player::Player(string name) {
        //cout<< "Enter Player constructor"<<endl;
        for (int i = 0; i < 5; ++i) {
            resources[i] = 0; // Initialize all resources to 0
        }
        this->name = name;
        this->points = 0;
        this->playerNumber = ++playerCount;// The first player will have number 1
        this->developmentCards = vector<shared_ptr<DevCard>>();
    }

    // Destructor
    Player::~Player() {
        // Nothing to clean up, but we need a destructor for completeness
    }
    int Player::getPoints() const{
        return this->points;
    }
    int Player::getPlayerNumber() const{
        return this->playerNumber;
    }

    // This function returns the name of the player
    string Player::getName() const {
        return this->name;
    }

    // Add resources to the player
    void Player::addResource(int resourceType, int amount) {
        //cout<< "Enter addResource"<<endl;
        if (resourceType >= 0 && resourceType < 5) 
            resources[resourceType] += amount;
        else
            throw std::out_of_range("Invalid resource type 1: " + std::to_string(resourceType));
        //cout << "Player " << this->name << " has received " << amount << " " << resourceType << " resources" << endl;
        //cout<<name<<" has "<<resources[resourceType]<<" resources of type "<<resourceType<<endl;
    }

    // Remove resources from the player
    void Player::removeResource(int resourceType, int amount) {
        //cout<< "Enter removeResource"<<endl;
        if (resourceType >= 0 && resourceType < 5) {
            if(resources[resourceType] >= amount)
                throw std::out_of_range("No enough resources");
            resources[resourceType] -= amount;
        }
        else
            throw std::out_of_range( "Invalid resource type 2");
    }

    // Get the amount of a specific resource
    int Player::getResource(int resourceType) const {
        if (resourceType >= 0 && resourceType < 5)
            return resources[resourceType];
        throw std::out_of_range( "Invalid resource type 3");// If the resource type is invalid
    }
    void Player::addPoints(int amount){
        this->points += amount;
    }
    void Player::printResources() const{
        cout << "Player " << this->name << " has the following resources:" << endl;
        cout << "WOOD: " << resources[WOOD] << endl;
        cout << "BRICK: " << resources[BRICK] << endl;
        cout << "SHEEP: " << resources[SHEEP] << endl;
        cout << "WHEAT: " << resources[WHEAT] << endl;
        cout << "IRON: " << resources[IRON] << endl;
    }
    void Player::rolledSeven(){
        //Check if the player has more than 7 resources
        int totalResources = this->getResourcesCount();
        if(totalResources<8)
            return;

        // The player chooses half of his resources to discard
        this->printResources();
        cout << "You have more than 7 resources, you should discard half of them" << endl;
    }
    void Player::buyDevelopmentCard(shared_ptr<DevCard> card){
       // Add the card to the player's deck
        this->developmentCards.push_back(card);
    }
    shared_ptr<DevCard> Player::getCardAt(int num){
        if(num >= 0 && num < this->getCardCount())
            return developmentCards[num];
        throw std::out_of_range ("Invalid card index");
    }
    int Player::getCardCount() const{
        return this->developmentCards.size();
    }
    int Player::getResourcesCount() const{
        int totalResources = 0;
        for (int i = 0; i < 5; ++i) {
            totalResources += resources[i];
        }
        return totalResources;
    }
    void Player::printDevelopmentCards(){
        cout << "Player " << this->name << " has the following development cards:" << endl;
        for (int i = 0; i < this->getCardCount(); ++i) {
            string s = this->getCardAt(i)->isUsed() ? "Yes" : "No";
            cout << i << ".: " << this->getCardAt(i)->getTypeName() << ", is used: " << s << endl;
        }
    }
    int Player::useDevelopmentCard(int cardIndex){
        if(cardIndex >= 0 && cardIndex < this->getCardCount()){
            shared_ptr<DevCard> card = this->getCardAt(cardIndex);
            if(card->isUsed())
                throw std::out_of_range("The card is already used");
            card->useDevelopmentCard();
            return card->getTypeName();
        }
        else
            throw std::out_of_range("Invalid card index");
    }
    int Player::numOfNightOpened(){
        int count = 0;
        for (int i = 0; i < this->getCardCount(); ++i) {
            if(this->getCardAt(i)->getTypeName() == KNIGHT&&this->getCardAt(i)->isUsed())
                count++;
        }
        return count;
    }
    void Player::clearAllDevCards(){
        this->developmentCards.clear();
    }
    void Player::deleteDevCard(int index){
        if(index >= 0 && index < this->getCardCount())
            this->developmentCards.erase(this->developmentCards.begin() + index);
        else
            throw std::out_of_range("Invalid card index");
    }
}
