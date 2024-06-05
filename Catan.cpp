/*
ID:207192246
Mail: ShayNamir@gmail.com
*/

#include "Catan.hpp"
#include <iostream>
#include <stdexcept>

using namespace std;
namespace ariel{
    //std::vector<DevCard> ariel::Catan::deck; // Initialize the static variable
    
    // Constructor
    Catan::Catan(Player& p1, Player& p2, Player& p3, bool isTest){
        //cout << "Entering the Catan constructor" << endl;
        players.push_back(&p1);
        players.push_back(&p2);
        players.push_back(&p3);
        
        if(isTest)
            this->board = Board(true);
        else
            this->board = Board();

        ChooseStartingPlayer(isTest);
        // Initialize the deck of development cards
        initializeDeck(isTest);
    }
    // Destructor
    Catan::~Catan() {
    // Nothing to clean up, but we need a destructor for completeness
    }
    void Catan::placeRoad(int playerNum, int landIndex, int spotIndex){
        
        // Check if it's the player's turn
        if (this->getTurn() != playerNum)
            throw std::invalid_argument("It's not your turn");

        // Check if the player has enough resources
        if ((players[playerNum-1]->getResource(WOOD) < 1 || players[playerNum-1]->getResource(BRICK) < 1))
            throw std::invalid_argument("You don't have enough resources to place a road");
        //cout << "Player " << p.getName() << " has " << p.getResource(WOOD) << " wood and " << p.getResource(BRICK) << " brick" << endl;
        // put the road on the board
        this->board.placeRoad(playerNum, landIndex, spotIndex);

        // If no exception was thrown, the road was placed successfully
        
        // Deduct the resources from the player
        players[playerNum-1]->removeResource(WOOD, 1);
        players[playerNum-1]->removeResource(BRICK, 1);
        
        // Print the updated board
        cout << players[playerNum-1]->getName()<<" placed road successfully (" << landIndex << ", " << spotIndex << ")" << endl;
    }

    void Catan::placeSettlement(int playerNum, int landIndex, int spotIndex){
        
        // Check if it's the player's turn
        if (this->getTurn() != this->players[playerNum-1]->getPlayerNumber()){
            //cout<<"-------------Not your turn"<<endl;
            throw std::invalid_argument("It's not your turn");
        }
        
        // If the start of the game, the player can place a settlement wherever he wants
        if (players[playerNum-1]->getPoints()<2) {
            // put the settlement on the board
            this->board.plaseSettlement(playerNum,players[playerNum-1]->getPoints()<2 ,landIndex, spotIndex);

            // If no exception was thrown, the settlement was placed successfully
            
            // Increase the player's points
            addPoints(playerNum,1);
            // Add to the player the road resources
            players[playerNum-1]->addResource(WOOD, 1);
            players[playerNum-1]->addResource(BRICK, 1);

            // Print the updated board
            cout << players[playerNum-1]->getName()<<" placed settlement successfully (" << landIndex << ", " << spotIndex << ")" << endl;
            return;
        }
        // Check if the player has enough resources
        if (players[playerNum-1]->getResource(WOOD) < 1 || players[playerNum-1]->getResource(BRICK) < 1||players[playerNum-1]->getResource(SHEEP) < 1||players[playerNum-1]->getResource(WHEAT) < 1)
            throw std::invalid_argument("You don't have enough resources to place a settlement");
        
        // put the settlement on the board
        this->board.plaseSettlement(playerNum,players[playerNum-1]->getPoints()<2, landIndex, spotIndex);

        // If no exception was thrown, the road was placed successfully
        
        // Deduct the resources from the player
        players[playerNum-1]->removeResource(WOOD, 1);
        players[playerNum-1]->removeResource(BRICK, 1);
        players[playerNum-1]->removeResource(SHEEP, 1);
        players[playerNum-1]->removeResource(WHEAT, 1);

        // Increase the player's points
        players[playerNum-1]->addPoints(1);

        // Print the updated board
        cout << players[playerNum-1]->getName()<<" placed settlement successfully (" << landIndex << ", " << spotIndex << ")" << endl;
    }

