#include <iostream>
#include <fstream>
#include "character.h"
#include "archer.h"
#include "knight.h"
#include "mage.h"
#include "shop.h"
using namespace std;

//Combat fuction will contain the loop for the combat scenes of the game
bool combat(Character* x, Monsters* y){
    cout << endl;
    cout << endl;
    int choice;

    //As long as either the player or the opponent has health points above 0 the loop will run
    while (x->getHealth() > 0 && y->getHealth() > 0){
        cout << "Opponent: " << y->getName() << endl;
        cout << "Health: " << y->getHealth() << endl;
        cout << "\n\n";
        cout << "Character: " << x->getName() << endl;
        cout << "Health: " << x->getHealth() << endl;
        if(x->getArchtype() == "Knight" || x->getArchtype() == "Archer"){
            cout << "Stamina: " << x->getStamina() << endl;
        }
        else{
            cout << "Mana: " << x->getMana() << endl;
        }
        cout << "--------------------------" << endl;
        cout << "Menu:" << endl;
        cout << "Character status - 1 " << endl;
        cout << "Use Consumable - 2" << endl;
        cout << "Escape - 3" << endl;
        cout << "Attack - 4" << endl;
        cout << "--------------------------" << endl;
        cout << endl;
        cout << "Enter choice: " << endl;
        cin >> choice;
        cout << endl;
        while(choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5){
            cout << "Invalid option please enter a valid choice:" << endl;
            cin >> choice;
            cout << endl;
        }

        //Will present the characters health
        if (choice == 1){
            x->status();
        }

        //Will give menu to show players items
        else if (choice == 2){
            int optP;
            x->inventory();
            cout << endl;
            cout << "Which potion would you like to use?" << endl;
            cout << "1 = hp , 2 = mana, 3 = stamina , 4 = crit , 5 = stealth, 6 = focus, 7 = exit" << endl;
            cout << "Enter choice:" << endl;
            cin >> optP;
            cout << endl;
            while(optP!= 1 && optP != 2 && optP != 3 && optP != 4 && optP!= 5 && optP != 6 && optP != 7){
                cout << "Invalid option please enter a valid choice:" << endl;
                cin >> optP;
                cout << endl;
            }
            switch (optP){
            //Health Potion
                case 1:
                    if(x->gethP() > 0){
                        x->setHealth(100);
                        x->sethP(x->gethP() - 1);
                        cout << "Drinking health potion....Health set to max" << endl;
                        break;
                    }
                    else{
                        cout << "Not enough health potions" << endl;
                        break;
                    }
            //Mana Potion
                case 2:
                    if(x->getmP() > 0){
                        x->setMana(100);
                        x->setmP(x->getmP() - 1);
                        cout << "Drinking mana potion....Mana set to max" << endl;
                        break;
                    }
                    else{
                        cout << "Not enough mana potions" << endl;
                        break;
                    }
            //Stamina Potion
                case 3:
                    if(x->getsP() > 0){
                        x->setStamina(100);
                        x->setsP(x->getsP() - 1);
                        cout << "Drinking stamina potion....Stamina set to max" << endl;
                        break;
                    }
                    else{
                        cout << "Not enough stamina potions" << endl;
                        break;
                    }
            //Critical Potion
                case 4:
                    if(x->getcP() > 0){
                        x->setCritOn(true);
                        x->setcP(x->getcP() - 1);
                        cout << "Drinking crtical potion....Next attack will be a critical hit" << endl;
                        break;
                    }
                    else{
                        cout << "Not enough critical potions" << endl;
                        break;
                        }
            //Stealth Potion
                case 5:
                    if(x->getshP() > 0){
                        x->setStealth(true);
                        x->setshP(x->getshP() - 1);
                        cout << "Drinking stealth potion....Now able to escape restricted dungeons" << endl;
                        break;
                    }
                    else{
                        cout << "Not enough stealth potions" << endl;
                        break;
                        }
            //Focus Potion
                case 6:
                    if(x->getfP() > 0){
                        x->setFocusOn(true);
                        x->setfP(x->getfP() - 1);
                        cout << "Drinking focus potion....Next attack will not miss" << endl;
                        break;
                    }
                    else{
                        cout << "Not enough focus potions" << endl;
                        break;
                        }
            //Exit
                case 7:
                    break;
                default:
                    break;
            }
        }
        //Retreat from dungeon
        else if (choice == 3){
            if(x->getMission() == 4 && x->getStealth() == false){
                cout << "Dungeon is restricted...not able to escape!!!" << endl;
            }
            else if(x->getMission() == 4 && x->getStealth() == true){
                cout << "Using stealth....successfully escaped!!!" << endl;
                x->setStealth(false);
                return false;
            }
            else if(x->getMission() == 1 || x->getMission() == 2 || x->getMission() == 3 ){
                cout << "Retreating from dungeon" << endl;
                return false;
            }
        }
        //Combat
        else if(choice == 4){
            x->attack(*y);
            if(y->getHealth() > 0){
                // Seed the random number generator
                random_device rd;
                mt19937 gen(rd());

                // Define the range
                uniform_int_distribution<> distribution(1, 10);

                // Generate a random number in the range 1-10
                int randomNumber = distribution(gen);
                if(randomNumber > 5){
                    cout << y->getName() << " attacks " << x->getName() << endl;
                    x->takeDmg(y->getAtk() - x->getDef());
                }
                else if( randomNumber == 7){
                    cout << y->getName() << " critical attacks " << x->getName() << endl;
                    x->takeDmg((y->getAtk() - x->getDef() )* 2);
                }
                else{
                    cout << y->getName() << " Has missed their attack" << endl;
                }
            }
            //Resets potion activation to false
            x->setFocusOn(false);
            x->setCritOn(false);
        }
        //Secret menu for devs, will insta kill
        else if(choice == 5){
            cout << "Instant Kill" << endl;
            y->setHealth(0);
        }
        cout << endl;
    }
    //Return true if monster has been defeated
    if(y->getHealth() <= 0){
        cout << "Congratulations you have beaten " << y->getName() << endl;
        return true;
    }
    //Return false if player is killed
    else if(x->getHealth() <= 0){
        cout << "You have been killed, returning to town" << endl;
        return false;
    }
   return false;
};

