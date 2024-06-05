/*
ID:207192246
Mail: ShayNamir@gmail.com
*/
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include "Catan.hpp"
#include "Player.hpp"
#include "Board.hpp"

using namespace std;
using namespace ariel;

#include <iostream>
int main()
{
    cout<<endl;
    cout<<endl;
    cout << "Welcome to Catan! made by Shay Namir." << endl;

    Player p1("Shay");
    Player p2("Eli");
    Player p3("Elon");

    Catan catan(p1, p2, p3);
    catan.printBoard();

    for (int i = 0; i < 3; i++)
    {
        int cp= catan.getTurn();// The current player

        // Ask the player to insert the location (land and spot) of the settlement and the road.
        // The player should insert the location in the following format: "land spot"
        cout << "Player " << catan.getPlayer(cp).getName() << ", please insert the location of the settlement: (land spot) ";
        int land, spot;
        cin >> land >> spot;
        catan.placeSettlement(cp, land, spot);
        cout << "Player " << catan.getPlayer(cp).getName() << ", please insert the location of the road: (land spot)";
        cin >> land >> spot;
        catan.placeRoad(cp, land, spot);
        //catan.chooseFirstRes(cp);

        // The second settlement and road
        cout << "Player " << catan.getPlayer(cp).getName() << ", please insert the location of the second settlement: (land spot)";
        cin >> land >> spot;
        catan.placeSettlement(cp, land, spot);
        cout << "Player " << catan.getPlayer(cp).getName() << ", please insert the location of the second road: (land spot)";
        cin >> land >> spot;
        catan.placeRoad(cp, land, spot);
        catan.chooseFirstRes(cp);

        // The second player's turn
        catan.endTurn(cp);
    }
    // The game has started
    int action = -1;
    while (catan.checkWinner(catan.getTurn())|| action!=0)
    {
        int cp= catan.getTurn();// The current player
        cout << "Player: " << catan.getPlayer(cp).getName() << " please choose an action: " << endl
             << "1. Roll the dice" << endl
             << "2. Build a road" << endl
             << "3. Build a settlement" << endl
             << "4. Build a city" << endl
             << "5. Buy a development card" << endl
             << "6. Use a development card" << endl
             << "7. Trade" << endl
             << "8. Print details" << endl
             << "9. End turn" << endl
             << " In each stage type 0 to exite"<<endl;

        cin >> action;
        switch (action)
        {
        case 1:
            // Choosing the number - for testing 
            //cout<<"Insert tne number that you want the dice will be:"<< endl;
            //int dice;
            //cin>> dice; 
            catan.rollDice(cp);
            break;
        case 2:
        {
            cout << "Please insert the location of the road: (land spot)";
            int land, spot;
            cin >> land >> spot;
            catan.placeRoad(cp, land, spot);
        }
        break;
        case 3:
        {
            cout << "Please insert the location of the settlement: (land spot)";
            int land, spot;
            cin >> land >> spot;
            catan.placeSettlement(cp, land, spot);
        }
        break;
        case 4:
        {
            cout << "Please insert the location of the city: (land spot)";
            int land, spot;
            cin >> land >> spot;
            catan.placeCity(cp, land, spot);
        }
        break;
        case 5:
            catan.buyDevelopmentCard(cp);
            break;
        case 6:
        {
            catan.getPlayer(cp).printDevelopmentCards();
            cout << "Please insert the index of the development card: ";
            int index;
            cin >> index;
            catan.useDevelopmentCard(cp, index);
        }
        break;
        case 7:
        {
            cout<<"What do you want to trade?"<<endl;
            cout<<"1. Resources"<<endl;
            cout<<"2. Development cards"<<endl;
            int input;
            cin>>input;
            switch (input)
            {
            case 1:
            {
                cout<<"The players are:"<<endl;
                for (int i = 0; i < 3; i++)
                {
                    cout<<i+1<<". "<<catan.getPlayer(i).getName()<<endl;
                }
                cout << "Please insert the number of the player you want to trade with: ";
                int p2;
                cin >> p2;

                cout << "Please insert the resource you want to trade: " << endl
                    << "1. Wood" << endl
                    << "2. Brick" << endl
                    << "3. Wheat" << endl
                    << "4. Sheep" << endl
                    << "5. Ore" << endl;
                int res1, res2, amount1, amount2;
                cin >> res1;
                cout << "Please insert the amount of the resource you want to trade: ";
                cin >> amount1;
                cout << "Please insert the resource you want to get: " << endl
                    << "1. Wood" << endl
                    << "2. Brick" << endl
                    << "3. Wheat" << endl
                    << "4. Sheep" << endl
                    << "5. Ore" << endl;
                cin >> res2;
                cout << "Please insert the amount of the resource you want to get: ";
                cin >> amount2;
                catan.tradeResorces(cp, p2, res1, res2, amount1, amount2);
            }
            break;
            case 2:
            {
                cout << "Please insert the number of the player you want to trade with: ";
                int p2;
                cin >> p2;
                cout<<"Your development cards are:"<<endl;
                catan.printDevelopmentCards(cp);
                cout<<"The other player's development cards are:"<<endl;
                catan.printDevelopmentCards(p2);
                cout << "Please insert the index of the development card you want to trade: ";
                int index;
                cin >> index;
                cout << "Please insert the index of the development card you want to get: ";
                int index2;
                cin >> index2;
                catan.tradeDevCard(cp, p2, index,index2);
            }
        }
        break;
        case 8:
        {
            int input = 0;
            cout << "Please choose what to print: " << endl
                 << "1. Points" << endl
                 << "2. Board" << endl
                 << "3. Development cards" << endl;
            cin >> input;
            switch (input)
            {
            case 1:
                catan.printPoints();
                break;
            case 2:
                catan.printBoard();
                break;
            case 3:
                catan.printDevelopmentCards(cp);
                break;
            default:
                cout << "Invalid input" << endl;
                break;
            }
        }
        break;
        case 9:
            catan.endTurn(cp);
            break;
        case 0:
            std::cout << "Exiting program..." << std::endl;
            exit(0); // Exit the program with a status code of 0
        default:
            cout << "Invalid action" << endl;
            break;
        }
    }

    return 0;
    }   
}