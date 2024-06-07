#ifndef KNIGHT_H
#define KNIGHT_H
#include "character.h"
#include <random>
using namespace std;

class Knight : public Character{
    public:
    //Overloaded constructor
        Knight(string name):Character(name){
            stamina = 100;
            health = 200;
            atk = 10;
            def = 10;
            crit = 2;
            archtype = "Knight";
        }

    //Rest function will set health and stamina to max
        void rest(){
            setHealth(200);
            stamina = 100;
            cout << "Sleeping.... Health and Stamina restored to max" << endl;
        }

    //Will give a overview of character
        void status(){
                cout << "-----Character Status-----" << endl;
                cout << " Archtype: " << archtype << endl;
                cout << " Name: " << name << endl;
                cout << " Level: " << level << endl;
                cout << " Health: " << health << endl;
                cout << " Experience: " << exp << endl;
                cout << " Stamina: " << stamina << endl;
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
        void setStamina(int x){stamina = x;}

    //Getter functions
        int getStamina(){return stamina;}

    //Attack functions
        void attack( Monsters& x){
            // Seed the random number generator
            random_device rd;
            mt19937 gen(rd());

            // Define the range
            uniform_int_distribution<> distribution(1, 10);

            // Generate a random number in the range 1-10
            int randomNumber = distribution(gen);
            if(stamina > 0){
                if(focusOn == true && critOn == true){
                    cout << "Focus and Critical potion active" << endl;
                    cout << name << " lands critical hit on " << x.getName() << endl;
                    setStamina((stamina - 10));
                    x.takeDmg(atk * crit);
                }
                else if(critOn == true) {
                    if(randomNumber > 5){
                        cout << "Critical potion active" << endl;
                        cout << name << " lands critical hit on " << x.getName() << endl;
                        setStamina((stamina - 10));
                        x.takeDmg(atk * crit);
                    }
                    else{
                        cout << name << " has missed their attack !! " << endl;
                        setStamina((stamina - 10));
                    }
                }
                else if (focusOn == true){
                    cout << "Focus potion active" << endl;
                    if(randomNumber == 7 || randomNumber == 9){
                        cout << name << " lands critical hit on " << x.getName() << endl;
                        setStamina((stamina - 10));
                        x.takeDmg(atk * crit);
                    }
                    else{
                        cout << name << " swings sword at " << x.getName() << endl;
                        setStamina((stamina - 10));
                        x.takeDmg(atk);
                    }
                }
                else if(randomNumber > 5){
                    if(randomNumber == 7 || randomNumber == 9){
                        cout << name << " lands critical hit on " << x.getName() << endl;
                        setStamina((stamina - 10));
                        x.takeDmg(atk * crit);
                    }
                    else{
                        cout << name << " swings sword at " << x.getName() << endl;
                        setStamina((stamina - 10));
                        x.takeDmg(atk);
                    }
                }
                else{
                    cout << name << " has missed their attack !! " << endl;
                    setStamina((stamina - 10));
                }
            }
            else{
                cout << "Not enough stamina attack has failed!!!!" << endl;
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
            fout << this->stamina << endl;
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
            fin >> this->stamina;
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
        int stamina;
};

#endif