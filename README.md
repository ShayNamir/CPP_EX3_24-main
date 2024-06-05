# Catan Game Implementation

## Overview

This project implements a digital version of the popular board game "Settlers of Catan". The game involves players building settlements, cities, and roads, collecting resources, and trading to achieve victory points. The objective is to reach a set number of victory points to win the game.

## Rules of the Game

- **Players**: 3 players are involved in each game.
- **Turn Order**: Players take turns in a sequential manner. The starting player is chosen randomly at the beginning.
- **Resources**: The game features five types of resources: Wood, Brick, Sheep, Wheat, and Iron.
- **Development Cards**: Players can buy use, and trade development cards which provide various benefits like knights, victory points, road building, monopoly, and year of plenty.
- **Winning Condition**: The first player to reach 10 victory points wins the game.

## Class Hierarchy

1. **Catan**:
   - Manages the game flow, players, and interactions with the board.
   - Methods include setting up the game, handling turns, and determining the winner.

2. **Board**:
   - Represents the game board consisting of 19 lands.
   - Methods include placing roads, settlements, and cities, and distributing resources.

3. **Land**:
   - Represents a single hexagonal land on the board with resource type and number.
   - Methods include placing settlements and roads, and checking ownership.

4. **Player**:
   - Represents a player in the game with a name, resources, and development cards.
   - Methods include managing resources, development cards, and points.

5. **DevCard**:
   - Represents development cards in the game.
   - Methods include getting card type and using the card.

6. **Spot**:
   - Represents a spot on a land where structures like roads, settlements, or cities can be placed.
   - Methods include placing and checking structures.

## Libraries Used

- Standard C++ Library: for basic functionalities such as input/output, strings, vectors, and algorithms.
- `<iostream>`, `<vector>`, `<string>`, `<map>`, and `<algorithm>`: specific headers used for various functionalities in the game.

## Methods Description

### Catan Class

- **Catan(Player& p1, Player& p2, Player& p3, bool isTest=false)**: Constructor to initialize the game with three players.
- **~Catan()**: Destructor.
- **Board& getBoard()**: Returns the game board.
- **int getTurn() const**: Returns the current turn.
- **Player& getPlayerByName(std::string name)**: Returns a player by name.
- **Player& getPlayer(int num)**: Returns a player by number.
- **void placeSettlement(int playerNum, int landIndex, int spotIndex)**: Places a settlement for a player.
- **void placeRoad(int playerNum, int landIndex, int spotIndex)**: Places a road for a player.
- **void placeCity(int playerNum, int landIndex, int spotIndex)**: Places a city for a player.
- **void rollDice(int playerNum)**: Rolls dice for resource distribution.
- **void ChooseStartingPlayer(bool isTest=false)**: Chooses the starting player.
- **void endTurn(int playerNum)**: Ends the current player's turn.
- **bool checkWinner(int playerNum)**: Checks if the player has won.
- **void tradeResources(int p1, int p2, int res1, int res2, int amount1, int amount2)**: Trades resources between players.
- **void tradeDevCard(int p1, int p2, int cardIndex1, int cardIndex2)**: Trades development cards between players.
- **void printPoints()**: Prints the points of all players.
- **void printWinner()**: Prints the winner of the game.
- **void printBoard()**: Prints the game board.
- **void printDevelopmentCards(int playerNum)**: Prints the development cards of a player.
- **Player& getCurrentPlayer()**: Returns the current player.
- **void buyDevelopmentCard(int playerNum)**: Buys a development card for a player.
- **void useDevelopmentCard(int playerNum, int cardIndex, bool isTest=false)**: Uses a development card for a player.
- **void initializeDeck(bool isTest=false)**: Initializes the deck of development cards.
- **void chooseFirstRes(int playerNum)**: Chooses the first resource for a player.
- **void addResource(int playerNum, int resourceType, int amount)**: Adds resources to a player.
- **void addPoints(int playerNum, int amount)**: Adds points to a player.
- **void distributeResources(int diceRoll)**: Distributes resources based on the dice roll.
- **void rollDice(int playerNum, int dice)**: Rolls a specific dice value (for testing).

### Board Class

