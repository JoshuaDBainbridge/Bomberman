// BombermanMain.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>
using namespace std;

class Enity {
private:
    string id;
    char weapon;
    char type; 
    int position; 
    bool alive = true;
public:
    Enity(string newE, int pos) {
        std::cout << newE << std::endl;
        if (newE.length() == 1) {
            type = 'R';
            position = pos;
            weapon = newE[1];
            id = "R";
        }
        else {
            position = pos;
            weapon = newE[1];
            id = newE;
            if (newE[0] == 'P') {
                type = 'P';
            }
            else {
                type = 'E';
            }
        }
    }
    void setPosition(int pos) {
        position = pos; 
    }
    int getPosition() {
        return position; 
    }
    char getWeapon() {
        return weapon; 
    }
    string getID() {
        return id; 
    }
    void printEnity() {
        std::cout << "Type: " << type << " Wepon: " << weapon << " y-> " << position / 100 << " pos: x-> " << position%100  <<  std::endl;
    }
    ~Enity(){}
};

class GameBoard {
private: 
    int mapSize = 5; 
    bool playerWin = false; 
    unordered_map<string, unique_ptr<Enity>> characterList;
    unordered_map<int, string> map; 
public: 
    GameBoard() {
        // map[(int) position] = (str) name 
        // characterList [(str)name] = Pointer to Enity Object
    }
    void addEnity(string name, string newE, int pos) {
        if (name[0] != 'R') {
            characterList.insert({name, make_unique<Enity>(newE, pos) });
            characterList[name]->printEnity();
        }
        map.insert({ pos, name });
        //std::cout << "\n" << map[pos];
        //characterList[map[pos]]->printEnity();
    }
    void moveEnityUP(string name) {
        int x, y, newPos; 
        if (characterList[name] != NULL){
            x = (characterList[name]->getPosition()) % 100;
            y = (characterList[name]->getPosition()) / 100;
            if (y > 0) {
                newPos = (100 * (y - 1) + x);

                if (isSpaceEmpty(newPos)) {
                    map.erase(characterList[name]->getPosition());
                    map[newPos] = name;
                    characterList[name]->setPosition(newPos);
                    characterList[name]->printEnity();
                }
            }
        }
    }
    void moveEnityDOWN(string name) {
        int x, y, newPos;
        if (characterList[name] != NULL) {
            x = (characterList[name]->getPosition()) % 100;
            y = (characterList[name]->getPosition()) / 100;
            if (y < 19) {
                newPos = (100 * (y + 1) + x);

                if (isSpaceEmpty(newPos)) {
                    map.erase(characterList[name]->getPosition());
                    map[newPos] = name;
                    characterList[name]->setPosition(newPos);
                    characterList[name]->printEnity();
                }
            }
        }
    }
    void moveEnityLEFT(string name) {
        int x, y, newPos;
        if (characterList[name] != NULL) {
            x = (characterList[name]->getPosition()) % 100;
            y = (characterList[name]->getPosition()) / 100;
            if (x > 0) {
                newPos = (100 * y + (x - 1));

                if (isSpaceEmpty(newPos)) {
                    map.erase(characterList[name]->getPosition());
                    map[newPos] = name;
                    characterList[name]->setPosition(newPos);
                    characterList[name]->printEnity();
                }
            }
        }
    }
    void moveEnityRIGHT(string name) {
        int x, y, newPos;
        if (characterList[name] != NULL) {
            x = (characterList[name]->getPosition()) % 100;
            y = (characterList[name]->getPosition()) / 100;
            if (x < 19) {
                newPos = (100 * y + (x + 1));

                if (isSpaceEmpty(newPos)) {
                    map.erase(characterList[name]->getPosition());
                    map[newPos] = name;
                    characterList[name]->setPosition(newPos);
                    characterList[name]->printEnity();
                }
            }
        }
    }
    
