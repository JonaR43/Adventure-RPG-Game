#ifndef MAGE_H
#define MAGE_H
#include "character.h"
#include <random>
using namespace std;

class Mage : public Character{
    public:
    //Overloaded constructor
        Mage(string name):Character(name){
            mana = 100;
            health = 100;
            atk = 20;
            def = 5;
            crit = 2;
            archtype = "Mage";
        }

    //Rest function will set health and stamina to max
        void rest(){
            setHealth(100);
            mana = 100;
            cout << "Sleeping.... Health and Mana restored to max" << endl;
        }

    //Will give a overview of character
        void status(){
                cout << "-----Character Status-----" << endl;
                cout << " Archtype: " << archtype << endl;
                cout << " Name: " << name << endl;
                cout << " Level: " << level << endl;
                cout << " Health: " << health << endl;
                cout << " Experience: " << exp << endl;
                cout << " Mana: " << mana << endl;
                cout << " Stage: " << stage << endl;
                cout << " Mission: " << mission << endl;
                cout << " Attack: " << atk << endl;
                cout << " Defense: " << def  << endl;
                cout << " Critical: " << crit << endl;
                cout << " Gold: " << gold << endl;
                cout << "--------------------------" << endl;
            }

        void campaign(){
                cout << "Stage: " << stage << endl;
                cout << "Mission: " << mission << endl;
            }

    //Setter functions
        void setMana(int x){mana = x;}

    //Getter functions
        int getMana(){return mana;}

    //Attack functions
        void attack( Monsters& x){
            // Seed the random number generator
            random_device rd;
            mt19937 gen(rd());

            // Define the range
            uniform_int_distribution<> distribution(1, 10);

            // Generate a random number in the range 1-10
            int randomNumber = distribution(gen);
            if(mana > 0){
                if(critOn == true) {
                    if(randomNumber > 5){
                        cout << "Critical potion active" << endl;
                        cout << name << " lands critical hit on " << x.getName() << endl;
                        setMana((mana - 10));
                        x.takeDmg(atk * crit);
                    }
                    else{
                        cout << name << " has missed their attack !! " << endl;
                        setMana((mana - 10));
                    }
                }
                else if (focusOn == true){
                    cout << "Focus potion active" << endl;
                    if(randomNumber == 7 || randomNumber == 9){
                        cout << name << " lands critical hit on " << x.getName() << endl;
                        setMana((mana - 10));
                        x.takeDmg(atk * crit);
                    }
                    else{
                        cout << name << " cast spell at " << x.getName() << endl;
                        setMana((mana - 10));
                        x.takeDmg(atk);
                    }
                }
                else if(focusOn == true && critOn == true){
                    cout << "Focus and Critical potion active" << endl;
                    cout << name << " lands critical hit on " << x.getName() << endl;
                    setMana((mana - 10));
                    x.takeDmg(atk * crit);
                }
                else if(randomNumber > 5){
                    if(randomNumber == 7 || randomNumber == 9){
                        cout << name << " lands critical hit on " << x.getName() << endl;
                        setMana((mana - 10));
                        x.takeDmg(atk * crit);
                    }
                    else{
                        cout << name << " cast spell at " << x.getName() << endl;
                        setMana((mana - 10));
                        x.takeDmg(atk);
                    }
                }
                else{
                    cout << name << " has missed their attack !! " << endl;
                    setMana((mana - 10));
                }
            }
            else{
                cout << "Not enough mana attack has failed!!!!" << endl;
            }
        }

        void takeDmg(int x) {health -= x;}
    //Save and Load functions
        void saveToFile() {
            ofstream fout;
            fout.open(this->name + ".txt");
            fout << this->archtype << endl;
            fout << this->name << endl;
            fout << this->level << endl;
            fout << this->health << endl;
            fout << this->exp << endl;
            fout << this->mana << endl;
            fout << this->stage << endl;
            fout << this->mission << endl;
            fout << this->hP << endl;
            fout << this->mP << endl;
            fout << this->sP << endl;
            fout << this->cP << endl;
            fout << this->shP << endl;
            fout << this->fP << endl;
            fout << this->atk << endl;
            fout << this->def << endl;
            fout << this->crit << endl;
            fout << this->gold << endl;
            fout << this->newChar << endl;
            fout.close();
        }
        
        void loadFromFile(string filename) {
            ifstream fin;
            fin.open(filename + ".txt");
            getline(fin, this->archtype);
            getline(fin, this->name);
            fin >> this->level;
            fin >> this->health;
            fin >> this->exp;
            fin >> this->mana;
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
            fin >> this->newChar;
            fin.close();
        }

    private:
        int mana;
};

#endif