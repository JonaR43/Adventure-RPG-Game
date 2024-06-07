#ifndef SHOP_H
#define SHOP_H
#include <iostream>
#include "character.h"
using namespace std;

class Shop{
    public:
    // The standard amount of potions available at the beginning of each stage will be 5 of each individual potion.
        Shop(){
            healthP = 5;
            manaP = 5;
            staminaP = 5;
            critP = 5;
            stealthP = 5;
            focusP = 5;
        }

    //Save and Load functions
        void saveToFile(Character& x) {
            ofstream fout;
            fout.open(x.getName() + "shop.txt");
            fout << this->healthP << endl;
            fout << this->manaP << endl;
            fout << this->staminaP << endl;
            fout << this->critP << endl;
            fout << this->stealthP << endl;
            fout << this->focusP << endl;
            fout.close();
        }
        void loadFromFile(Character& x) {
            ifstream fin;
            fin.open(x.getName() + "shop.txt");
            fin >> this->healthP;
            fin >> this->manaP;
            fin >> this->staminaP;
            fin >> this->critP;
            fin >> this->stealthP;
            fin >> this->focusP;
            fin.close();
        }

    // Will be used to give the status of potions available to purchase
        void status(){
            cout << "Potion's - (cost)" << endl;
            cout << "-------------------------------" << endl;
            cout << "Health Potions (100 gold) : " << healthP << endl;
            cout << "Mana Potions (100 gold) : " << manaP << endl;
            cout << "Stamina Potions (100 gold) : " << staminaP << endl;
            cout << "Critical Potions (150 gold) : " << critP << endl;
            cout << "Stealth Potions (500 gold) : " << stealthP << endl;
            cout << "Focus Potions (200 gold): " << focusP << endl;
            cout << "-------------------------------" << endl;
        }
    // Function used to purchase and remove potions from shop inventory
        void purchase(int choice, int amount, Character& x){
            //1 = hp , 2 = mana, 3 = stamina , 4 = crit , 5 = stealth, 6 = focus
            switch(choice){
                case 1:
                    if(healthP > 0 && amount <= healthP && x.getGold() >= (100 * amount )){
                        healthP = healthP - amount;
                        x.sethP(x.gethP() + amount);
                        x.setGold(x.getGold() - (100 * amount));
                        cout << "Purchase complete" << endl;
                        break;
                    }
                    else{
                        if(healthP == 0){
                            cout << "Out of stock" << endl;
                            break;
                        }
                        else if(amount > healthP){
                            cout << "Not enough inventory" << endl;
                            break;
                        }
                        else if(x.getGold() < (100 * amount)){
                            cout << "Not enough gold" << endl;
                            break;
                        }
                    }

                case 2:
                    if(manaP > 0 && amount < manaP&& x.getGold() >= (100 * amount )){
                        manaP = manaP - amount;
                        x.setmP(x.getmP() + amount);
                        x.setGold(x.getGold() - (100 * amount));
                        cout << "Purchase complete" << endl;
                        break;
                    }
                    else{
                        if(manaP == 0){
                            cout << "Out of stock" << endl;
                            break;
                        }
                        else if(amount > manaP){
                            cout << "Not enough inventory" << endl;
                            break;
                        }
                        else if(x.getGold() < (100 * amount)){
                            cout << "Not enough gold" << endl;
                            break;
                        }
                    }

                case 3:
                    if(staminaP > 0 && amount < staminaP && x.getGold() >= (100 * amount )){
                        staminaP = staminaP - amount;
                        x.setsP(x.getsP() + amount);
                        x.setGold(x.getGold() - (100 * amount));
                        cout << "Purchase complete" << endl;
                        break;
                    }
                    else{
                        if(staminaP == 0){
                            cout << "Out of stock" << endl;
                            break;
                        }
                        else if(amount > staminaP){
                            cout << "Not enough inventory" << endl;
                            break;
                        }
                        else if(x.getGold() < (100 * amount)){
                            cout << "Not enough gold" << endl;
                            break;
                        }
                    }

                case 4:
                    if(critP > 0 && amount < critP && x.getGold() >= (150 * amount )){
                        critP = critP - amount;
                        x.setcP(x.getcP() + amount);
                        x.setGold(x.getGold() - (150 * amount));
                        cout << "Purchase complete" << endl;
                        break;
                    }
                    else{
                        if(critP == 0){
                            cout << "Out of stock" << endl;
                            break;
                        }
                        else if(amount > critP){
                            cout << "Not enough inventory" << endl;
                            break;
                        }
                        else if(x.getGold() < (150 * amount)){
                            cout << "Not enough gold" << endl;
                            break;
                        }
                    }
                case 5:
                    if(stealthP > 0 && amount < stealthP && x.getGold() >= (500 * amount )){
                        stealthP = stealthP - amount;
                        x.setshP(x.getshP() + amount);
                        x.setGold(x.getGold() - (500 * amount));
                        cout << "Purchase complete" << endl;
                        break;
                    }
                    else{
                        if(stealthP == 0){
                            cout << "Out of stock" << endl;
                            break;
                        }
                        else if(amount > stealthP){
                            cout << "Not enough inventory" << endl;
                            break;
                        }
                        else if(x.getGold() < (500 * amount)){
                            cout << "Not enough gold" << endl;
                            break;
                        }
                    }
                case 6:
                    if(focusP > 0 && amount < focusP && x.getGold() >= (200 * amount )){
                        focusP = focusP - amount;
                        x.setfP(x.getfP() + amount);
                        x.setGold(x.getGold() - (200 * amount));
                        cout << "Purchase complete" << endl;
                        break;
                    }
                    else{
                        if(focusP == 0){
                            cout << "Out of stock" << endl;
                            break;
                        }
                        else if(amount > focusP){
                            cout << "Not enough inventory" << endl;
                            break;
                        }
                        else if(x.getGold() < (200 * amount)){
                            cout << "Not enough gold" << endl;
                            break;
                        }
                    }
                case 7:
                    break;
                default:
                    break;
            }
        }
    //Function that will be used to restock potion inventory
        void restock(int choice, int amount, Character& x){
            //1 = hp , 2 = mana, 3 = stamina , 4 = crit , 5 = stealth, 6 = focus
            switch(choice){
                case 1:
                    if(x.gethP() > 0){
                        healthP = healthP + amount;
                        x.sethP(x.gethP() - amount);
                        x.setGold(x.getGold() + (100 * amount));
                        cout << "Sell completed" << endl;
                        break;
                    }
                    else{
                        cout << "No potions in inventory to sell" << endl;
                        break;
                    }
                case 2:
                    if(x.getmP() > 0){
                        manaP = manaP + amount;
                        x.setmP(x.getmP() - amount);
                        x.setGold(x.getGold() + (100 * amount));
                        cout << "Sell completed" << endl;
                        break;
                    }
                    else{
                        cout << "No potions in inventory to sell" << endl;
                        break;
                    }
                case 3:
                    if(x.getsP() > 0){
                        staminaP = staminaP + amount;
                        x.setsP(x.getsP() - amount);
                        x.setGold(x.getGold() + (100 * amount));
                        cout << "Sell completed" << endl;
                        break;
                    }
                    else{
                        cout << "No potions in inventory to sell" << endl;
                        break;
                    }
                case 4:
                    if(x.getcP() > 0){
                        critP = critP + amount;
                        x.setcP(x.getcP() - amount);
                        x.setGold(x.getGold() + (150 * amount));
                        cout << "Sell completed" << endl;
                        break;
                    }
                    else{
                        cout << "No potions in inventory to sell" << endl;
                        break;
                    }
                case 5:
                    if(x.getshP() > 0){
                        stealthP = stealthP + amount;
                        x.setshP(x.getshP() - amount);
                        x.setGold(x.getGold() + (500 * amount));
                        cout << "Sell completed" << endl;
                        break;
                    }
                    else{
                        cout << "No potions in inventory to sell" << endl;
                        break;
                    }
                case 6:
                    if(x.getfP() > 0){
                        focusP = focusP + amount;
                        x.setfP(x.getfP() - amount);
                        x.setGold(x.getGold() + (200 * amount));
                        cout << "Sell completed" << endl;
                        break;
                    }
                    else{
                        cout << "No potions in inventory to sell" << endl;
                        break;
                    }
                case 7:
                    break;
                default:
                    break;
            }
        }
    //Function used to reset shop to default
        void reset(){
            healthP = 5;
            manaP = 5;
            staminaP = 5;
            critP = 5;
            stealthP = 5;
            focusP = 5;
        }
    private:
        int healthP, manaP, staminaP, critP, stealthP, focusP;
};
#endif