    void attack(string name) {
        //std::cout << "Attacking!" << std::endl;
        int x, y, atkPos;
        if (characterList[name] != NULL) {
            x = (characterList[name]->getPosition()) % 100;
            y = (characterList[name]->getPosition()) / 100;
            if (characterList[name]->getWeapon() == 'A') {
                for (int j = y - 1; j <= y + 1; j++) {
                    for (int i = x - 1; i <= x + 1; i++) {
                        atkPos = (100 * (j) + i);

                        //std::cout << atkPos << std::endl;
                        if (!map[atkPos].empty() && atkPos != (characterList[name]->getPosition())) {
                            if (map[atkPos][0] == 'E' || map[atkPos][0] == 'P') {
                                deleteEnity(map[atkPos]);
                            }
                        }
                    }
                }
            }
            else if (characterList[name]->getWeapon() == 'V') {
                for (int j = 0; j < mapSize; j++) {
                    atkPos = (100 * (j)+x);
                    if (!map[atkPos].empty() && atkPos != (characterList[name]->getPosition())) {
                        if (map[atkPos][0] == 'E' || map[atkPos][0] == 'P') {
                            deleteEnity(map[atkPos]);
                        }
                    }
                }
            }
            else if (characterList[name]->getWeapon() == 'H') {
                for (int i = 0; i < mapSize; i++) {
                    atkPos = (100 * (y)+i);
                    if (!map[atkPos].empty() && atkPos != (characterList[name]->getPosition())) {
                        if (map[atkPos][0] == 'E' || map[atkPos][0] == 'P') {
                            deleteEnity(map[atkPos]);
                        }
                    }
                }
            }
            else {
                std::cout << "WEAPON ERROR: UNKNOWN WEAPON" << std::endl;
            }
        }
    }
    bool gameOver() {
    }
    bool isSpaceEmpty(int pos) {
        if (map[pos].empty()) {
            return true; 
        }
        else {
            return false; 
        }
    }
    void deleteEnity(string name) {
        //std::cout << "\n" << "DELETING: " << name << "\n";

        map.erase(characterList[name]->getPosition());
        if (map[characterList[name]->getPosition()].empty()) {
            //std::cout << "DID " << map[characterList[name]->getPosition()] << std::endl;
        }
        characterList[name]->~Enity();
        characterList.erase(name);

        if (characterList[name] <= 0) {
            //std::cout << "DID it" << characterList[name] << std::endl;
        }
    }

    void paint() {
        for (int y = 0; y < mapSize; y++) {
            for (int x = 0; x < mapSize; x++) {
                std::cout << " ";
                if (isSpaceEmpty((100*y)+x)) {
                    std::cout << " 0 ";
                }
                else if (map[(100 * y) + x][0]  == 'R') {
                    std::cout << " R ";
                }
                else if (map[(100 * y) + x][0] == 'E') {
                    std::cout << characterList[map[100 * y + x]]->getID();
                }
                else {
                    std::cout << characterList[map[100 * y + x]]->getID() << " ";
                }
            }
            std::cout<<std::endl; 
        }
    }
};

int main()
{
    //GameBoard gb;
    //Enity test("PA", "0000");
    //test.showDetails();

    //unordered_map<string, unique_ptr<Enity>> testMap;
    //unique_ptr<Enity> test2(new Enity("EA0", "0001"));
    //testMap.insert({"A0E", make_unique<Enity>("EA0", "0001")});
    //unique_ptr<Enity> test2 (new Enity("EA0", "0001"));
    //test2->showDetails();
    //testMap["A0E"] -> showDetails();
        
    unique_ptr<GameBoard> gb(new GameBoard());
    gb->addEnity("E0","EA0", 101);
    gb->addEnity("E1", "EH1", 3);
    gb->addEnity("E2", "EV2", 2);
    gb->addEnity("E3", "EV3", 1);
    gb->addEnity("E4","EV4", 103);
    gb->addEnity("R", "R", 202);

    //std::cout << gb->isSpaceEmpty(1919) << std::endl;
    //gb->deleteEnity("E0");
    //gb->moveEnityUP("E0");
    //gb->moveEnityDOWN("E0");
    //gb->moveEnityLEFT("E0");
    //gb->moveEnityRIGHT("E0");
    
    //gb->attack("E0");
    /*
    gb->paint();

    std::cout << " MOVE RIGHT " << std::endl;
    gb-> moveEnityLEFT("E0");
    gb->paint(); 

    std::cout << " Attack " << std::endl;
    gb->attack("E0");
    gb->paint();

    std::cout << " TRY MOVE DOWN " << std::endl;
    gb->moveEnityDOWN("E0");
    gb->paint();

    std::cout << " MOVE RIGHT " << std::endl;
    gb->moveEnityLEFT("E0");
    gb->paint();

    gb->moveEnityUP("E0");
    gb->paint();
    
    gb->moveEnityUP("E0");
    gb->paint();

    gb->moveEnityUP("E0");
    gb->paint();

    gb->attack("E1");
    gb->paint();
    */

    std::cout << std::endl << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