//Loads monster depending on the stage and mission of the character
void loadMission(Character* x, Shop* y){
    //Checks the stage
    if(x->getStage() == 1) {
        //Checks mission to load monster based on boss fight or regular mission, boss fight is mission = 4
        if(x->getMission() == 1){
            cout << "You are in stage 1 , mission 1, facing zombie." << endl;
            Monsters* a = new Monsters("Zombie",5, 80, 15, 10);
            //If true then the player will advance and receive rewards, false will not advance the player
            if(combat(x , a)){
                int num;
                x->setMission(2);
                x->setGold(x->getGold() + 500);
                x->setExp(x->getExp() + 50);
                if(x->getExp() >= 100){
                    num = x->getExp() / 100;
                    x->setAtk(x->getAtk() + (5 * num));
                    x->setDef(x->getDef() + (5 * num));
                    x->setLevel(x->getLevel() + (x->getExp() / 100));
                    x->setExp((x->getExp() % 100 ));
                }
                cout << "You have advanced to the next mission!" << endl;
                cout << "You have earned 50 xp" << endl;
                cout << "You have earned 500 gold" << endl;
                x->rest();
            }
            else{
                cout << "Mission Failed" << endl;
            }
        }
        else if(x->getMission() == 2){
            cout << "You are in stage 1 and mission 2, facing Skeleton." << endl;
            Monsters* a = new Monsters("Skeleton",5, 80, 15, 10);
            if(combat(x , a)){
                int num;
                x->setMission(3);
                x->setGold(x->getGold() + 500);
                x->setExp(x->getExp() + 50);
                if(x->getExp() >= 100){
                    num = x->getExp() / 100;
                    x->setAtk(x->getAtk() + (5 * num));
                    x->setDef(x->getDef() + (5 * num));
                    x->setLevel(x->getLevel() + (x->getExp() / 100));
                    x->setExp((x->getExp() % 100 ));;
                }
                cout << "You have advanced to the next mission!" << endl;
                cout << "You have earned 50 xp" << endl;
                cout << "You have earned 500 gold" << endl;
                x->rest();
            }
            else{
                cout << "Mission Failed" << endl;

            }
        }
        else if(x->getMission() == 3){
            cout << "You are in stage 1 and mission 3, facing Ghoul." << endl;
            Monsters* a = new Monsters("Ghoul",5, 80, 15, 10);
            if(combat(x , a)){
                int num;
                x->setMission(4);
                x->setGold(x->getGold() + 500);
                x->setExp(x->getExp() + 50);
                if(x->getExp() >= 100){
                    num = x->getExp() / 100;
                    x->setAtk(x->getAtk() + (5 * num));
                    x->setDef(x->getDef() + (5 * num));
                    x->setLevel(x->getLevel() + (x->getExp() / 100));
                    x->setExp((x->getExp() % 100 ));
                }
                cout << "You have advanced to the next mission!" << endl;
                cout << "You have earned 50 xp" << endl;
                cout << "You have earned 500 gold" << endl;
            }
            else{
                cout << "Mission Failed" << endl;
            }
        }
        else if(x->getMission() == 4){
            cout << "You are in stage 1 and mission 4, Boss Fight ahead!!!!" << endl;
            Monsters* a = new Monsters("Boss - Dragon",10, 150, 20, 20);
            if(combat(x , a)){
                int num;
                x->setMission(1);
                x->setStage(2);
                x->setGold(x->getGold() + 1000);
                y->reset();
                x->setExp(x->getExp() + 200);
                if(x->getExp() >= 100){
                    num = x->getExp() / 100;
                    x->setAtk(x->getAtk() + (5 * num));
                    x->setDef(x->getDef() + (5 * num));
                    x->setLevel(x->getLevel() + (x->getExp() / 100));
                    x->setExp((x->getExp() % 100 ));
                }
                cout << "You have advanced to the next stage!" << endl;
                cout << "You have earned 200 xp" << endl;
                cout << "You have earned 1000 gold" << endl;
            }
            else{
                cout << "Mission Failed" << endl;
            }
        }
    }
    else if(x->getStage() == 2) {
        if(x->getMission() == 1){
            cout << "You are in stage 2 , mission 1, facing Wolf." << endl;
            Monsters* a = new Monsters("Wolf",5, 100, 25, 15);
            if(combat(x , a)){
                int num;
                x->setMission(2);
                y->reset();
                x->setGold(x->getGold() + 500);
                x->setExp(x->getExp() + 50);
                if(x->getExp() >= 100){
                    num = x->getExp() / 100;
                    x->setAtk(x->getAtk() + (5 * num));
                    x->setDef(x->getDef() + (5 * num));
                    x->setLevel(x->getLevel() + (x->getExp() / 100));
                    x->setExp((x->getExp() % 100 ));
                }
                cout << "You have advanced to the next mission!" << endl;
                cout << "You have earned 50 xp" << endl;
                cout << "You have earned 500 gold" << endl;
            }
            else{
                cout << "Mission Failed" << endl;
            }
        }
        else if(x->getMission() == 2){
            cout << "You are in stage 2 and mission 2, facing Dark Knight." << endl;
            Monsters* a = new Monsters("Dark Knight",5, 100, 25 ,15);
            if(combat(x , a)){
                int num;
                x->setMission(3);
                y->reset();
                x->setGold(x->getGold() + 500);
                x->setExp(x->getExp() + 50);
                if(x->getExp() >= 100){
                    num = x->getExp() / 100;
                    x->setAtk(x->getAtk() + (5 * num));
                    x->setDef(x->getDef() + (5 * num));
                    x->setLevel(x->getLevel() + (x->getExp() / 100));
                    x->setExp((x->getExp() % 100 ));
                }
                cout << "You have advanced to the next mission!" << endl;
                cout << "You have earned 50 xp" << endl;
                cout << "You have earned 500 gold" << endl;
            }
            else{
                cout << "Mission Failed" << endl;
            }
        }
        else if(x->getMission() == 3){
            cout << "You are in stage 2 and mission 3, facing Warlock." << endl;
            Monsters* a = new Monsters("Warlock",5, 100, 25, 15);
            if(combat(x , a)){
                int num;
                x->setMission(4);
                y->reset();
                x->setGold(x->getGold() + 500);
                x->setExp(x->getExp() + 50);
                if(x->getExp() >= 100){
                    num = x->getExp() / 100;
                    x->setAtk(x->getAtk() + (5 * num));
                    x->setDef(x->getDef() + (5 * num));
                    x->setLevel(x->getLevel() + (x->getExp() / 100));
                    x->setExp((x->getExp() % 100 ));
                }
                cout << "You have advanced to the next mission!" << endl;
                cout << "You have earned 50 xp" << endl;
                cout << "You have earned 500 gold" << endl;
            }
            else{
                cout << "Mission Failed" << endl;
            }
        }
        else if(x->getMission() == 4){
            cout << "You are in stage 2 and mission 4, Boss Fight ahead!!!!" << endl;
            Monsters* a = new Monsters("Boss - Basilisk",10, 200, 30, 25);
            if(combat(x , a)){
                int num;
                x->setMission(1);
                x->setStage(3);
                x->setGold(x->getGold() + 1000);
                y->reset();
                x->setExp(x->getExp() + 200);
                if(x->getExp() >= 100){
                    num = x->getExp() / 100;
                    x->setAtk(x->getAtk() + (5 * num));
                    x->setDef(x->getDef() + (5 * num));
                    x->setLevel(x->getLevel() + (x->getExp() / 100));
                    x->setExp((x->getExp() % 100 ));
                }
                cout << "You have advanced to the next stage!" << endl;
                cout << "You have earned 200 xp" << endl;
                cout << "You have earned 1000 gold" << endl;
            }
            else{
                cout << "Mission Failed" << endl;
            }
        }
    }
    else if(x->getStage() == 3) {
        if(x->getMission() == 1){
            cout << "You are in stage 3 , mission 1, facing Mercenary." << endl;
            Monsters* a = new Monsters("Mercenary",5, 150, 30, 20);
            if(combat(x , a)){
                int num;
                x->setMission(2);
                y->reset();
                x->setGold(x->getGold() + 500);
                x->setExp(x->getExp() + 50);
                if(x->getExp() >= 100){
                    num = x->getExp() / 100;
                    x->setAtk(x->getAtk() + (5 * num));
                    x->setDef(x->getDef() + (5 * num));
                    x->setLevel(x->getLevel() + (x->getExp() / 100));
                    x->setExp((x->getExp() % 100 ));
                }
                cout << "You have advanced to the next mission!" << endl;
                cout << "You have earned 50 xp" << endl;
                cout << "You have earned 500 gold" << endl;
            }
            else{
                cout << "Mission Failed" << endl;
            }
        }
        else if(x->getMission() == 2){
            cout << "You are in stage 3 and mission 2, facing Spider." << endl;
            Monsters* a = new Monsters("Spider",5, 150, 30, 20);
            if(combat(x , a)){
                int num;
                x->setMission(3);
                y->reset();
                x->setGold(x->getGold() + 500);
                x->setExp(x->getExp() + 50);
                if(x->getExp() >= 100){
                    num = x->getExp() / 100;
                    x->setAtk(x->getAtk() + (5 * num));
                    x->setDef(x->getDef() + (5 * num));
                    x->setLevel(x->getLevel() + (x->getExp() / 100));
                    x->setExp((x->getExp() % 100 ));
                }
                cout << "You have advanced to the next mission!" << endl;
                cout << "You have earned 50 xp" << endl;
                cout << "You have earned 500 gold" << endl;
            }
            else{
                cout << "Mission Failed" << endl;
            }
        }
        else if(x->getMission() == 3){
            cout << "You are in stage 3 and mission 3, facing Undead Samurai." << endl;
            Monsters* a = new Monsters("Undead Samurai",5, 150, 30 ,20);
            if(combat(x , a)){
                int num;
                x->setMission(4);
                y->reset();
                x->setGold(x->getGold() + 500);
                x->setExp(x->getExp() + 50);
                if(x->getExp() >= 100){
                    num = x->getExp() / 100;
                    x->setAtk(x->getAtk() + (5 * num));
                    x->setDef(x->getDef() + (5 * num));
                    x->setLevel(x->getLevel() + (x->getExp() / 100));
                    x->setExp((x->getExp() % 100 ));
                }
                cout << "You have advanced to the next mission!" << endl;
                cout << "You have earned 50 xp" << endl;
                cout << "You have earned 500 gold" << endl;
            }
            else{
                cout << "Mission Failed" << endl;
            }
        }
        else if(x->getMission() == 4){
            cout << "You are in stage 3 and mission 4, Boss Fight ahead!!!!" << endl;
            Monsters* a = new Monsters("Boss - Zombie King",10, 250, 40, 30);
            if(combat(x , a)){
                int num;
                x->setMission(1);
                x->setStage(4);
                x->setGold(x->getGold() + 1000);
                y->reset();
                x->setExp(x->getExp() + 200);
                if(x->getExp() >= 100){
                    num = x->getExp() / 100;
                    x->setAtk(x->getAtk() + (5 * num));
                    x->setDef(x->getDef() + (5 * num));
                    x->setLevel(x->getLevel() + (x->getExp() / 100));
                    x->setExp((x->getExp() % 100 ));
                }
                cout << "You have advanced to the next stage!" << endl;
                cout << "You have earned 200 xp" << endl;
                cout << "You have earned 1000 gold" << endl;
            }
            else{
                cout << "Mission Failed" << endl;
            }
        }
    }
};

