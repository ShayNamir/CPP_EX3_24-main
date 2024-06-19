/*
ID:207192246
Mail: ShayNamir@gmail.com
*/
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <vector>

using namespace std;

namespace ariel {
    class DevCard;  // Forward declaration
    
    class Player {
    private:
        // Static variable to keep track of the number of players starting from 1
        static int playerCount;
        std::string name;
        int playerNumber;
        int resources[5]; // Assuming 5 types of resources: WOOD, BRICK, SHEEP, WHEAT, IRON
        int points;
        vector<shared_ptr<DevCard>> developmentCards;

    public:
        // Constructor
        //Default constructor
        Player();
        Player(string name);
        
        // Destructor
        ~Player();
        
        // This function returns the name of the player
        string getName() const;
        int getPoints() const;
        int getPlayerNumber() const;

        // Functions to manipulate resources
        void addResource(int resourceType, int amount);
        void removeResource(int resourceType, int amount);
        int getResource(int resourceType) const;
        int getResourcesCount() const;
        void rolledSeven();
        void buyDevelopmentCard(shared_ptr<DevCard> card);
        void deleteDevCard(int index);
        shared_ptr<DevCard> getCardAt(int num);
        int useDevelopmentCard( int cardIndex);
        int getCardCount() const;
        int numOfNightOpened();


        void addPoints(int amount);
        void printResources() const;
        void printDevelopmentCards();
        
        //For testing
        void clearAllDevCards();
    };
}

#endif // PLAYER_HPP
