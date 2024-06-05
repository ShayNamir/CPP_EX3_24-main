/*
ID:207192246
Mail: ShayNamir@gmail.com
*/
#ifndef LAND_HPP
#define LAND_HPP

#include "Spot.hpp"
//#include "Board.hpp"
#define WOOD 0
#define BRICK 1
#define SHEEP 2
#define WHEAT 3
#define IRON 4
#define DESERT -1
namespace ariel{
    //Forward declaration
    //class Board;
    class Land{
        private:
            Spot roadSpots[6];// 0: top left, 1: top, 2: top right, 3: bottom right, 4: bottom, 5: bottom left
            Spot settlementSpots[6];// 0: top left, 1: top right, 2: right, 3: bottom right, 4: bottom left, 5: left
            int number; // 2-12
            int resource;// 0-4
            // Helper function to close adding 0-5
            int closeAdding(int index, int add) const;
        public:
            // Constructor
            Land();
            Land( int number, int resource);
            int getNumber();
            int getResource(); 
            string getResourceName();
            Spot& getSpot(bool isRoad, int index);
            bool isSpotTaken(bool isRoad,int spotIndex);
            int getOwner(bool isRoad,int spotIndex);
            void placeSettlement(int playerNum, int spotIndex);
            void placeRoad(int playerNum, int spotIndex);
            bool canPlaceRoad(int playerNum, int spotIndex);
            int canPlaceSettlement(int playerNum, int spotIndex);
            void placeCity(int playerNum, int spotIndex);
            //void distributeResources(int diceRoll);
            void printLand();
            bool isSett(int playerNum);
    };
}
#endif // LAND_HPP