//Game loop function
void gameLoop(Character* x){
    Shop* store = new Shop();
//This will check if the character is new or loaded, if character is loaded the last saved inventory of the shop will be loaded
    if(x->getNewChar() == false){
        store->loadFromFile(*x);
    }

    int choice = 0;
    int count = 0;
    cout << "--------------------------" << endl;
    cout << " Game menu: \n";
    cout << " Character Status - 1 \n";
    cout << " Visit shop - 2\n";
    cout << " Rest Character - 3\n";
    cout << " Save - 4\n";
    cout << " Exit - 5\n";
    cout << " Begin Mission - 6\n";
    cout << " Potion Inventory - 7\n";
    cout << "--------------------------" << endl;
    cout << endl;
        while(choice != 9){
            //Will print out character status
            if(choice == 1){
                x->status();
            }
            //Will access the shop and shop menu
            else if(choice == 2){
                store->status();
                cout << endl;
                cout << "--------------------------" << endl;
                cout << " Shop Menu:" << endl;
                cout << " Gold available: " << x->getGold() << endl;
                cout << " Purchase potions - 1" << endl;
                cout << " Sell Potions - 2" << endl;
                cout << " Exit store - 3" << endl;
                cout << "--------------------------" << endl;
                int opt = 0;
                int count1 = 0;
                while(opt != 8){
                    //Purchase option
                    if(opt == 1){
                        int choice2, amount;
                        cout << "Which potion would you like to buy?" << endl;
                        cout << "1 = hp , 2 = mana, 3 = stamina , 4 = crit , 5 = stealth, 6 = focus, 7 = exit" << endl;
                        cin >> choice2;
                        cout << endl;
                        if(choice2 == 1 || choice2 == 2 || choice2 == 3 || choice2 == 4 || choice2 == 5 || choice2 == 6){
                            cout << "How many would you like to buy?" << endl;
                            cin >> amount;
                            cout << endl;
                            store->purchase(choice2, amount, *x);
                            cout << endl;
                        }
                    }
                    //Sell option
                    else if(opt == 2){
                        int choice2, amount;
                        cout << "Which potion would you like to sell?" << endl;
                        cout << "1 = hp , 2 = mana, 3 = stamina , 4 = crit , 5 = stealth, 6 = focus, 7 = exit" << endl;
                        cin >> choice2;
                        cout << endl;
                        if(choice2 == 1 || choice2 == 2 || choice2 == 3 || choice2 == 4 || choice2 == 5 || choice2 == 6){
                            cout << "How many would you like to sell?" << endl;
                            cin >> amount;
                            cout << endl;
                            store->restock(choice2, amount, *x);
                            cout << endl;
                        }
                    }
                    //Exit Store
                    else if(opt == 3){
                        cout << "Thank you for shopping come again soon!" << endl;
                        break;
                    }
                    if (count1 > 0){
                        store->status();
                        cout << endl;
                        cout << "--------------------------" << endl;
                        cout << " Shop Menu:" << endl;
                        cout << " Gold available: " << x->getGold() << endl;
                        cout << " Purchase potions - 1" << endl;
                        cout << " Sell Potions - 2" << endl;
                        cout << " Exit store - 3" << endl;
                        cout << "--------------------------" << endl;
                    }
                    cout << endl;
                    cout << "Enter choice:" << endl;
                    cin >> opt;
                    while(opt != 1 && opt != 2 && opt != 3){
                        cout << "Invalid option please enter a valid choice:" << endl;
                        cin >> opt;
                        cout << endl;
                    }
                    count1++;
                    cout << endl;
                }
            }
        //Rest function
            else if(choice == 3){
                x->rest();
            }
        //Save function
            else if(choice == 4){
                x->setNewChar(false);
                x->saveToFile();
                store->saveToFile(*x);
                cout << "Progress Saved!!" << endl;
            }
        //The exit choice will give the message to the player if they want to save before the exit
            else if(choice == 5){
                int choice3;
                cout << "Would you like to save?" << endl;
                cout << " Yes - 1 / No - 2" << endl;
                cout << endl;
                cout << "Enter choice: " << endl;
                cin >> choice3;
                cout << endl;
                if(choice3 == 1){
                    x->setNewChar(false);
                    x->saveToFile();
                    store->saveToFile(*x);
                    cout << "Progress Saved!!" << endl;
                    cout << "Goodbye!" << endl;
                    choice = 9;
                    break;
                }
                else{
                    cout << "Goodbye!" << endl;
                    choice = 9;
                    break;
                }
            }
            //Begin missions, will use load function and combat loop if needed
            else if(choice == 6){
                if(x->getStage() == 4){
                    cout << "Congratulations you have beat the game!!!!" << endl;
                    exit;
                }
                loadMission(x, store);
            }
            //Access Potion Inventory
            else if(choice == 7){
                x->inventory();
            }
            if(count > 0){
                cout << endl;
                cout << "--------------------------" << endl;
                cout << " Character Status - 1 \n";
                cout << " Visit shop - 2\n";
                cout << " Rest Character - 3\n";
                cout << " Save - 4\n";
                cout << " Exit - 5\n";
                cout << " Begin Mission - 6\n";
                cout << " Potion Inventory - 7\n";
                cout << "--------------------------" << endl;
                cout << endl;
            }
            cout << "Enter choice:" << endl;
            cin >> choice;
            while(choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6 && choice != 7){
                cout << "Invalid option please enter a valid choice:" << endl;
                cin >> choice;
                cout << endl;
            }
            count++;
            cout << endl;
        }
};

