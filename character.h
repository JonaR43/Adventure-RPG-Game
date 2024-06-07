#ifndef CHARACTER_H
#define CHARACTER_H
#include <iostream>
#include <fstream>
#include "monsters.h"
using namespace std;

class Character{
    public:
    //Default constructor
        Character(){
            name = "Empty";
            archtype = "none";
            level = 1;
            health = 100;
            exp = 0;
            atk = 0;
            def = 0;
            stage = 1;
            mission = 1;
            hP = 0;
            mP = 0;
            sP = 0;
            cP = 0;
            shP = 0;
            fP = 0;
            gold = 100;
            newChar = true;
        }

    //Overloaded constructor will take in a string to set as the name
       Character(string name){
            this->name = name;
            archtype = "none";
            level = 1;
            health = 100.0;
            exp = 0;
            atk = 0;
            def = 0;
            stage = 1;
            mission = 1;
            hP = 0;
            mP = 0;
            sP = 0;
            cP = 0;
            shP = 0;
            fP = 0;
            gold = 1000;
            newChar = true;
            focusOn = false;
            stealthOn = false;
            critOn == false;
        }

    //Print out the character information, virtual and will be overwritten by derived class
        virtual void status(){
            cout << "Name: " << name << endl;
            cout << "Level: " << level << endl;
            cout << "Health: " << health << endl;
            cout << "Experience: " << exp << endl;
            cout << "Stage: " << stage << endl;
            cout << "Mission: " << mission << endl;
        }

        void inventory(){
            cout << "--------------------------" << endl;
            cout << "Health Potions: " << hP << endl;
            cout << "Mana Potions: " << mP << endl;
            cout << "Stamina Potions: " << sP << endl;
            cout << "Critical Potions: " << cP << endl;
            cout << "Stealth Potions: " << shP << endl;
            cout << "Focus Potions: " << fP << endl;
            cout << "--------------------------" << endl;
        }

    //Prints out the current stage and mission in the campaign
        virtual void campaign(){
            cout << "Stage: " << stage << endl;
            cout << "Mission: " << mission << endl;
        }

    //Use fuction #1 that will restore health, for derived class their special attribute will be restored
        virtual void rest(){
            health = 100;
            cout << "Sleeping.... Health restored to max" << endl;
        }

    //Save and Load functions
        virtual void saveToFile() {
            ofstream fout;
            fout.open(this->name + ".txt");
            fout << this->name << endl;
            fout << this->level << endl;
            fout << this->health << endl;
            fout << this->exp << endl;
            fout << this->stage << endl;
            fout << this->mission << endl;
            fout << this->hP;
            fout << this->mP;
            fout << this->sP;
            fout << this->cP;
            fout << this->shP;
            fout << this->fP;
            fout << this->fP << endl;
            fout << this->atk << endl;
            fout << this->def << endl;
            fout << this->crit << endl;
            fout << this->gold << endl;
            fout << this->newChar << endl;
            fout.close();
        }

        virtual void loadFromFile(string filename) {
            ifstream fin;
            fin.open(filename + ".txt");
            getline(fin, this->archtype);
            getline(fin, this->name);
            fin >> this->level;
            fin >> this->health;
            fin >> this->exp;
            fin >> this->stage;
            fin >> this->mission;
            fin >> this->hP;
            fin >> this->mP;
            fin >> this->sP;
            fin >> this->cP;
            fin >> this->shP;
            fin >> this->fP;
            fin >> this->atk;
            fin >> this->def;
            fin >> this->crit;
            fin >> this->gold;
            fin >> this->fP;
            fin >> this->atk;
            fin >> this->def;
            fin >> this->crit;
            fin >> this->gold;
            fin >> this->newChar;
            fin.close();
            cout << "Character has been loaded succesfully." << endl;
        }

    //Function to use consumables
        void useItem(){
            //1 = hp, 2 = mana, 3 = stamina, 4 = crit, 5 = stealth 6 = 
            int choice;
            cout << "Which potion would you like to use?" << endl;
            cin >> choice;
            switch (choice){
                case 1:
                    setHealth(100);
                    break;
                
                default:
                    break;
            }
        }

    //Attacking function passing in opponent by reference
        virtual void attack(Monsters& x){
            cout << name << " attacking " << x.getName() << endl;
            int dmg = atk;
        }

    // Taking damage function
        virtual void takeDmg(int x) {health -= x;}

    //Setter functions
        void setHealth(int x) {health = x;}
        void setLevel(int x) {level = x;}
        void setExp(int x) {exp = x;}
        void setStage(int x) {stage = x;}
        void setMission(int x) {mission = x;}
        void setAtk(int x) {atk = x;}
        void setDef(int x) {def = x;}
        void setCrit(int x) {crit = x;}
        void sethP(int x) {hP = x;}
        void setmP(int x) {mP = x;}
        void setsP(int x) {sP = x;}
        void setcP(int x) {cP = x;}
        void setshP(int x) {shP = x;}
        void setfP(int x) {fP = x;}
        void setNewChar(bool x) {newChar = x;}
        void setGold(int x) {gold = x;}
        void setStealth(bool x) {stealthOn = x;}
        void setFocusOn(bool x) {focusOn = x;}
        void setCritOn(bool x){critOn = x;}
        virtual void setMana(int x){}
        virtual void setStamina(int x){}

    //Getter functions
        int getHealth() {return health;}
        int getLevel() {return level;}
        int getExp() {return exp;}
        int getStage() {return stage;}
        int getMission() {return mission;}
        int getAtk() {return atk;}
        int getDef() {return def;}
        int getCrit() {return crit;}
        int gethP() {return hP;}
        int getmP() {return mP;}
        int getsP() {return sP;}
        int getcP() {return cP;}
        int getshP() {return shP;}
        int getfP() {return fP;}
        int getGold() {return gold;}
        virtual int getStamina() {return stamina;}
        virtual int getMana(){return mana;}
        string getName() {return name;}
        string getArchtype() {return archtype;}
        bool getNewChar() {return newChar;}
        bool getStealth() {return stealthOn;}
        bool getFocus() {return focusOn;}


    protected:
        string name , archtype;
        int level, stage, mission, gold;
        int health, exp, atk, def, crit, mana, stamina;
        int hP, mP, sP, cP, shP, fP;
        bool newChar, focusOn, stealthOn, critOn;
};
#endif