    void Catan::placeCity(int playerNum, int landIndex, int spotIndex){
        // Check if it's the player's turn
        if (this->getTurn() != playerNum)
            throw std::invalid_argument("It's not your turn");

        // Check if the player has enough resources
        if (players[playerNum-1]->getResource(WHEAT) < 2 || players[playerNum-1]->getResource(IRON) < 3)
            throw std::invalid_argument("You don't have enough resources to place a city");
        
        // put the city on the board
        this->board.placeCity(playerNum, landIndex, spotIndex);

        // If no exception was thrown, the city was placed successfully
        // Deduct the resources from the player
        players[playerNum-1]->removeResource(WHEAT, 2);
        players[playerNum-1]->removeResource(IRON, 3);

        // Increase the player's points
        players[playerNum-1]->addPoints(1);

        // Print the updated board
        cout << players[playerNum-1]->getName()<<" placed city successfully (" << landIndex << ", " << spotIndex << ")" << endl;
    }
    void Catan::rollDice(int playerNum){
        // Check if it's the player's turn
        if (this->getTurn() != playerNum)
            throw std::invalid_argument("It's not your turn");

        // Roll the dice
        srand(time(0));
        int dice1 = rand() % 6 + 1;
        int dice2 = rand() % 6 + 1;
        int sum = dice1 + dice2;
        
        // Check if the sum is 7
        if (sum == 7) {
            // Move the robber
            cout << "The sum is 7, all players should lose half of their resources" << endl;
            
            //Every player with more than 7 resources will lose half of his resources
            for(size_t i=0;i<this->players.size();i++)
                players[i]->rolledSeven();   
            
            // Move the robber
            //this->moveRobber();
            return;
        }
        // Give the resources to the players
        distributeResources(sum);

        // Print the result
        cout << players[playerNum-1]->getName() << " rolled " << sum << " (" << dice1 << " + " << dice2 << ")" << endl;
    }
    //For tsting
    void Catan::rollDice(int playerNum, int dice){
        // Check if it's the player's turn
        if (this->getTurn() != playerNum)
            throw std::invalid_argument("It's not your turn");
        int sum = dice;
        int dice1 = dice-1;
        int dice2=1;
        if (sum == 7) {
            // Move the robber
            cout << "The sum is 7, all players should lose half of their resources" << endl;
            
            //Every player with more than 7 resources will lose half of his resources
            for(size_t i=0;i<this->players.size();i++)
                players[i]->rolledSeven();   
            
            // Move the robber
            //this->moveRobber();
            return;
        }
        // Give the resources to the players
        //this->board.distributeResources(sum);
        distributeResources(sum);

        // Print the result
        cout << players[playerNum-1]->getName() << " rolled " << sum << " (" << dice1 << " + " << dice2 << ")" << endl;
    }
    void Catan::endTurn(int playerNum){
        // Check if it's the player's turn
        if (this->getTurn() != playerNum)
            throw std::invalid_argument("It's not your turn");

        // Change the turn
        //cout<<"Turn: "<<this->turn<<endl;
        this->turn = (this->turn % 3) + 1;
        cout<<"-----Turn :"<<this->turn<<endl;
        cout << "It's now " << this->players[this->turn - 1]->getName() << "'s turn" << endl;
        //cout<<"Turn: "<<this->turn<<endl;
        checkWinner(playerNum);
    }
    bool Catan::checkWinner( int playerNum){
        // Check if the player has 10 points
        if (players[playerNum-1]->getPoints() >= 10) {
            cout << players[playerNum-1]->getName() << " is the winner! with " << players[playerNum-1]->getPoints() << " points" << endl;
            return true;
        }
        return false;
    }
    void Catan::tradeResorces(int p1, int p2, int res1, int res2, int amount1, int amount2){
        //From p1 to p2
        // Check if it's the player's turn
        if (this->getTurn() != p1)
            throw std::invalid_argument("It's not your turn");
        
        // Check if the players are different
        if (p1 == p2)
            throw std::invalid_argument("You can't trade with yourself");
        
        // Check if player 1 has the resources
        if (players[p1-1]->getResource(res1) < amount1)
            throw std::invalid_argument("You don't have enough resources to trade");
        // Check if player 2 has the resources
        if (players[p2-1]->getResource(res2) < amount2)
            throw std::invalid_argument("The other player doesn't have enough resources to trade");
        
        // Trade the resources
        //cout<<players[p1]->getName()<<": before remooving "<<players[p1]->getResource(res1)<<endl; 
        players[p1-1]->removeResource(res1, amount1);
        //cout<<players[p1]->getName()<<": after remooving "<<players[p1]->getResource(res1)<<endl;
        //cout<<players[p1]->getName()<<": before adding "<<players[p1]->getResource(res2)<<endl;
        players[p1-1]->addResource(res2, amount2);
        //cout<<players[p1]->getName()<<": after adding "<<players[p1]->getResource(res2)<<endl;
        //cout<<players[p2]->getName()<<": before remooving "<<players[p2]->getResource(res2)<<endl;
        players[p2-1]->removeResource(res2, amount2);
        //cout<<players[p2]->getName()<<": after remooving "<<players[p2]->getResource(res2)<<endl;
        //cout<<players[p2]->getName()<<": before adding "<<players[p2]->getResource(res1)<<endl;
        players[p2-1]->addResource(res1, amount1);
        //cout<<players[p2]->getName()<<": after adding "<<players[p2]->getResource(res1)<<endl;

        // Print the result
        cout << players[p1-1]->getName() << " traded " << amount1 << " " << res1 << " with " << players[p2-1]->getName() << " for " << amount2 << " " << res2 << endl;
    }
    void Catan::printPoints(){
        for(size_t i=0;i<this->players.size();i++)
            cout << this->players[i]->getName() << " has: " << this->players[i]->getPoints() << " points" << endl;
    }
    