int main(){

    cout << "Welcome to Dungeon Fighter" << endl;
    cout << endl;
    cout << " Main Menu:" << endl;
    cout << "--------------------------" << endl;
    cout << " New Character - Press 1" << endl;
    cout << " Load Character - Press 2 " << endl;
    cout << " Exit - Press 3 " << endl;
    cout << "--------------------------" << endl;
    cout << "Enter Choice:" << endl;

    int option;
    string name;
    cin >> option;
    cout << endl;

    // Loop for invalid choice
    while(option != 1 && option !=2 && option !=3){
        cout << "Invalid option please enter another choice:" << endl;
        cin >> option;
        cout << endl;
    }

    //New Character option
    if(option == 1){
        cout << "Enter the characters name:" << endl;
        cin >> name;
        cout << endl;
        cout << "Please select a class." << endl;
        cout << "Press 1 - Knight: This class is focused on meele combat and uses a variriety of swords to attack thier foes." << endl;
        cout << "Press 2 - Archer: This class is focused on ranged combat and uses stamina to land great damage to their foes." << endl;
        cout << "Press 3 - Mage: This class is focused on magic combat and uses spells to inflict damage on their opponents." << endl;
        int classPick;
        cin >> classPick;

        //Loop for invalid choice
        while(classPick != 1 && classPick !=2 && classPick !=3){
            cout << "Invalid option please enter another choice:" << endl;
            cin >> option;
            cout << endl;
        }

        //Knight class
        if(classPick == 1){
            Character* s = new Knight(name);
            cout << "\nCharacter created" << endl;
            cout << "Welcome " << name << endl;
            cout << endl;
            gameLoop(s);
            delete s;
        }

        //Archer class
        else if(classPick == 2){
            Character* s = new Archer(name);
            cout << "\nCharacter created" << endl;
            cout << "Welcome " << name << endl;
            cout << endl;
            gameLoop(s);
            delete s;
        }

        //Mage class
        else if(classPick == 3){
            Character* s = new Mage(name);
            cout << "\nCharacter created" << endl;
            cout << "Welcome " << name << endl;
            cout << endl;
            gameLoop(s);
            delete s;
        }
    }

    //Load option
    else if(option == 2){
        cout << "Enter the name of the file to load from." << endl;
        string fileName;
        cin >> fileName;
        cout << endl;
        Character a(fileName);
        a.loadFromFile(fileName);

        //Load Knight
        if(a.getArchtype() == "Knight"){
            cout << "Welcome back " << fileName << endl;
            cout << endl;
            Character* b = new Knight(fileName);
            b->loadFromFile(fileName);
            b->status();
            cout << endl;
            gameLoop(b);
            delete b;
        }

        //Load Mage
        else if(a.getArchtype() == "Mage"){
            cout << "Welcome back " << fileName << endl;
            cout << endl;
            Character* b = new Mage(fileName);
            b->loadFromFile(fileName);
            b->status();
            cout << endl;
            gameLoop(b);
            delete b;
        }

        //Load Archer
        else if(a.getArchtype() == "Archer"){
            cout << "Welcome back " << fileName << endl;
            cout << endl;
            Character* b = new Archer(fileName);
            b->loadFromFile(fileName);
            b->status();
            cout << endl;
            gameLoop(b);
            delete b;
        }
   }
   // Exit
        else if (option == 3){
            cout << "Goodbye!" << endl;
        }
    return 0;
}