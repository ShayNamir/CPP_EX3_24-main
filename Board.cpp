/*
ID:207192246
Mail: ShayNamir@gmail.com
*/

#include "Board.hpp"
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>
#include <iomanip>
#include <sstream>


namespace ariel {
    
    // Constructor - generate a random board
    Board::Board(bool isTest) {
        // Initialize all lands to empty
        if(isTest){
            /*
                    0) Iron 10, 1) Sheep 2, 2) Wood 9
                3) Wheat 12, 4) Brick 6, 5) Sheep 4 6) Brick 10
            7) Wheat 9, 8) Wood 11, 9) Desert 0, 10) Wood 3 11) Iron 8
                12) Wood 8, 13) Iron 3, 14) Wheat 4, 15) Sheep 5
                    16) Brick 5, 17) Wheat 6, 18) Sheep 11
            */
            lands[0] = Land(10,IRON);
            lands[1] = Land(2,SHEEP);
            lands[2] = Land(9,WOOD);
            lands[3] = Land(12,WHEAT);
            lands[4] = Land(6,BRICK);
            lands[5] = Land(4,SHEEP);
            lands[6] = Land(10,BRICK);
            lands[7] = Land(9,WHEAT);
            lands[8] = Land(11,WOOD);
            lands[9] = Land(0,DESERT);
            lands[10] = Land(3,WOOD);
            lands[11] = Land(8,IRON);
            lands[12] = Land(8,WOOD);
            lands[13] = Land(3,IRON);
            lands[14] = Land(4,WHEAT);
            lands[15] = Land(5,SHEEP);
            lands[16] = Land(5,BRICK);
            lands[17] = Land(6,WHEAT);
            lands[18] = Land(11,SHEEP);
            return;
        }
        else{
            for (int i = 0; i < BOARD_SIZE; ++i) {
                lands[i] = Land();
            }

            std::vector<Land> randomBoard = generateRandomBoard();
            // Copy the generated random board to the lands array
            for (size_t i = 0; i < randomBoard.size(); ++i) {
                lands[i] = randomBoard[i];
            }
        }
        
    }
    Board::~Board(){
        //delete[] lands;
    }
    int Board::closeAdding(int index, int add) const{
        int ans = index + add;
        if (ans < 0) 
            return ans+6;
        if (ans >= 6)
            return ans-6;
        return ans;
    }

    // Helper function to generate a random board for the Catane game
    std::vector<Land> Board::generateRandomBoard() {
        // Define resources and their counts (excluding the desert)
        std::vector<int> resources = {
            WOOD, WOOD, WOOD, WOOD,  // 4 forests
            BRICK, BRICK, BRICK,     // 3 hills
            SHEEP, SHEEP, SHEEP, SHEEP, // 4 pastures
            WHEAT, WHEAT, WHEAT, WHEAT, // 4 fields
            IRON, IRON, IRON,        // 3 mountains
            DESERT // 1 desert
        };

        // Define the numbers for the tiles (excluding the desert)
        std::vector<int> numbers = { 
            2, 3, 3, 4, 4, 5, 5, 6, 6, 8, 8, 9, 9, 10, 10, 11, 11, 12
        };

        // Shuffle resources
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::shuffle(resources.begin(), resources.end(), std::default_random_engine(seed));

        // Shuffle numbers
        std::shuffle(numbers.begin(), numbers.end(), std::default_random_engine(seed));

        int numberIndex = 0;
        std::vector<Land> ans(BOARD_SIZE);  // Resize the vector to the board size
        // Assign resources and numbers to lands
        for (int i = 0; i < BOARD_SIZE; ++i) {
            int resource = resources[i];
            int number;
            if (resource == DESERT)
                number = 0;  // desert
            else
                number = numbers[numberIndex++];
            ans[i] = Land(number, resource);
        }
        return ans;
    }
    
