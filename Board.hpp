/*
ID:207192246
Mail: ShayNamir@gmail.com
*/
#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <string>
#include <map>
#include <iostream>
#include "Player.hpp"
#include "Land.hpp"
#define BOARD_SIZE 19

namespace ariel {
    //Forward declaration
    //class Land;
    
    class Board {
    private:
        Land lands[BOARD_SIZE];
        // Helper function to generate a random board
        static std::vector<Land> generateRandomBoard();
        // Helper function to close adding 0-5
        int closeAdding(int index, int add) const;

    public:
        // Constructor
        Board(bool isTest=false);
        Land getLand(int index) const;

        bool isPlaceTaken(bool isRoad,int landIndex, int spotIndex);
        void placeRoad(int playerNum, int landIndex, int spotIndex);
        void plaseSettlement(int playerNum,bool firstTurn, int landIndex, int spotIndex);
        void placeCity(int playerNum, int landIndex, int spotIndex);
        //void distributeResources(int diceRoll);
        void printBoard();
        //void chooseFirstRes(int playerNum);
        vector<vector<int>> getSNeighbors(int landIndex,int spotIndex);
    };
}
#endif // BOARD_HPP
