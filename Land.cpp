/*
ID:207192246
Mail: ShayNamir@gmail.com
*/
#include "Land.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
namespace ariel{
    // Constructor
    Land::Land(){
        this->number = 0;
        this->resource = 0;
        // Initialize all spots to empty
        for (int i = 0; i < 6; ++i) {
            settlementSpots[i] = Spot();// An empty spot
            roadSpots[i] = Spot();// An empty spot
        }
    }
    Land::Land( int number, int resource){
        this->number = number;
        this->resource = resource;
        // Initialize all spots to empty
        for (int i = 0; i < 6; ++i) {
            settlementSpots[i] = Spot();// An empty spot
            roadSpots[i] = Spot();// An empty spot
        }
    }
    int Land::getNumber(){
        return this->number;
    }
    int Land::getResource(){
        return this->resource;
    }
    string Land::getResourceName(){
        switch (this->resource)
        {
        case WOOD:
            return "Wood";
        case BRICK:
            return "Brick";
        case SHEEP:
            return "Sheep";
        case WHEAT:
            return "Wheat";
        case IRON:
            return "Iron";
        case DESERT:
            return "Desert";
        default:
            return "Unknown";
        }
    }
    bool Land::isSpotTaken(bool isRoad,int spotIndex){
        if(isRoad)
            return roadSpots[spotIndex].isTaken();
        return settlementSpots[spotIndex].isTaken();
    }