    void Catan::initializeDeck(bool isTest) {
       /*
       The deck should contain:
            3 knights
            4 victory points
            1 road building
            1 monopoly  
            1 year of plenty
            SUM = 10
       */

        if(isTest){
            // Clear the existing deck if any
            deck.clear();
            deck.push_back(DevCard(KNIGHT));
            deck.push_back(DevCard(KNIGHT));
            deck.push_back(DevCard(KNIGHT));
            deck.push_back(DevCard(VICTORY_POINT));
            deck.push_back(DevCard(VICTORY_POINT));
            deck.push_back(DevCard(VICTORY_POINT));
            deck.push_back(DevCard(VICTORY_POINT));
            deck.push_back(DevCard(ROAD_BUILDING));
            deck.push_back(DevCard(MONOPOLY));
            deck.push_back(DevCard(YEAR_OF_PLENTY));
            return;
        }
        // Clear the existing deck if any
        deck.clear();

        // 3 knights
        for (size_t i = 0; i < 3; i++) {
            deck.push_back(DevCard(KNIGHT));
        }
        // 4 victory points
        for (size_t i = 0; i < 4; i++) {
            deck.push_back(DevCard(VICTORY_POINT));
        }
        // 1 road building
        deck.push_back(DevCard(ROAD_BUILDING));
        // 1 monopoly
        deck.push_back(DevCard(MONOPOLY));
        // 1 year of plenty
        deck.push_back(DevCard(YEAR_OF_PLENTY));

        // Shuffle the deck
        auto rng = std::default_random_engine(time(nullptr));
        std::shuffle(deck.begin(), deck.end(), rng);
    }

    void Catan::buyDevelopmentCard(int playerNum) {
    // Check if it's the player's turn
    if (this->getTurn() != playerNum)
        throw std::invalid_argument("It's not your turn");
    
    // Check if the player has enough resources
    if (players[playerNum-1]->getResource(WHEAT) < 1 || players[playerNum-1]->getResource(SHEEP) < 1 || players[playerNum-1]->getResource(IRON) < 1)
        throw std::invalid_argument("You don't have enough resources to buy a development card");

    if (deck.empty())
        throw std::out_of_range("No more development cards available in the deck");
    
    DevCard card = deck.back();// Get the last card in the deck
    deck.pop_back();// Remove the card from the deck

    players[playerNum-1]->buyDevelopmentCard(card);// Add the card to the player's deck

    // Deduct the resources from the player
    players[playerNum-1]->removeResource(WHEAT, 1);
    players[playerNum-1]->removeResource(SHEEP, 1);
    players[playerNum-1]->removeResource(IRON, 1);

}

