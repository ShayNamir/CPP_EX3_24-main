/*
ID:207192246
Mail: ShayNamir@gmail.com
*/
#ifndef CATAN_HPP
#define CATAN_HPP
#include "Player.hpp"
#include "Board.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <random>
namespace ariel{
    class Catan
    {
        private:
        vector<Player*> players;
        Board board;
        int turn;// 1: p1, 2: p2, 3: p3
        vector<DevCard> deck;

        public:
        //Constructor
        Catan(Player& p1, Player& p2, Player& p3, bool isTest=false);

        //destructor
        ~Catan();

        //Mthods
        Board& getBoard();
        int getTurn()const;
        Player& getPlayerByName(string name);
        Player& getPlayer(int num);
        void placeSettlement(int playerNum, int landIndex, int spotIndex);
        void placeRoad(int playerNum, int landIndex, int spotIndex);
        void placeCity(int playerNum, int landIndex, int spotIndex);
        void rollDice(int playerNum);
        void ChooseStartingPlayer(bool isTest=false);
        void endTurn(int playerNum);
        bool checkWinner(int playerNum);
        void tradeResorces(int p1, int p2, int res1, int res2, int amount1, int amount2);
        void tradeDevCard(int p1, int p2, int cardIndex1, int cardIndex2);
        void printPoints();
        void printWinner();
        void printBoard();
        void printDevelopmentCards(int playerNum);
        Player& getCurrentPlayer();
        //void moveRobber();
        void buyDevelopmentCard(int playerNum);
        void useDevelopmentCard(int playerNum, int cardIndex, bool isTest=false);
        void initializeDeck(bool isTest=false);
        void chooseFirstRes(int playerNum);
        void addResource(int playerNum,int resourceType, int amount);
        void addPoints(int playerNum,int amount);
        void distributeResources(int diceRoll);

        //For testing
        void rollDice(int playerNum, int dice);
    };
}
#endif // CATAN_HPP