    int Land::getOwner(bool isRoad,int spotIndex){
        // Check if the spot is taken
        if (!isSpotTaken(isRoad,spotIndex))
            throw std::invalid_argument("The spot is not taken");
        
        if(isRoad)
            return roadSpots[spotIndex].getOwner();
        
        return settlementSpots[spotIndex].getOwner();
    }
    Spot& Land::getSpot(bool isRoad, int index){
        if(isRoad)
            return roadSpots[index];
        return settlementSpots[index];
    }
    int Land::closeAdding(int index, int add) const{
        int ans = index + add;
        if (ans < 0) 
            return ans+6;
        if (ans >= 6)
            return ans-6;
        return ans;
    }
    bool Land::canPlaceRoad(int playerNum, int spotIndex){
        
        //Road to the road
        int spotIndexNeighbor= this->closeAdding(spotIndex,1);//Right
        if(this->isSpotTaken(true,spotIndexNeighbor)){
            if(this->getOwner(true,spotIndexNeighbor)==playerNum)
                return true;
        }

        spotIndexNeighbor= this->closeAdding(spotIndex,-1);//Left
        if(this->isSpotTaken(true,spotIndexNeighbor)){
            if(this->getOwner(true,spotIndexNeighbor)==playerNum)
                return true;
        }

        // Settlement to road
        spotIndexNeighbor= this->closeAdding(spotIndex,1);//Right
        if(this->isSpotTaken(false,spotIndexNeighbor)){
            if(this->getOwner(false,spotIndexNeighbor)==playerNum)
                return true;
        }

        spotIndexNeighbor= this->closeAdding(spotIndex,-1);//Left
        if(this->isSpotTaken(false,spotIndexNeighbor)){
            if(this->getOwner(false,spotIndexNeighbor)==playerNum)
                return true;
        }
        return false;
    }
    void Land::placeRoad(int playerNum, int spotIndex){
        /*
        
        // Check if can place road
        if(!canPlaceRoad(player,spotIndex))
            throw std::invalid_argument("Can't place road here");
        */
        
        // Place the road
        roadSpots[spotIndex].placeRoad(playerNum);
        
    }
    int Land::canPlaceSettlement(int playerNum, int spotIndex){
        // Hard no: 0
        // No:1
        // Yes:2
        //2,1
        //Check if there are a settlement or a city near
        int neighborIndex = closeAdding(spotIndex,-1);
        int neighborIndex2 = closeAdding(spotIndex,+1);
        if(isSpotTaken(false,neighborIndex2)||isSpotTaken(false,neighborIndex)||isSpotTaken(false,spotIndex))
            return 0;// Hard no

        //Check for a road to the spot (in the same player)
        neighborIndex = closeAdding(spotIndex,-1);
        if((isSpotTaken(true,spotIndex)&&getOwner(true,spotIndex)==playerNum) 
        || (isSpotTaken(true,neighborIndex)&&getOwner(true,neighborIndex)==playerNum)){
            return 2;//Yes
        }

        return 1;//No
    }
    void Land::placeSettlement(int playerNum, int spotIndex){
        /*
        // Check if can place settlement
        if(canPlaceSettlement(player,spotIndex)==0)
            throw std::invalid_argument("Can't place settlement here");
        */

        // Place the settlement
        settlementSpots[spotIndex].placeSettlement(playerNum);
    }
    void Land::placeCity(int playerNum, int spotIndex){
        // Check if the spot is taken by the player and is a settlement
        Spot& spot = getSpot(false,spotIndex);
        int spotStr = spot.getStructure();
        if(spotStr==NOTHING)
            throw std::invalid_argument("There is nothing in the spot");
        if(spotStr==ROAD)
            throw std::invalid_argument("There is a road in the spot - Error in the board, in spot: "+std::to_string(spotIndex));
        if(spotStr==CITY)
            throw std::invalid_argument("There is already a city in the spot");

        // Check if the player is the owner of the spot
        if(spot.getOwner()!=playerNum)
            throw std::invalid_argument("You are not the owner of this settlement");

        // Place the city
        spot.placeCity();
    }
/*
    void Land::distributeResources(int diceRoll){
        // Check if the land has the number of the dice roll
        if(this->number!=diceRoll)
            return;
        
        // Check if the land is a desert
        if(this->resource==DESERT)
            return;
        
        // Distribute resources to the players
        for (int i = 0; i < 6; ++i) {
            if(settlementSpots[i].isTaken()){
                settlementSpots[i].getOwner().addResource(this->resource,settlementSpots[i].getStructure()==CITY?2:1);
            }
        }
    }
*/
    void Land::printLand(){
        /*
        std::string resource_name;
        switch (this->resource) {
            case WOOD:
                resource_name = "Wood";
                break;
            case BRICK:
                resource_name = "Brick";
                break;
            case SHEEP:
                resource_name = "Sheep";
                break;
            case WHEAT:
                resource_name = "Wheat";
                break;
            case IRON:
                resource_name = "Iron";
                break;
            case DESERT:
                resource_name = "Desert";
                break;
            default:
                resource_name = "Unknown";
                break;
        }

        // Hexagon representation
        const std::string top = "  ____  ";
        const std::string middle_top = " /      \\ ";
        const std::string middle = "/        \\";
        const std::string middle_bottom = "\\        /";
        const std::string bottom = " \\____/ ";

        // Center the resource and number inside the hexagon
        std::string resource_display = resource_name.substr(0, 6); // Ensure resource fits in width
        std::ostringstream oss;
        oss << std::setw(2) << std::setfill(' ') << this->number;
        std::string number_display = oss.str();

        std::string resource_line = " /" + resource_display + "\\ ";
        std::string number_line = "/  " + number_display + "  \\";
        
        // Print the hexagon with the resource and number
        std::cout << top << std::endl;
        std::cout << resource_line << std::endl;
        std::cout << number_line << std::endl;
        std::cout << middle_bottom << std::endl;
        std::cout << bottom << std::endl;
        */
        string resource;
        switch (this->resource)
        {
        case WOOD:
            resource = "Wood";
            break;
        case BRICK:
            resource = "Brick";
            break;
        case SHEEP:
            resource = "Sheep";
            break;
        case WHEAT:
            resource = "Wheat";
            break;
        case IRON:
            resource = "Iron";
            break;
        case DESERT:
            resource = "Desert";
            break;
        default:
            resource = "Unknown";
            break;
        }
        // Print the land
        std::cout << resource<<":"<<this->number<<" ";
        
    }

    bool Land::isSett(int playerNum){
        /*
        
        */
        for(size_t i=0;i<6;i++){
            if(playerNum == settlementSpots[i].getOwner()&&settlementSpots[i].isCollectable()==false){
                settlementSpots[i].collect();
                return true;
                i--;
            }
        }
        return false;
    }

}