    void Catan::useDevelopmentCard(int playerNum, int cardIndex, bool isTest) {
        
        // Check if it's the player's turn
        if (this->getTurn() != playerNum)
            throw std::invalid_argument("It's not your turn");

        // Check if the player has the card
        if (cardIndex < 0 || cardIndex >= players[playerNum-1]->getCardCount())
            throw std::invalid_argument("Invalid card index");
        
        bool isUsed = players[playerNum-1]->getCardAt(cardIndex).isUsed();
        if (isUsed)
            throw std::invalid_argument("The card has already been used");

        // Use the card
        int type = players[playerNum-1]->useDevelopmentCard(cardIndex);
        if (type == KNIGHT) {
            //Do nothing
            if(players[playerNum-1]->numOfNightOpened()>2){
                players[playerNum-1]->addPoints(2);//If the player has more than 2 knights he gets 2 points
                cout << players[playerNum-1]->getName() << " Has the biggest army and got 2 points" << endl;
            }
            // Print the result
            cout << players[playerNum-1]->getName() << " used a knight card" << endl;
        }
        else if (type == VICTORY_POINT) {
            // Increase the player's points
            players[playerNum-1]->addPoints(1);
            // Print the result
            cout << players[playerNum-1]->getName() << " got 1 point" << endl;
        }
        else if (type == ROAD_BUILDING) {
            // Give the player 2 roads
            players[playerNum-1]->addResource(WOOD, 2);
            players[playerNum-1]->addResource(BRICK, 2);

            // Ask the player to choose 2 spots to place the roads
            int landIndex1, spotIndex1, landIndex2, spotIndex2;
            if(isTest){
                landIndex1=2;
                spotIndex1=1;
                landIndex2=0;
                spotIndex2=0;
            }
            else{
                cout << "Choose the first spot to place the road: " << endl;
                cin >> landIndex1 >> spotIndex1;
                cout << "Choose the second spot to place the road: " << endl;
                cin >> landIndex2 >> spotIndex2;
            }

            // Build the roads
            this->placeRoad(playerNum, landIndex1, spotIndex1);
            this->placeRoad(playerNum, landIndex2, spotIndex2);

            // Print the result
            cout << players[playerNum-1]->getName() << " placed 2 roads successfully" << endl;
        }
        else if (type == MONOPOLY) {//Woods
            int resourceType;
            if(isTest)
                resourceType=WOOD;
            else{
                // Ask the player to choose a resource type
                cout << "Choose a resource type to monopolize: 0: WOOD, 1: BRICK, 2: SHEEP, 3: WHEAT, 4: IRON" << endl;
                cin >> resourceType;
                if (resourceType < 0 || resourceType > 4)
                    throw std::invalid_argument("Invalid resource type");
            }
            // Get the total amount of the resource
            int total = 0;
            for (size_t i = 0; i < this->players.size(); i++) {
                //Skip the current player
                if (i == static_cast<size_t>(playerNum-1))
                    continue;
                int current = this->players[i]->getResource(resourceType); 
                this->players[i]->removeResource(resourceType, current);
                total += current;
                cout<<"Took "<<current<<" resources from "<<this->players[i]->getName()<<endl;
            }
            players[playerNum-1]->addResource(resourceType, total);
            // Print the result
            cout << players[playerNum-1]->getName() << " got " << total << " in total  " << endl;
        }
        else if (type == YEAR_OF_PLENTY) {//WOOD and BRICK
            int resourceType1, resourceType2;
            if(isTest){
                resourceType1=WOOD;
                 resourceType2=BRICK;
            }
            else{
            // Ask the player to choose 2 resource types
            cout << "Choose 2 resource types to get: 0: WOOD, 1: BRICK, 2: SHEEP, 3: WHEAT, 4: IRON" << endl;
            cin >> resourceType1 >> resourceType2;
            }
            // Asumming the player will enter valid resource types
            players[playerNum-1]->addResource(resourceType1, 1);
            players[playerNum-1]->addResource(resourceType2, 1);

            // Print the result
            cout << players[playerNum-1]->getName() << " got 1 " << resourceType1 << " and 1 " << resourceType2 << endl;
        }
    }
    void Catan::printDevelopmentCards(int playerNum){
    //Print in order
    for(int i=0;i<players[playerNum]->getCardCount();i++)
        cout << "Card " << i << ": " << players[playerNum]->getCardAt(i).getType() << " Used: " << players[playerNum]->getCardAt(i).isUsed() << endl;
    if(players[playerNum]->getCardCount()==0)
        cout << "You dont have a development cards" << endl;
}
    void Catan::ChooseStartingPlayer(bool isTest){
        if(isTest){
            this->turn = 1;
            return;
        }
        //Randomly choose the starting player
        cout<<"Starting the game, Selecting the starting player randomly..."<<endl;
        srand(time(0));
        int startingPlayer = rand() % 3 + 1;// 1: p1, 2: p2, 3: p3
        if(startingPlayer == 1)
            cout << "The starting player is " << players[0]->getName() << endl;
        else if(startingPlayer == 2)
            cout << "The starting player is " << players[1]->getName() << endl;
        else
            cout << "The starting player is " << this->players[2]->getName() << endl;

        this->turn = startingPlayer;
    }
    void Catan::printBoard(){
    this->board.printBoard();
}
    Player& Catan::getCurrentPlayer(){
        // Ensure that 'turn' is a valid index for the 'players' vector
        if (turn >= 1 && static_cast<size_t>(turn) <= players.size()) {
            return *players[turn - 1];
        } else {
            throw std::out_of_range("Invalid turn value");
        }
    }

