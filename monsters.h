#ifndef MONSTERS_H
#define MONSTERS_H
#include <iostream>
#include <string>
#include <random>
#include "character.h"
using namespace std;

class Monsters{
    public:
    //Overloaded constructor
        Monsters(string name, int level, int health, int atk, int def){
            this->name = name;
            this->level = level;
            this->health = health;
            this->atk = atk;
            this->def = def;
        }

    //Setter functions
        void setHealth(int x){health = x;}
        void setLevel(int x){level = x;}
        void setName(string x){name = x;}
    //Getter functions
        int getHealth(){return health;}
        int getLevel(){return level;}
        int getAtk(){return atk;}
        string getName(){return name;}
        
    //Receiving damage function
        void takeDmg(int x) {health -= x;}

    private:
        string name;
        int level, health, atk, def;

};

#endif