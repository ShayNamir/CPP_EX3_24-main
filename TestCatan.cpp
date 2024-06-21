/*
ID:207192246
Mail: ShayNamir@gmail.com
*/
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Catan.hpp"

using namespace ariel;
using namespace std;

// Static variables for the game and players
static bool isCreated = false;
static Catan* catan = nullptr;
static Player* p1 = nullptr;
static Player* p2 = nullptr;
static Player* p3 = nullptr;

void createGame() {
    if (!isCreated) {
        p1 = new Player("Shay(1)");
        p2 = new Player("Avi(2)");
        p3 = new Player("Elon(3)");

        catan = new Catan(*p1, *p2, *p3, true); // The test mode
        catan->printBoard();

        // First stage of the game
        std::cout << "First stage" << endl;
        int cp = catan->getTurn();

        int land = 0; int spot = 0; // Assume the first settlement is at 0,1
        catan->placeSettlement(cp, land, spot);
        catan->addResource(catan->getTurn(), IRON, 1);
        land = 0; spot = 4;
        cout<<"1:";
        CHECK_THROWS(catan->placeRoad(cp, land, spot)); // Try to place a road in a spot that is not connected to the settlement
        land = 0; spot = 5; // Assume the first road is at 0,5
        catan->placeRoad(cp, land, spot);
        cout<<"2:";

        // The second settlement and road
        land = 1; spot = 1; // Assume the first settlement is at 1,1
        catan->placeSettlement(cp, land, spot);
        catan->addResource(cp, catan->getBoard().getLand(land).getResource(), 1); // Add one Sheep to the player
        land = 1; spot = 0; // Assume the first road is at 1,0
        catan->placeRoad(cp, land, spot);

        // The second player's turn
        catan->endTurn(cp);
        std::cout << endl;
        cp = catan->getTurn();

        land = 1; spot = 4;
        catan->placeSettlement(cp, land, spot);
        catan->addResource(cp, catan->getBoard().getLand(land).getResource(), 1); // Add one Sheep to the player
        land = 5; spot = 0;
        catan->placeRoad(cp, land, spot);

        // The second settlement and road
        land = 8; spot = 2;
        catan->placeSettlement(cp, land, spot);
        catan->addResource(cp, catan->getBoard().getLand(land).getResource(), 1); // Add one Wood to the player
        land = 9; spot = 0; // Assume the first road is at 0,0
        catan->placeRoad(cp, land, spot);

        // The third player's turn
        catan->endTurn(cp);
        std::cout << endl;
        cp = catan->getTurn();

        land = 18; spot = 4;
        catan->placeSettlement(cp, land, spot);
        catan->addResource(cp, catan->getBoard().getLand(land).getResource(), 1); // Add one Sheep to the player
        land = 18; spot = 4;
        catan->placeRoad(cp, land, spot);

        // The second settlement and road
        land = 17; spot = 4;
        catan->placeSettlement(cp, land, spot);
        catan->addResource(cp, catan->getBoard().getLand(land).getResource(), 1); // Add one Wood to the player
        land = 17; spot = 4; // Assume the first road is at 0,0
        catan->placeRoad(cp, land, spot);

        // End of the first stage
        std::cout<<"-Turn: "<<catan->getTurn()<<endl;
        catan->endTurn(cp);
        std::cout<<"-Turn: "<<catan->getTurn()<<endl;
        isCreated = true;
    }
}

