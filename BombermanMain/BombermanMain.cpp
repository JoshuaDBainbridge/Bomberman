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
    string position; 
    bool alive = true;
public:
    Enity(string newE, string pos) {
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
    void setPosition(string pos) {
        position = pos; 
    }
    string getPosition() {
        return position; 
    }
    char getWeapon() {
        return weapon; 
    }
    void printEnity() {
        std::cout << "Type: " << type << " Wepon: " << weapon << " pos " << position << std::endl;
    }
    ~Enity(){}
};

class GameBoard {
private: 
    int mapSize = 20; 
    unordered_map<string, unique_ptr<Enity>> characterList;
    unordered_map<string, string> map; 
public: 
    GameBoard() {

    }
    void addEnity(string name, string newE, string pos) {
        if (name[0] != 'R') {
            characterList.insert({name, make_unique<Enity>(newE, pos) });
            characterList[name]->printEnity();
        }
        map.insert({pos, name});
        //std::cout << "\n" << map[pos];
        //characterList[map[pos]]->printEnity();
    }
    void moveEnityUP(string name) {
        int x, y;
        string newPos; 
        if (characterList[name] != NULL){
            x = (std::stoi(characterList[name]->getPosition())) % 100;
            y = (std::stoi(characterList[name]->getPosition())) / 100;
            if (y > 0) {
                newPos = to_string(100 * (y - 1) + x);
                if (newPos.length() < 4) {
                    newPos = "0" + newPos;
                }
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
        int x, y;
        string newPos;
        if (characterList[name] != NULL) {
            x = (std::stoi(characterList[name]->getPosition())) % 100;
            y = (std::stoi(characterList[name]->getPosition())) / 100;
            if (y < 19) {
                newPos = to_string(100 * (y + 1) + x);
                if (newPos.length() < 4) {
                    newPos = "0" + newPos;
                }
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
        int x, y;
        string newPos;
        if (characterList[name] != NULL) {
            x = (std::stoi(characterList[name]->getPosition())) % 100;
            y = (std::stoi(characterList[name]->getPosition())) / 100;
            if (x > 0) {
                newPos = to_string(100 * y + (x - 1));

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
        int x, y;
        string newPos;
        if (characterList[name] != NULL) {
            x = (std::stoi(characterList[name]->getPosition())) % 100;
            y = (std::stoi(characterList[name]->getPosition())) / 100;
            if (x < 19) {
                newPos = to_string(100 * y + (x + 1));

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
        int x, y;
        string atkPos;
        if (characterList[name] != NULL) {
            x = (std::stoi(characterList[name]->getPosition())) % 100;
            y = (std::stoi(characterList[name]->getPosition())) / 100;
            if (characterList[name]->getWeapon() == 'A') {
                for (int j = y - 1; j <= y + 1; j++) {
                    for (int i = x - 1; i <= x + 1; i++) {
                        atkPos = to_string(100 * (j) + i);
                        if (atkPos.length() < 4) {
                            atkPos = "0" + atkPos;
                        }
                        std::cout << atkPos << std::endl;
                        
                        if (!map[atkPos].empty() && atkPos != (characterList[name]->getPosition())) {
                            if (map[atkPos][0] == 'E' || map[atkPos][0] == 'P') {
                                deleteEnity(map[atkPos]);
                            }
                        }
                    }
                }
            }
            else if (characterList[name]->getWeapon() == 'V') {

            }
            else if (characterList[name]->getWeapon() == 'H') {

            }
            else {
                std::cout << "WEAPON ERROR: UNKNOWN WEAPON" << std::endl;
            }
        }
    }


    bool isSpaceEmpty(string pos) {
        if (map[pos].empty()) {
            return true; 
        }
        else {
            return false; 
        }
    }
    void deleteEnity(string name) {
        std::cout << "\n" << name << "\n";
        map.erase(characterList[name]->getPosition());
        characterList[name]->~Enity();
        characterList.erase(name);
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
    gb->addEnity("E0","EA0", "1010");
    gb->addEnity("E1", "EV1", "0910");
    gb->addEnity("E2", "EV2", "1110");
    gb->addEnity("E3", "EV3", "1009");
    gb->addEnity("E4","EV4", "1011");
    gb->addEnity("R", "R", "0000");
    //gb->isSpaceEmpty("1919");
    //gb->deleteEnity("E0");
    gb->moveEnityUP("E0");
    gb->moveEnityDOWN("E0");
    gb->moveEnityLEFT("E0");
    gb->moveEnityRIGHT("E0");
    
    gb->attack("E0");

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