    void Board::placeRoad(int playerNum, int landIndex, int spotIndex){
        // Check if the spot is taken
        if(isPlaceTaken(true,landIndex,spotIndex))
            throw std::invalid_argument("This spot is already taken");


        //Check if there are a settlement or a city near the road
        if(lands[landIndex].getSpot(false,spotIndex).isTakenBy(playerNum)||lands[landIndex].getSpot(false,(spotIndex+1)%6).isTakenBy(playerNum)){
            //Place the road
            this->lands[landIndex].placeRoad(playerNum,spotIndex);
            return;
        }
        
        
            
        //cout<<"Board::placeRoad, spotIndex: "<<spotIndex<<"landIndex: "<<landIndex<<endl<<endl;
        int landIndex2 = -1;
        int spotIndex2 = -1;
        
        {// Neighbors
        //check if the road is between two lands
        if(spotIndex == 0){// Top left neighbor
            //4,5,6,8,9,10,11,12,13,14,15,16,17,18
            if ((landIndex>=4 && landIndex<=6)||(landIndex>=8&& landIndex<=15)){//4,5,6 ,16,17,18
                landIndex2 = landIndex-4;
                spotIndex2 = 3;
            }
            if(landIndex>=8&& landIndex<=15){//8-15
                landIndex2 = landIndex-5;
                spotIndex2 = 3;
            }
        }
        if(spotIndex==1){//Top right neighbor
            //3,4,5,7,8,9,10,12,13,14,15,16,17,18
            if ((landIndex>=3 && landIndex<=5)||(landIndex>=16&& landIndex<=18)){//3,4,5 ,16,17,18
                landIndex2 = landIndex-3;
                spotIndex2 = 4;
            }
            if(landIndex>=7&&landIndex!= 11){//7-18 without 11
                landIndex2 = landIndex-4;
                spotIndex2 = 4;
            }
        }
        if(spotIndex==2){// Right neighbor
            //0,1,3,4,5,7,8,9,10,12,13,14,16,17
            if(!(landIndex==2||landIndex==6||landIndex==11||landIndex==15||landIndex==18)){
                landIndex2 = landIndex+1;
                spotIndex2 = 5;
            }
        }
        if(spotIndex==3){// Bottom right neighbor
            //0,1,2,3,4,5,6,7,8,9,10,12,13,14
            if (landIndex>=3 && landIndex<=10){//3-10
                landIndex2 = landIndex+5;
                spotIndex2 = 0;
            }
            if((landIndex<=2)||(landIndex<=14 && landIndex>=12)){//0,1,2,12,13,14
                landIndex2 = landIndex+4;
                spotIndex2 = 0;
            }
        }
        if(spotIndex == 4){// Bottom left neighbor
            //0-6, 8-11,13-15,
            if (landIndex>=4 && landIndex<=11 && landIndex!= 7){//4-11 withot 7
                landIndex2 = landIndex+4;
                spotIndex2 = 1;
            }
            if((landIndex<=3)||(landIndex>=13&& landIndex<=15)){//0-3, 13-15
                landIndex2 = landIndex+3;
                spotIndex2 = 1;
            }
        }
        if(spotIndex==5){// Left neighbor
            //Withot: 0,3,7,12,16
            if(!(landIndex==0||landIndex==3||landIndex==7||landIndex==12||landIndex==16)){
                landIndex2 = landIndex-1;
                spotIndex2 = 2;
            }
        }
        }
        //cout<<"landIndex: "<<landIndex2<<"spotIndex: "<<spotIndex2<<endl;
        //cout<<"Board::placeRoad, landIndex2: "<<landIndex2<<"spotIndex2: "<<spotIndex2<<endl<<endl;
        
        //Place road
        //Check if there are a road near the road
        if(lands[landIndex].getSpot(true,(spotIndex+1)%6).isTakenBy(playerNum)||lands[landIndex].getSpot(true,(spotIndex-1)%6).isTakenBy(playerNum)){
            //Place the road
            this->lands[landIndex].placeRoad(playerNum,spotIndex);
            //Check for a neighbor
            if(spotIndex2 != -1)
                this->lands[landIndex2].placeRoad(playerNum,spotIndex2);
            return;
        }
        if(spotIndex2 == -1){//No neighbor
            //Check around the bord
            {
            bool placeAround=false;
            if(spotIndex==0){
                //cout<<"Enter here: landIndex: "<<landIndex<<"spotIndex: "<<spotIndex<<endl;
                if(landIndex==3)
                    placeAround=lands[landIndex-3].getSpot(true,5).isAround(playerNum);
                else if(landIndex==7)
                    placeAround=lands[landIndex-4].getSpot(true,5).isAround(playerNum);
                else if(landIndex==1||landIndex==2)
                    placeAround=lands[landIndex-1].getSpot(true,1).isAround(playerNum);
            }

            else if(spotIndex==1&&(landIndex<=1))
                placeAround=lands[landIndex+1].getSpot(true,1).isAround(playerNum);
                
            else if(spotIndex==2){
                if(landIndex==2)
                    placeAround=this->lands[landIndex+4].getOwner(true,1)==playerNum;
                else if(landIndex==6)
                    placeAround=this->lands[landIndex+5].getOwner(true,1)==playerNum;
            }

            else if(spotIndex==3){
                if(landIndex==11)
                    placeAround=lands[landIndex+4].getSpot(true,2).isAround(playerNum);
                else if(landIndex==15)
                    placeAround=lands[landIndex+3].getSpot(true,2).isAround(playerNum);
            }

            else if(spotIndex==4){
                if(landIndex ==17|landIndex==18)
                    placeAround=lands[landIndex-1].getSpot(true,3).isAround(playerNum);
                else if(landIndex==7)
                    placeAround=lands[landIndex+5].getSpot(true,5).isAround(playerNum);
                else if(landIndex==12)
                    placeAround=lands[landIndex+5].getSpot(true,5).isAround(playerNum);
            }

            else if(spotIndex==5){
                if(landIndex==0)
                    placeAround=lands[landIndex+3].getSpot(true,0).isAround(playerNum);
                else if(landIndex==3)
                    placeAround=lands[landIndex+4].getSpot(true,0).isAround(playerNum);
            }
            //cout<< "placeAround: "<<placeAround<<endl;
            if(placeAround){
                //cout<<"Place the road, placeAround = "<<placeAround<<endl;
                //Place the road
                this->lands[landIndex].placeRoad(playerNum,spotIndex);
            }
            else
                throw std::invalid_argument("Can't place a road at the position ("+to_string(landIndex)+","+to_string(spotIndex)+")");
            }
        }
        
        else{// Has neighbor
            bool me = this->lands[landIndex].canPlaceRoad(playerNum,spotIndex);
            bool neighbor = this->lands[landIndex2].canPlaceRoad(playerNum,spotIndex2);
            if(me||neighbor){//Place the road in both
                this->lands[landIndex].placeRoad(playerNum,spotIndex);
                this->lands[landIndex2].placeRoad(playerNum,spotIndex2);
            }
            else
                throw std::invalid_argument("Can't place a road at the position ("+to_string(landIndex)+","+to_string(spotIndex)+")");
        }
    }
    vector<vector<int>> Board::getSNeighbors(int landIndex,int spotIndex){
        int landIndex2 = -1;
        int spotIndex2 = -1;
        int landIndex3 = -1;
        int spotIndex3 = -1;
        // Neighbors
        {
            if(spotIndex == 0 &&landIndex !=0 &&landIndex !=3&&landIndex !=7){// Top left neighbor. All Without 0,3,7
                //One neighbor
                //1,2,4,5,6,8,9,10,11,13,14,15,17,18
                if(landIndex !=12&&landIndex !=16){
                    landIndex2= landIndex-1;
                    spotIndex2=2;
                }
                //4,5,6,8,9,10,11,12,13,14,15,16,17,18
                if(landIndex>3&&landIndex !=7){
                    spotIndex3=4;
                    //4,5,6,16,17,18
                    if((landIndex>=4&&landIndex<=6)||(landIndex>=16))
                        landIndex3= landIndex-4;
                    else
                        landIndex3= landIndex-5;
                }
            }
            
            if(spotIndex == 1 &&landIndex >2){// Top neighbor. All Without 0,1,2
                //One neighbor
                //3,6,7,11
                if(landIndex ==3){
                    landIndex2= landIndex-3;
                    spotIndex2=5;
                }
                else if(landIndex ==6||landIndex ==7){
                    landIndex2= landIndex-4;
                    spotIndex2=5;
                    if(landIndex ==6)
                        spotIndex2=3;
                }
                else if(landIndex ==11){
                    landIndex2= landIndex-5;
                    spotIndex2=3;
                }

                // Two neighbors - the rest
                else if(landIndex==4||landIndex==5||landIndex>=16){
                    landIndex2=landIndex-4;
                    spotIndex2=3;

                    landIndex3=landIndex-3;
                    spotIndex3=5;
                }
                //8-10, 12-15
                else{
                    landIndex2=landIndex-5;
                    spotIndex2=3;

                    landIndex3=landIndex-4;
                    spotIndex3=5;
                }
            }

            if(spotIndex==2&&landIndex!=2&&landIndex!=6&&landIndex!=11){// Top right neighbor. All Without 2,6,11
                //One neighbor
                //0,1,15,18
                if(landIndex==0||landIndex==1){
                    landIndex2=landIndex+1;
                    spotIndex2= 0;
                }
                else if(landIndex==15||landIndex==18){
                    if(landIndex==15){
                        landIndex2=11;
                        spotIndex2= 4;
                    }
                    else{
                        landIndex2=15;
                        spotIndex2= 4;
                    }
                }
                //Two neighbors
                else{
                    landIndex2=landIndex+1;
                    spotIndex2= 0;
                    spotIndex3= 4;
                    if(landIndex<=5||landIndex>=16){
                        landIndex3=landIndex-3;
                    }
                    else
                        landIndex3=landIndex-4;
                }
            }
            
            if(spotIndex==3&&landIndex!=11&&landIndex!=15&&landIndex!=18){// Bottom right neighbor. All Without 2,6,11
            // One neighbor
            //2,6,16,17
            if(landIndex==2|| landIndex==6){
                spotIndex2 = 1;
                if(landIndex==2)
                    landIndex2 = 6;
                else
                landIndex2 = 11;
            }
            else if(landIndex==16|| landIndex==17){
                landIndex2= landIndex+1;
                spotIndex2=5;
            }
            //Two neighbors
            else{
                if(landIndex<=1||landIndex>=12){
                    landIndex2=landIndex+1;
                    spotIndex2 = 5;

                    landIndex3 = landIndex+4;
                    spotIndex3 = 1;
                }
                else{
                    landIndex2=landIndex+1;
                    spotIndex2 = 5;

                    landIndex3 = landIndex+5;
                    spotIndex3 = 1;
                }
            }
            }
        
            if(spotIndex==4&&landIndex!=16&&landIndex!=17&&landIndex!=18){// Bottom neighbor. All Without 16,17,18
                // One neighbor
                //7,11,12,15
                if(landIndex==11||landIndex==12){
                    landIndex2=landIndex+4;
                    spotIndex2=0;
                }
                else if(landIndex==7){
                    landIndex2=landIndex+5;
                    spotIndex2=0;
                }
                else if(landIndex==15){
                    landIndex2=landIndex+3;
                    spotIndex2=0;
                }
                // Two neighbors
                else{
                    if(landIndex<=2||landIndex>=13){
                        landIndex2=landIndex+4;
                        spotIndex2=0;

                        landIndex3=landIndex+3;
                        spotIndex3=2;
                    }
                    else{
                        landIndex2=landIndex+5;
                        spotIndex2=0;

                        landIndex3=landIndex+4;
                        spotIndex3=2;
                    }
                }
            }
        
            if(spotIndex==5&&landIndex!=12&&landIndex!=16&&landIndex!=7){// Bottom left neighbor. All Without 7,12,16
                // One neighbor
                //0,3,17,18
                if(landIndex==0){
                    landIndex2=3;
                    spotIndex2=1;
                }
                else if(landIndex==3){
                    landIndex2=7;
                    spotIndex2=1;   
                }
                else if (landIndex==17||landIndex==18){
                    landIndex2=landIndex-1;
                    spotIndex2 = 3;
                }
                // Two neighbors
                else{
                    landIndex2=landIndex-1;
                    spotIndex2 = 3;
                    if(landIndex==1||landIndex==2||landIndex>=13){
                        landIndex2=landIndex+3;
                        spotIndex2 = 1;
                    }
                    else{
                        landIndex2=landIndex+4;
                        spotIndex2 = 1;
                    }
                }
            }
        }
        return {{landIndex2,spotIndex2},{landIndex3,spotIndex3}};
    }
    void Board::plaseSettlement(int playerNum,bool firsTurn, int landIndex, int spotIndex){
         // Check if the spot is taken
        if(isPlaceTaken(false,landIndex,spotIndex))
            throw std::invalid_argument("This spot is already taken");
        
        
        vector<vector<int>> neighbors = getSNeighbors(landIndex,spotIndex);
        //Can be up to 3 neighbors
        int landIndex2 = neighbors[0][0];
        int spotIndex2 = neighbors[0][1];
        int landIndex3 = neighbors[1][0];
        int spotIndex3 = neighbors[1][1];

        
        if(spotIndex2==-1 && spotIndex3==-1){//No neighbor
            int canPlace =this->lands[landIndex].canPlaceSettlement(playerNum,spotIndex);
            //cout<<"canPlace: "<<canPlace<<endl;
            // If the first turn
            if(firsTurn&&canPlace!=0){// Hard no
                //Place the settlement
                this->lands[landIndex].placeSettlement(playerNum,spotIndex);
            }
            else if(canPlace>1){
                //Place the settlement
                this->lands[landIndex].placeSettlement(playerNum,spotIndex);
            }
            else
                throw std::invalid_argument("Can't place a settlement11 at the position("+to_string(landIndex)+","+to_string(spotIndex)+")");
        }
        else if(spotIndex2==-1){// One neighbor (number 3)
            int canPlace = this->lands[landIndex].canPlaceSettlement(playerNum,spotIndex);
            canPlace*=this->lands[landIndex3].canPlaceSettlement(playerNum,spotIndex3);

            // If the first turn
            if(firsTurn&&canPlace!=0){// Hard no
                //Place the settlement
                this->lands[landIndex].placeSettlement(playerNum,spotIndex);
                this->lands[landIndex3].placeSettlement(playerNum,spotIndex3);
            }

            else if(canPlace>1){
                //Place the settlement
                this->lands[landIndex].placeSettlement(playerNum,spotIndex);
                this->lands[landIndex3].placeSettlement(playerNum,spotIndex3);
            }
            else
                throw std::invalid_argument("Can't place a settlement12 at the position("+to_string(landIndex)+","+to_string(spotIndex)+")");
        }
        else if(spotIndex3==-1){// One neighbor (number 2)
            int canPlace = this->lands[landIndex].canPlaceSettlement(playerNum,spotIndex);
            canPlace *=this->lands[landIndex2].canPlaceSettlement(playerNum,spotIndex2);

            // If the first turn
            if(firsTurn&&canPlace!=0){// Hard no
                //Place the settlement
                this->lands[landIndex].placeSettlement(playerNum,spotIndex);
                this->lands[landIndex2].placeSettlement(playerNum,spotIndex2);
            }

            else if(canPlace>1){
                //Place the settlement
                this->lands[landIndex].placeSettlement(playerNum,spotIndex);
                this->lands[landIndex2].placeSettlement(playerNum,spotIndex2);
            }
            else
                throw std::invalid_argument("Can't place a settlement13 at the position("+to_string(landIndex)+","+to_string(spotIndex)+") ");
        }
        else{//Both
            int canPlace = this->lands[landIndex].canPlaceSettlement(playerNum,spotIndex);
            canPlace *= this->lands[landIndex2].canPlaceSettlement(playerNum,spotIndex2);
            canPlace *= this->lands[landIndex3].canPlaceSettlement(playerNum,spotIndex3);

            // If the first turn
            if(firsTurn&&canPlace!=0){// Hard no
                //Place the settlement
                this->lands[landIndex].placeSettlement(playerNum,spotIndex);
                this->lands[landIndex2].placeSettlement(playerNum,spotIndex2);
                this->lands[landIndex3].placeSettlement(playerNum,spotIndex3);
            }

            else if(canPlace>1){
                //Place the settlement
                this->lands[landIndex].placeSettlement(playerNum,spotIndex);
                this->lands[landIndex2].placeSettlement(playerNum,spotIndex2);
                this->lands[landIndex3].placeSettlement(playerNum,spotIndex3);
            }
            else
                throw std::invalid_argument("Can't place a settlement14 at the position("+to_string(landIndex)+","+to_string(spotIndex)+")");
        }
    
    }
    void Board::placeCity(int playerNum, int landIndex, int spotIndex){
        vector<vector<int>> neighbors = getSNeighbors(landIndex,spotIndex);
        //Can be up to 3 neighbors
        int landIndex2 = neighbors[0][0];
        int spotIndex2 = neighbors[0][1];
        int landIndex3 = neighbors[1][0];
        int spotIndex3 = neighbors[1][1];
        
        this->lands[landIndex].placeCity(playerNum,spotIndex);
        if(spotIndex2==-1 && spotIndex3==-1)//No neighbor
            return;

        else if(spotIndex2==-1)// One neighbor (number 3)
            this->lands[landIndex3].placeCity(playerNum,spotIndex3);    
        
        else if(spotIndex3==-1)// One neighbor (number 2)
            this->lands[landIndex2].placeCity(playerNum,spotIndex2);
        
        else{//Both
            this->lands[landIndex2].placeCity(playerNum,spotIndex2);
            this->lands[landIndex3].placeCity(playerNum,spotIndex3);
        }
    }

/*
    void Board::distributeResources(int diceRoll){
        for (int i = 0; i < BOARD_SIZE; ++i) {
            this->lands[i].distributeResources(diceRoll);
        }
    }
*/
    void Board::printBoard(){
        /*
        const int rows[5] = {3, 4, 5, 4, 3};
        int index = 0;

        for (int row = 0; row < 5; ++row) {
            if(rows[row]==3)
                std::cout << "\t   ";
            else if(rows[row]==4)
                std::cout << "\t";
            
            if (row % 2 == 0) {
                std::cout << "    ";
            }

            // Print the top of hexagons
            for (int i = 0; i < rows[row]; ++i) {
                std::cout << "  / \\  ";
                if (i < rows[row] - 1) {
                    std::cout << " ";
                }
            }
            std::cout << std::endl;

            if(rows[row]==3)
                std::cout << "\t   ";
            else if(rows[row]==4)
                std::cout << "\t";
            
            if (row % 2 == 0) {
                std::cout << "    ";
            }

            // Print the top middle part of hexagons
            for (int i = 0; i < rows[row]; ++i) {
                std::cout << " /   \\ ";
                if (i < rows[row] - 1) {
                    std::cout << " ";
                }
            }
            std::cout << std::endl;

            if(rows[row]==3)
                std::cout << "\t   ";
            else if(rows[row]==4)
                std::cout << "\t";
            
            if (row % 2 == 0) {
                std::cout << "    ";
            }

            // Print the middle part of hexagons (resource name)
            for (int i = 0; i < rows[row]; ++i) {
                std::cout << "|" << std::setw(6) << std::left << this->lands[index].getResourceName() << "|";
                if (i < rows[row] - 1) {
                    std::cout << " ";
                }
                index++;
            }
            std::cout << std::endl;

            if(rows[row]==3)
                std::cout << "\t   ";
            else if(rows[row]==4)
                std::cout << "\t";
            
            if (row % 2 == 0) {
                std::cout << "    ";
            }

            index -= rows[row];

            // Print the bottom middle part of hexagons (number)
            for (int i = 0; i < rows[row]; ++i) {
                std::cout << " \\ " << std::setw(2) << lands[index].getNumber() << " / ";
                if (i < rows[row] - 1) {
                    std::cout << " ";
                }
                index++;
            }
            std::cout << std::endl;

            if(rows[row]==3)
                std::cout << "\t   ";
            else if(rows[row]==4)
                std::cout << "\t";
            
            if (row % 2 == 0) {
                std::cout << "    ";
            }

            // Print the bottom of hexagons
            for (int i = 0; i < rows[row]; ++i) {
                std::cout << "  \\/  ";
                if (i < rows[row] - 1) {
                    std::cout << " ";
                }
            }
            std::cout << std::endl;
        }
        */
        for (int i = 0; i < BOARD_SIZE; ++i) {
            if(i==0||i==3||i==7||i==12||i==16)
                cout << endl;
            if(i==7)
                cout<<"\t";
            if(i==0||i==16)//Tab twice
                cout << "\t\t";
            else if(i==3||i==12)//Tab once
                cout << "\t    ";
            this->lands[i].printLand();
        }
        cout<<endl;
        
    }
    bool Board::isPlaceTaken(bool isRoad,int landIndex, int spotIndex){
        return lands[landIndex].isSpotTaken(isRoad,spotIndex);
    }
    Land Board::getLand(int index) const{
        return lands[index];
    }
}
/*
     __     __      __
   /   \   /   \   /   \
  |Wood | |Iron | |Brick|
   \ 3 /   \ 8 /   \ 6 /
     --     --      --
*/