TEST_CASE("Test Catan") {
    createGame();

    SUBCASE("Check the resources collection of the first stage") {
        //cout << "Enter resources collection of the first stage" << endl;
        // First player should have 1 Iron and 1 Sheep and 0 in the rest
        CHECK_EQ(p1->getResource(IRON), 1);
        CHECK_EQ(p1->getResource(SHEEP), 1);
        CHECK_EQ(p1->getResource(WOOD), 0);
        CHECK_EQ(p1->getResource(WHEAT), 0);
        CHECK_EQ(p1->getResource(BRICK), 0);
        // Second player should have 1 Sheep and 1 Wood and 0 in the rest
        CHECK_EQ(p2->getResource(SHEEP), 1);
        CHECK_EQ(p2->getResource(WOOD), 1);
        CHECK_EQ(p2->getResource(WHEAT), 0);
        CHECK_EQ(p2->getResource(BRICK), 0);
        CHECK_EQ(p2->getResource(IRON), 0);
        // Third player should have 1 Sheep and 1 Wheat and 0 in the rest
        CHECK_EQ(p3->getResource(SHEEP), 1);
        CHECK_EQ(p3->getResource(WHEAT), 1);
        CHECK_EQ(p3->getResource(WOOD), 0);
        CHECK_EQ(p3->getResource(BRICK), 0);
        CHECK_EQ(p3->getResource(IRON), 0);
        cout << "Check the resources collection of the first stage" << endl;
    }

    SUBCASE("Check the points collection of the first stage") {
        cout << "Enter points collection of the first stage" << endl;
        // First player should have 2 points
        CHECK_EQ(catan->getPlayer(1).getPoints(), 2);
        // Second player should have 2 points
        CHECK_EQ(catan->getPlayer(2).getPoints(), 2);
        // Third player should have 2 points
        CHECK_EQ(catan->getPlayer(3).getPoints(), 2);
    }
    
    SUBCASE("Adding 20 resources to each player"){
        for(int i=1;i< 4;i++){
            catan->addResource(i, WOOD, 20);
            catan->addResource(i, BRICK, 20);
            catan->addResource(i, SHEEP, 20);
            catan->addResource(i, WHEAT, 20);
            catan->addResource(i, IRON, 20);
        }
        CHECK_EQ(p1->getResource(IRON), 21);
        CHECK_EQ(p1->getResource(SHEEP), 21);
        CHECK_EQ(p1->getResource(WOOD), 20);
        CHECK_EQ(p1->getResource(WHEAT), 20);
        CHECK_EQ(p1->getResource(BRICK), 20);
        // Second player should have 1 Sheep and 1 Wood and 0 in the rest
        CHECK_EQ(p2->getResource(SHEEP), 21);
        CHECK_EQ(p2->getResource(WOOD), 21);
        CHECK_EQ(p2->getResource(WHEAT), 20);
        CHECK_EQ(p2->getResource(BRICK), 20);
        CHECK_EQ(p2->getResource(IRON), 20);
        // Third player should have 1 Sheep and 1 Wheat and 0 in the rest
        CHECK_EQ(p3->getResource(SHEEP), 21);
        CHECK_EQ(p3->getResource(WHEAT), 21);
        CHECK_EQ(p3->getResource(WOOD), 20);
        CHECK_EQ(p3->getResource(BRICK), 20);
        CHECK_EQ(p3->getResource(IRON), 20);


    }

    SUBCASE("Trade resources between players"){
        //Before
        int p1Wood = p1->getResource(WOOD);
        int p1Brick = p1->getResource(BRICK);
        int p2Wood = p2->getResource(WOOD);
        int p2Brick = p2->getResource(BRICK);
        //cout<<"Before, p1 wood: "<<p1Wood<<" p1 brick: "<<p1Brick<<" p2 wood: "<<p2Wood<<" p2 brick: "<<p2Brick<<endl;
        catan->tradeResorces(1,2 , WOOD, BRICK, 1, 1);//p1 gives 1 wood and gets 1 brick from p2
        //cout<<"After, p1 wood: "<<p1->getResource(WOOD)<<" p1 brick: "<<p1->getResource(BRICK)<<" p2 wood: "<<p2->getResource(WOOD)<<" p2 brick: "<<p2->getResource(BRICK)<<endl;
        //After
        CHECK_EQ(p1->getResource(WOOD), p1Wood-1);
        CHECK_EQ(p1->getResource(BRICK), p1Brick+1);
        CHECK_EQ(p2->getResource(WOOD), p2Wood+1);
        CHECK_EQ(p2->getResource(BRICK), p2Brick-1);

        //Trade that he doesn't have
        CHECK_THROWS(catan->tradeResorces(1,2 , WOOD, BRICK, 20, 1));
        //Trades what the other player doesn't have
        CHECK_THROWS(catan->tradeResorces(1,2 , WOOD, BRICK, 1, 23));

        //Trade with himself
        CHECK_THROWS(catan->tradeResorces(1,1 , WOOD, BRICK, 1, 1));

    }

    SUBCASE("Build a road"){
        //P1 (3,5) CHECKKKKKKKKK
        int p1Brick = p1->getResource(BRICK);
        int p1Wood = p1->getResource(WOOD);
        //cout<<"-Before, p1 brick: "<<p1Brick<<" p1 wood: "<<p1Wood<<endl;
        catan->placeRoad(1, 1, 1);
        catan->placeRoad(1, 0, 1);// Test in edge
        catan->placeRoad(1, 1, 2);
        catan->placeRoad(1, 2, 0);// Test in edge
        catan->placeRoad(1, 3, 0);// Test in edge
        CHECK_EQ(catan->getBoard().getLand(3).getSpot(true,0).isTakenBy(1), 1);
        
        catan->placeRoad(1, 3, 5); //(3,5)
        p1Brick-=6;
        p1Wood-=6;
        CHECK_EQ(p1->getResource(BRICK), p1Brick);
        CHECK_EQ(p1->getResource(WOOD), p1Wood);
        

        //CHECK_EQ(p1->getResource(BRICK), p1Brick-5);
        //CHECK_EQ(p1->getResource(WOOD), p1Wood-5);

        //Exception
        CHECK_THROWS(catan->placeRoad(1, 0, 1));// has already a road in this spot
        CHECK_THROWS(catan->placeRoad(1, 0, 3));// not connected to the settlement
        CHECK_THROWS(catan->placeRoad(1, 5, 0));// Belong to the other player
        CHECK_THROWS(catan->placeRoad(2, 5, 0));// Not the turn of the player
        //he now have 14 woods and 16 bricks
        //check if he can build a road
        catan->getPlayer(1).removeResource(WOOD, p1Wood);// remove the resources
        CHECK_THROWS(catan->placeRoad(1, 1, 1));// not enough resources
        catan->getPlayer(1).addResource(WOOD, 14);// return the resources
        //cout<<"-After, p1 brick: "<<p1->getResource(BRICK)<<" p1 wood: "<<p1->getResource(WOOD)<<endl;

        //Return the turn to the first player
        catan->endTurn(1);
        //Second player's turn
        catan->placeRoad(2, 5, 1);
        catan->placeRoad(2, 8, 1);
        catan->placeRoad(2, 8, 0);
        catan->placeRoad(2, 7, 1);
        catan->endTurn(2);

        //Third player's turn
        catan->placeRoad(3, 17, 3);
        catan->placeRoad(3, 17, 2);
        catan->endTurn(3);
    }
    
    SUBCASE("Build a settlement"){
        int brick = p1->getResource(BRICK);
        int wood = p1->getResource(WOOD);
        int sheep = p1->getResource(SHEEP);
        int wheat = p1->getResource(WHEAT);
        
        catan->placeSettlement(1, 2, 1);

        //Try to build a settlement in a spot that is not connected to the road
        CHECK_THROWS(catan->placeSettlement(1, 2, 3));
        //Try to build a settlement close to another settlement
        CHECK_THROWS(catan->placeSettlement(1, 1, 2));

        CHECK_EQ(p1->getResource(BRICK), brick-1);
        CHECK_EQ(p1->getResource(WOOD), wood-1);
        CHECK_EQ(p1->getResource(SHEEP), sheep-1);
        CHECK_EQ(p1->getResource(WHEAT), wheat-1);
        catan->endTurn(1);

        //Second player's turn
        brick = p2->getResource(BRICK);
        wood = p2->getResource(WOOD);
        sheep = p2->getResource(SHEEP);
        wheat = p2->getResource(WHEAT);

        catan->placeSettlement(2, 6, 0);
        catan->placeSettlement(2, 3, 5);
        CHECK_THROWS(catan->placeSettlement(2, 9, 1));// close to another settlement
        CHECK_THROWS(catan->placeSettlement(2, 6, 2));// not connected to the road
        CHECK_THROWS(catan->placeSettlement(3, 5, 0));// not the turn of the player

        CHECK_EQ(p2->getResource(BRICK), brick-2);
        CHECK_EQ(p2->getResource(WOOD), wood-2);
        CHECK_EQ(p2->getResource(SHEEP), sheep-2);
        CHECK_EQ(p2->getResource(WHEAT), wheat-2);
        catan->endTurn(2);

        //Third player's turn
        brick = p3->getResource(BRICK);
        wood = p3->getResource(WOOD);
        sheep = p3->getResource(SHEEP);
        wheat = p3->getResource(WHEAT);

        catan->placeSettlement(3, 14, 4);

        CHECK_EQ(p3->getResource(BRICK), brick-1);
        CHECK_EQ(p3->getResource(WOOD), wood-1);
        CHECK_EQ(p3->getResource(SHEEP), sheep-1);
        CHECK_EQ(p3->getResource(WHEAT), wheat-1);
        catan->endTurn(3);
    }

    SUBCASE("Build a city"){
        int brick = p1->getResource(BRICK);
        int wood = p1->getResource(WOOD);
        int sheep = p1->getResource(SHEEP);
        int wheat = p1->getResource(WHEAT);
        int iron = p1->getResource(IRON);

        catan->placeCity(1, 2, 1);

        //Try to build a city in a spot that is not connected to the settlement
        CHECK_THROWS(catan->placeCity(1, 2, 3));
        //Try to build a city close to another city
        CHECK_THROWS(catan->placeCity(1, 1, 2));
        //Try to build a city in a spot that has a settlement but not the player's
        CHECK_THROWS(catan->placeCity(1, 1, 4));

        CHECK_EQ(p1->getResource(WHEAT), wheat-2);
        CHECK_EQ(p1->getResource(IRON), iron-3);
        CHECK_EQ(p1->getResource(BRICK), brick);
        CHECK_EQ(p1->getResource(WOOD), wood);
        CHECK_EQ(p1->getResource(SHEEP), sheep);
        catan->endTurn(1);

        //Second player's turn
        brick = p2->getResource(BRICK);
        wood = p2->getResource(WOOD);
        sheep = p2->getResource(SHEEP);
        wheat = p2->getResource(WHEAT);
        iron = p2->getResource(IRON);
        //cout<<"-Before, p2 brick: "<<brick<<" p2 wood: "<<wood<<" p2 sheep: "<<sheep<<" p2 wheat: "<<wheat<<" p2 iron: "<<iron<<endl;

        catan->placeCity(2, 6, 0);
        catan->placeCity(2, 3, 5);

        CHECK_THROWS(catan->placeCity(2, 9, 1));// close to another city
        CHECK_THROWS(catan->placeCity(2, 6, 2));// not connected to the settlement
        CHECK_THROWS(catan->placeCity(3, 5, 0));// not the turn of the player


        CHECK_EQ(p2->getResource(WHEAT), wheat-4);
        CHECK_EQ(p2->getResource(IRON), iron-6);
        CHECK_EQ(p2->getResource(BRICK), brick);
        CHECK_EQ(p2->getResource(WOOD), wood);
        CHECK_EQ(p2->getResource(SHEEP), sheep);
        catan->endTurn(2);

        //Third player's turn
        brick = p3->getResource(BRICK);
        wood = p3->getResource(WOOD);
        sheep = p3->getResource(SHEEP);
        wheat = p3->getResource(WHEAT);
        iron = p3->getResource(IRON);

        catan->placeCity(3, 14, 4);

        CHECK_EQ(p3->getResource(WHEAT), wheat-2);
        CHECK_EQ(p3->getResource(IRON), iron-3);
        CHECK_EQ(p3->getResource(BRICK), brick);
        CHECK_EQ(p3->getResource(WOOD), wood);
        CHECK_EQ(p3->getResource(SHEEP), sheep);
        catan->endTurn(3);
    }

    SUBCASE("Rool the dice - collect resources for each player"){
        
        int sheep1 = p1->getResource(SHEEP);
        int sheep2 = p2->getResource(SHEEP);

        catan->rollDice(1, 2);
        CHECK_EQ(p1->getResource(SHEEP), sheep1+1);
        CHECK_EQ(p2->getResource(SHEEP), sheep2+1);
        //End turn
        catan->endTurn(1);

        int brick = p2->getResource(BRICK);
        int wheat = p3->getResource(WHEAT);
        catan->rollDice(2, 6);
        CHECK_EQ(p2->getResource(BRICK), brick+2);
        CHECK_EQ(p3->getResource(WHEAT), wheat+3);//City and settlement
        //End turn
        catan->endTurn(2);

        int iron = p2->getResource(IRON);
        int wood = p2->getResource(WOOD);
        brick = p2->getResource(BRICK);
        wheat = p2->getResource(WHEAT);
        int sheep = p2->getResource(SHEEP);

        catan->rollDice(3, 12);
        CHECK_EQ(p2->getResource(IRON), iron);
        CHECK_EQ(p2->getResource(SHEEP), sheep);
        CHECK_EQ(p2->getResource(WOOD), wood);
        CHECK_EQ(p2->getResource(WHEAT), wheat+2);//City
        CHECK_EQ(p2->getResource(BRICK), brick);

        //End turn
        catan->endTurn(3);
    }

    SUBCASE("Playing not in the turn of the player"){
        CHECK_THROWS(catan->placeSettlement(2, 1, 1));
        CHECK_THROWS(catan->placeRoad(3, 1, 1));
        CHECK_THROWS(catan->placeCity(2, 1, 1));
        CHECK_THROWS(catan->rollDice(2, 2));
        CHECK_THROWS(catan->buyDevelopmentCard(2));
    }

    SUBCASE("Buy development card resources check"){
        catan->initializeDeck(true);
        int brick = p1->getResource(BRICK);
        int wood = p1->getResource(WOOD);
        int sheep = p1->getResource(SHEEP);
        int wheat = p1->getResource(WHEAT);
        int iron = p1->getResource(IRON);

        //End turn
        catan->endTurn(1);

        brick = p2->getResource(BRICK);
        wood = p2->getResource(WOOD);
        sheep = p2->getResource(SHEEP);
        wheat = p2->getResource(WHEAT);
        iron = p2->getResource(IRON);

        catan->buyDevelopmentCard(2);
        catan->buyDevelopmentCard(2);
        CHECK_EQ(p2->getResource(BRICK), brick);
        CHECK_EQ(p2->getResource(WOOD), wood);
        CHECK_EQ(p2->getResource(SHEEP), sheep-2);
        CHECK_EQ(p2->getResource(WHEAT), wheat-2);
        CHECK_EQ(p2->getResource(IRON), iron-2);

        //End turn
        catan->endTurn(2);

        brick = p3->getResource(BRICK);
        wood = p3->getResource(WOOD);
        sheep = p3->getResource(SHEEP);
        wheat = p3->getResource(WHEAT);
        iron = p3->getResource(IRON);

        catan->buyDevelopmentCard(3);
        CHECK_EQ(p3->getResource(BRICK), brick);
        CHECK_EQ(p3->getResource(WOOD), wood);
        CHECK_EQ(p3->getResource(SHEEP), sheep-1);
        CHECK_EQ(p3->getResource(WHEAT), wheat-1);
        CHECK_EQ(p3->getResource(IRON), iron-1);

        //Check buying a card when there are no enough iron
        p3->removeResource(IRON, p3->getResource(IRON));
        CHECK_THROWS(catan->buyDevelopmentCard(3));
        p3->addResource(IRON, 20);
        //Check buying a card when there are no enough wheat
        p3->removeResource(WHEAT, p3->getResource(WHEAT));
        CHECK_THROWS(catan->buyDevelopmentCard(3));
        p3->addResource(WHEAT, 20);
        //Check buying a card when there are no enough sheep
        p3->removeResource(SHEEP, p3->getResource(SHEEP));
        CHECK_THROWS(catan->buyDevelopmentCard(3));
        p3->addResource(SHEEP, 20);

        //End turn
        catan->endTurn(3);
    }

    SUBCASE("Buy and use development card"){
        //One player buy them all
        //Add him resources
        p1->addResource(IRON, 10);
        p1->addResource(WHEAT, 10);
        p1->addResource(SHEEP, 10);
        catan->initializeDeck(true);
        p1->clearAllDevCards();
        p2->clearAllDevCards();
        p3->clearAllDevCards();

        //1. the knights second 2. the victory points 3. year of plenty 4. monopoly 5. road building
        for(int i=0;i<9;i++){
            catan->buyDevelopmentCard(1);
        }
        CHECK_NOTHROW(catan->buyDevelopmentCard(1));// No enough cards in deck
        //Print the cards
        p1->printDevelopmentCards();
        /*
        0. Year of Plenty
        1. Monopoly
        2. Road Building
        3. Victory Point
        4. Victory Point
        5. Victory Point
        6. Victory Point
        7. Knight
        8. Knight
        9. Knight
        */

       SUBCASE("Year of Plenty"){
            int wood = p1->getResource(WOOD);
            int brick = p1->getResource(BRICK);
            //Use the card
            catan->useDevelopmentCard(1, 0, true);//Got 1 wood and 1 brick
            CHECK_EQ(p1->getResource(WOOD), wood+1);
            CHECK_EQ(p1->getResource(BRICK), brick+1);
            
            //Use the card again
            CHECK_THROWS(catan->useDevelopmentCard(1, 0, true));//Already used
           //Print the cards
            p1->printDevelopmentCards();
       }

        SUBCASE("Monopoly"){
            //Delete all the resources from the players
            {
                p1->removeResource(WOOD, p1->getResource(WOOD));
                p1->removeResource(BRICK, p1->getResource(BRICK));
                p1->removeResource(SHEEP, p1->getResource(SHEEP));
                p1->removeResource(WHEAT, p1->getResource(WHEAT));
                p1->removeResource(IRON, p1->getResource(IRON));
                p1->addResource(WOOD, 1);

                p2->removeResource(WOOD, p2->getResource(WOOD));
                p2->removeResource(BRICK, p2->getResource(BRICK));
                p2->removeResource(SHEEP, p2->getResource(SHEEP));
                p2->removeResource(WHEAT, p2->getResource(WHEAT));
                p2->removeResource(IRON, p2->getResource(IRON));
                p2->addResource(WOOD, 2);

                p3->removeResource(WOOD, p3->getResource(WOOD));
                p3->removeResource(BRICK, p3->getResource(BRICK));
                p3->removeResource(SHEEP, p3->getResource(SHEEP));
                p3->removeResource(WHEAT, p3->getResource(WHEAT));
                p3->removeResource(IRON, p3->getResource(IRON));
                p3->addResource(WOOD, 3);

            }
        
            //Use the card
            std::cout<<"p2 woods: "<<p2->getResource(WOOD)<<endl;
            std::cout<<"p3 woods: "<<p3->getResource(WOOD)<<endl;
            catan->useDevelopmentCard(1, 1, true);//Got all the woods
            std::cout<<"p2 woods: "<<p2->getResource(WOOD)<<endl;
            std::cout<<"p3 woods: "<<p3->getResource(WOOD)<<endl;
            CHECK_EQ(p1->getResource(WOOD), 1+2+3);
            CHECK_EQ(p2->getResource(WOOD), 0);
            CHECK_EQ(p3->getResource(WOOD), 0);

            //try to use the card again
            CHECK_THROWS(catan->useDevelopmentCard(1, 1, true));//Already used
        }

        SUBCASE("Victory Point"){
            int points = p1->getPoints(); // Has 2 points
            //Use the card
            catan->useDevelopmentCard(1, 3, true);//Got 1 point
            catan->useDevelopmentCard(1, 4, true);//Got 1 point
            catan->useDevelopmentCard(1, 5, true);//Got 1 point
            CHECK_EQ(p1->getPoints(), points+3);

            //Use the card again
            CHECK_THROWS(catan->useDevelopmentCard(1, 3, true));//Already used
            CHECK_THROWS(catan->useDevelopmentCard(1, 4, true));//Already used
            CHECK_THROWS(catan->useDevelopmentCard(1, 5, true));//Already used
        }
    
        SUBCASE("Road Building"){
            int wood = p1->getResource(WOOD);
            int brick = p1->getResource(BRICK);
            //(2,1) (0,0)
            CHECK_FALSE(catan->getBoard().getLand(2).getSpot(true,1).isTaken());
            CHECK_FALSE(catan->getBoard().getLand(0).getSpot(true,0).isTaken());
            CHECK_EQ(catan->getBoard().getLand(3).getSpot(true,0).getOwner(), 1);
            //Use the card
            catan->useDevelopmentCard(1, 2, true);//Got 2 roads
            CHECK(catan->getBoard().getLand(2).getSpot(true,1).isTaken());
            CHECK(catan->getBoard().getLand(0).getSpot(true,0).isTaken());
            CHECK_EQ(catan->getBoard().getLand(2).getSpot(true,1).getOwner(), 1);
            CHECK_EQ(catan->getBoard().getLand(0).getSpot(true,0).getOwner(), 1);
            CHECK_EQ(p1->getResource(WOOD), wood);
            CHECK_EQ(p1->getResource(BRICK), brick);
        }
    
        SUBCASE("Knight"){
            int points = p1->getPoints(); // Has 5 points
            //Use the card
            catan->useDevelopmentCard(1, 7, true);//Got 1 knight
            catan->useDevelopmentCard(1, 8, true);//Got 1 knight
            catan->useDevelopmentCard(1, 9, true);//Got 1 knight
            CHECK_EQ(p1->getPoints(), points+2);

            //Use the card again
            CHECK_THROWS(catan->useDevelopmentCard(1, 7, true));//Already used
            CHECK_THROWS(catan->useDevelopmentCard(1, 8, true));//Already used
            CHECK_THROWS(catan->useDevelopmentCard(1, 9, true));//Already used
        }
    }
     
    SUBCASE("Trade development cards between players"){
        p1->clearAllDevCards();
        p2->clearAllDevCards();
        p3->clearAllDevCards();
        catan->initializeDeck(true);
        p1->addResource(IRON, 20);
        p1->addResource(WHEAT, 20);
        p1->addResource(SHEEP, 20);
        p2->addResource(IRON, 20);
        p2->addResource(WHEAT, 20);
        p2->addResource(SHEEP, 20);
        p1->addResource(WOOD, 1);
        p2->addResource(WOOD, 1);
        p3->addResource(WOOD, 1);
        /*
        0. Year of Plenty
        1. Monopoly
        2. Road Building
        3. Victory Point
        4. Victory Point
        5. Victory Point
        6. Victory Point
        7. Knight
        8. Knight
        9. Knight
        */

        //Before- p1 try to use card
        CHECK_THROWS(catan->useDevelopmentCard(1, 0, true));
        //std::cout<<"__________________________"<<endl;
        //Buy a card
        catan->buyDevelopmentCard(1);//Year of Plenty
        catan->endTurn(1);
        

        //Before- p2 try to use card
        CHECK_THROWS(catan->useDevelopmentCard(2, 0, true));
        //Buy a card
        catan->buyDevelopmentCard(2);//Monopoly
        catan->endTurn(2);
        catan->endTurn(3);

        //Trade
        catan->tradeDevCard(1, 2, 0, 0);//p1 gives Year of Plenty and gets Monopoly
        int p1wood = p1->getResource(WOOD);
        int sum=p1wood;
        sum+=p2->getResource(WOOD);
        sum+=p3->getResource(WOOD);

        //Uses the card
        catan->useDevelopmentCard(1, 0, true);
        //Check if the card was used
        CHECK_EQ(p1->getResource(WOOD), sum);
        CHECK_EQ(p2->getResource(WOOD), 0);
        CHECK_EQ(p3->getResource(WOOD), 0);

        //Try to trade a card that he doesn't have
        CHECK_THROWS(catan->tradeDevCard(1, 2, 0, 0));
        catan->endTurn(1);

        
        int wood = p2->getResource(WOOD);
        int brick = p2->getResource(BRICK);
        // Uses the card
        catan->useDevelopmentCard(2, 0, true);//Year of Plenty
        //Check if the card was used
        CHECK_EQ(p2->getResource(WOOD), wood+1);
        CHECK_EQ(p2->getResource(BRICK), brick+1);

        //Try to trade not in the turn of the player
        CHECK_THROWS(catan->tradeDevCard(3, 1, 0, 0));

        //trade with himself
        CHECK_THROWS(catan->tradeDevCard(2, 2, 0, 0));

        catan->endTurn(2);
        catan->endTurn(3);

        //Trade a used card
        CHECK_THROWS(catan->tradeDevCard(1, 2, 0, 0));

    }

    SUBCASE("Winning the game"){
        cout<<"-Before, p1 points: "<<p1->getPoints()<<endl;//9
        cout<<"-Before, p2 points: "<<p2->getPoints()<<endl;//6
        cout<<"-Before, p3 points: "<<p3->getPoints()<<endl;//4

        //Add points to p1
        CHECK_FALSE(catan->checkWinner(1));
        CHECK_FALSE(catan->checkWinner(2));
        CHECK_FALSE(catan->checkWinner(3));
        p1->addPoints(1);
        CHECK(catan->checkWinner(1));
        CHECK_FALSE(catan->checkWinner(2));
        CHECK_FALSE(catan->checkWinner(3));
    }
}