    int Catan::getTurn()const{
        return this->turn;
    }
    Player& Catan:: getPlayerByName(string name){
        for(size_t i=0;i<players.size();i++){
            if(name == players[i]->getName())
                return *players[i];
        }
        throw std::invalid_argument("There is noplayer with that name");
    }

    void Catan::chooseFirstRes(int playerNum){
        //if(players[playerNum-1]->getPoints()>1)
            //throw std::invalid_argument("Not the first turn");
        
        //board.chooseFirstRes(playerNum);
        string print="";
        int count=1;
        vector<vector<int>> option;
        for (int i = 0; i < BOARD_SIZE; ++i) {
            if(getBoard().getLand(i).isSett(playerNum)&&getBoard().getLand(i).getResource()!= DESERT ){//Set and not desert
                print+=to_string(count);
                print+=". "+getBoard().getLand(i).getResourceName()+"\n";
                option.push_back({i,getBoard().getLand(i).getResource()});
                count++;
            }
        }
        cout << "Player " << players[playerNum-1]->getName() << ", please choose 2 resources to collect: (n1 n2)" << endl
             << print;
        int res, res2;
        cin >> res >> res2;
        //Assuming the player will enter valid numbers
        players[playerNum-1]->addResource(option[res-1][1],1);//Add the resource
        players[playerNum-1]->addResource(option[res2-1][1],1);//Add the resource
        //cout<< "Player " << players[playerNum]->getName() << " has collected 1 " << getBoard().getLand(option[res-1][0]).getResourceName()<<endl;

    }
    Board &Catan::getBoard(){
        return this->board;
    }
    void Catan::addResource(int playerNum, int resourceType, int amount){
        players[playerNum-1]->addResource(resourceType, amount);
    }
    void Catan::distributeResources(int diceRoll){
        for(size_t i=0;i<BOARD_SIZE;i++){
            Land land = board.getLand(i);
            if(land.getNumber()==diceRoll){
                for(size_t j=0;j<6;j++){
                    cout<<"Check spot: "<<j<<"in land "<<i<<endl;
                    if(land.getSpot(false,j).isTaken()){
                        int ownerID = land.getSpot(false, j).getOwner();
                        Player* owner = players[ownerID - 1];
                        int resource = land.getResource();
                        int structure = land.getSpot(false, j).getStructure();
                        cout<<"Found in land "<<i<<" spot "<<j<<" owner "<<owner->getName()<<" resource "<<resource<<" structure "<<structure<<endl;
                        
                        if (structure == CITY){
                            cout<< "Player " << owner->getName() << " got 2 " << land.getResourceName() << " from his city" << endl;
                            owner->addResource(resource, 2);
                        }
                        else {
                            cout<< "Player " << owner->getName() << " got 1 " << land.getResourceName() << " from his settlement" << endl;
                            owner->addResource(resource, 1);
                        }

                    }
                }
            }
        }
    }
    Player& Catan::getPlayer(int num){
        return *players[num-1];
    }
    void Catan::addPoints(int playerNum,int amount){
        players[playerNum-1]->addPoints(amount);
    }
    void Catan::tradeDevCard(int p1, int p2, int cardIndex1, int cardIndex2){
        // Check if it's the player's turn
        if (this->getTurn() != p1)
            throw std::invalid_argument("It's not your turn");
        
        // Check if the players are different
        if (p1 == p2)
            throw std::invalid_argument("You can't trade with yourself");
        
        // Check if player 1 has the card
        if (cardIndex1 < 0 || cardIndex1 >= players[p1-1]->getCardCount())
            throw std::invalid_argument("Invalid card index");
        // Check if player 2 has the card
        if (cardIndex2 < 0 || cardIndex2 >= players[p2-1]->getCardCount())
            throw std::invalid_argument("Invalid card index");

        //Check if one of the card is used
        if (players[p1-1]->getCardAt(cardIndex1).isUsed() || players[p2-1]->getCardAt(cardIndex2).isUsed())
            throw std::invalid_argument("One of the cards is already used");
        
        // Trade the cards
        DevCard card1 = players[p1-1]->getCardAt(cardIndex1);
        DevCard card2 = players[p2-1]->getCardAt(cardIndex2);
        players[p1-1]->deleteDevCard(cardIndex1);
        players[p2-1]->deleteDevCard(cardIndex2);
        cout<<"&&& card1: "<<card1.getTypeName()<<" card2: "<<card2.getTypeName()<<endl;
        players[p1-1]->buyDevelopmentCard(card2);
        players[p2-1]->buyDevelopmentCard(card1);

        // Print the result
        cout << players[p1-1]->getName() << " traded with " << players[p2-1]->getName() << endl;
    }
}