- **Board(bool isTest=false)**: Constructor to initialize the board.
- **Land getLand(int index) const**: Returns a land by index.
- **bool isPlaceTaken(bool isRoad, int landIndex, int spotIndex)**: Checks if a place is taken.
- **void placeRoad(int playerNum, int landIndex, int spotIndex)**: Places a road.
- **void placeSettlement(int playerNum, bool firstTurn, int landIndex, int spotIndex)**: Places a settlement.
- **void placeCity(int playerNum, int landIndex, int spotIndex)**: Places a city.
- **void printBoard()**: Prints the board.
- **vector<vector<int>> getSNeighbors(int landIndex, int spotIndex)**: Gets the neighbors of a spot.

### Land Class

- **Land()**: Default constructor.
- **Land(int number, int resource)**: Constructor to initialize a land with a number and resource.
- **int getNumber()**: Returns the number of the land.
- **int getResource()**: Returns the resource type of the land.
- **std::string getResourceName()**: Returns the name of the resource.
- **Spot& getSpot(bool isRoad, int index)**: Returns a spot on the land.
- **bool isSpotTaken(bool isRoad, int spotIndex)**: Checks if a spot is taken.
- **int getOwner(bool isRoad, int spotIndex)**: Returns the owner of a spot.
- **void placeSettlement(int playerNum, int spotIndex)**: Places a settlement.
- **void placeRoad(int playerNum, int spotIndex)**: Places a road.
- **bool canPlaceRoad(int playerNum, int spotIndex)**: Checks if a road can be placed.
- **int canPlaceSettlement(int playerNum, int spotIndex)**: Checks if a settlement can be placed.
- **void placeCity(int playerNum, int spotIndex)**: Places a city.
- **void printLand()**: Prints the land.
- **bool isSett(int playerNum)**: Checks if a player has a settlement.

### Player Class

- **Player()**: Default constructor.
- **Player(std::string name)**: Constructor to initialize a player with a name.
- **~Player()**: Destructor.
- **std::string getName() const**: Returns the player's name.
- **int getPoints() const**: Returns the player's points.
- **int getPlayerNumber() const**: Returns the player's number.
- **void addResource(int resourceType, int amount)**: Adds resources to the player.
- **void removeResource(int resourceType, int amount)**: Removes resources from the player.
- **int getResource(int resourceType) const**: Returns the amount of a resource.
- **int getResourcesCount() const**: Returns the total count of resources.
- **void rolledSeven()**: Handles the event of rolling a seven.
- **void buyDevelopmentCard(DevCard& card)**: Buys a development card.
- **void deleteDevCard(int index)**: Deletes a development card.
- **DevCard& getCardAt(int num)**: Returns a development card by index.
- **int useDevelopmentCard(int cardIndex)**: Uses a development card.
- **int getCardCount() const**: Returns the count of development cards.
- **int numOfNightOpened()**: Returns the number of knight cards played.
- **void addPoints(int amount)**: Adds points to the player.
- **void printResources() const**: Prints the player's resources.
- **void printDevelopmentCards()**: Prints the player's development cards.
- **void clearAllDevCards()**: Clears all development cards (for testing).

### DevCard Class

- **DevCard(int type)**: Constructor to initialize a development card with a type.
- **~DevCard()**: Destructor.
- **int getType() const**: Returns the type of the card.
- **std::string getTypeName() const**: Returns the name of the card type.
- **bool isUsed() const**: Checks if the card is used.
- **int useDevelopmentCard()**: Uses the card.

### Spot Class

- **Spot()**: Default constructor.
- **int getOwner() const**: Returns the owner of the spot.
- **void setOwner(int playerNum)**: Sets the owner of the spot.
- **void placeRoad(int playerNum)**: Places a road.
- **void placeSettlement(int playerNum)**: Places a settlement.
- **void placeCity()**: Places a city.
- **int getStructure() const**: Returns the structure on the spot.
- **bool isAround(int playerNum) const**: Checks if a player is around the spot.
- **void setStructure(const int& structure)**: Sets the structure on the spot.
- **void collect()**: Marks the spot as collectable.
- **bool isTaken() const**: Checks if the spot is taken.
- **bool isTakenBy(int playerNum) const**: Checks if the spot is taken by a specific player.
- **bool isCollectable() const**: Checks if the spot is collectable.
