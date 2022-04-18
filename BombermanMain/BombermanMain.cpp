// BombermanMain.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>

#include <fstream>
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
        std::cout <<"ID" << id << "Type: " << type << " Wepon: " << weapon << " y-> " << position / 100 << " pos: x-> " << position%100  <<  std::endl;
    }
    ~Enity(){}
};
class GameBoard {
private: 
    int mapSize = 20, enemyPop = 0;
    bool playerWin = false, playerAdded = false, playerDead = false; 
    unordered_map<string, unique_ptr<Enity>> characterList;
    unordered_map<int, string> map; 
public: 
    GameBoard() {
        // map[(int) position] = (str) name 
        // characterList [(str)name] = Pointer to Enity Object
    }
    void addEnity(string name, string newE, int pos) {
        if (name[0] == 'R') {
            map.insert({ pos, name });
        }else if(name[0] == 'E'){
            characterList.insert({ name, make_unique<Enity>(newE, pos) });
            //characterList[name]->printEnity();
            enemyPop++;
            map.insert({ pos, name });
        }
        else if (name[0] == 'P' && !playerAdded) {
            characterList.insert({ name, make_unique<Enity>(newE, pos) });
            //characterList[name]->printEnity();
            playerAdded= true;
            map.insert({ pos, name });
        }
        else {
            std::cout << "ERROR: ENITY MISMATCH! Unknown enity: " << newE << std::endl;
        }

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
                    //characterList[name]->printEnity();
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
                    //characterList[name]->printEnity();
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
                    //characterList[name]->printEnity();
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
                    //characterList[name]->printEnity();
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
                            if (map[atkPos][0] == 'E') {
                                deleteEnity(map[atkPos]);
                                enemyPop--; 
                            }
                            else if(map[atkPos][0] == 'P'){
                                playerDead = true; 
                            }
                        }
                    }
                }
            }
            else if (characterList[name]->getWeapon() == 'V') {
                int y = characterList[name]->getPosition() / 100; 
                for (int j = y; j < mapSize; j++) {
                    atkPos = (100 * (j)+x);
                    if (!map[atkPos].empty() && atkPos != (characterList[name]->getPosition())) {
                        if (map[atkPos][0] == 'E') {
                            deleteEnity(map[atkPos]);
                            enemyPop--;
                        }
                        else if (map[atkPos][0] == 'P') {
                            playerDead = true;
                        }
                        else if (map[atkPos][0] == 'R') {
                            break;
                        }
                    }
                }
                for (int j = y; j >= 0; j--) {
                    atkPos = (100 * (j)+x);
                    if (!map[atkPos].empty() && atkPos != (characterList[name]->getPosition())) {
                        if (map[atkPos][0] == 'E') {
                            deleteEnity(map[atkPos]);
                            enemyPop--;
                        }
                        else if (map[atkPos][0] == 'P') {
                            playerDead = true;
                        }
                        else if (map[atkPos][0] == 'R') {
                            break;
                        }
                    }
                }
            }
            else if (characterList[name]->getWeapon() == 'H') {
                int x = characterList[name]->getPosition() % 100;
                for (int i = x; i < mapSize; i++) {
                    atkPos = (100 * (y)+i);
                    if (!map[atkPos].empty() && atkPos != (characterList[name]->getPosition())) {
                        if (map[atkPos][0] == 'E') {
                            deleteEnity(map[atkPos]);
                            enemyPop--;
                        }
                        else if (map[atkPos][0] == 'P') {
                            playerDead = true;
                        }
                        else if (map[atkPos][0] == 'R') {
                            break;
                        }
                    }
                }
                for (int i = x; i >= 0; i--) {
                    atkPos = (100 * (y)+i);
                    if (!map[atkPos].empty() && atkPos != (characterList[name]->getPosition())) {
                        if (map[atkPos][0] == 'E') {
                            deleteEnity(map[atkPos]);
                            enemyPop--;
                        }
                        else if (map[atkPos][0] == 'P') {
                            playerDead = true;
                        }
                        else if (map[atkPos][0] == 'R') {
                            break;
                        }
                    }
                }

            }
            else {
                std::cout << "WEAPON ERROR: UNKNOWN WEAPON" << std::endl;
            }
        }
    }
    void gameResults() {
        if (enemyPop <= 0 && playerDead) {
            std::cout << "THE GAME ENDED IN A STALEMATE" << std::endl;
        }
        else if (enemyPop <= 0) {
            std::cout << "THE GAME ENDED: PLAYER WON" << std::endl;
        }
        else if (playerDead) {
            std::cout << "THE GAME ENDED: PLAYER LOST" << std::endl;
        }
        else {
            std::cout << "THE GAME ENDED IN A STALEMATE" << std::endl;
        }
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
                    std::cout << " O ";
                }
                else if (map[(100 * y) + x][0]  == 'R') {
                    std::cout << " R ";
                }
                else if (map[(100 * y) + x][0] == 'E') {
                    std::cout << characterList[map[100 * y + x]]->getID();
                }
                else {
                    if (!playerDead) {
                        std::cout << characterList[map[100 * y + x]]->getID() << " ";
                    }
                    else {
                        std::cout << " X ";
                    }
                }
            }
            std::cout<<std::endl; 
        }
    }
    ~GameBoard() {}
};

int main()
{
    std::cout << "()...WELCOME TO BOMBERMAN...() " << std::endl; 
    std::cout << "-playing with default 20 by 20 board " << endl;
    //std::cout << "~IMPORT GAME BOARD~";

    // Create a text string, which is used to output the text file
    int y = 0, x=0;
    int entities = 0; 
    string myText;
    unique_ptr<GameBoard> gb(new GameBoard());

    // Read from the text file
    ifstream MyReadFile("input.txt");

    // Use a while loop together with the getline() function to read the file line by line
    while (getline(MyReadFile, myText)) {
        if (y < 20) {
            remove(myText.begin(), myText.end(), ' ');
            while (entities < 20) {
                if (myText[x] != 'O') {
                    if (myText[x] == 'R') {
                        gb->addEnity("R", "R", (100*y+ entities));
                        entities++;
                        x++;
                    }
                    else if (myText[x] == 'E'){
                        gb->addEnity(myText.substr(x, 1) + myText.substr(x+2, 1), myText.substr(x, 3), (100 * y + entities));
                        entities++;
                        x+=3;
                    }
                    else if (myText[x] == 'P') {
                        gb->addEnity(myText.substr(x, 1), myText.substr(x, 2), (100 * y + entities));
                        entities++;
                        x += 2;
                    }
                    else {
                        entities++;
                        x++;
                    }
                }
                else {
                    entities++;
                    x++;
                }
            }
            y++;
            entities = 0;
            x = 0;
        }
        else {
            if (myText[myText.length() - 1] == 'U') {
                gb->moveEnityUP(myText.substr(0, myText.length() - 1));
            }
            else if (myText[myText.length() - 1] == 'D') {
                gb->moveEnityDOWN(myText.substr(0, myText.length() - 1));
            }
            else if (myText[myText.length() - 1] == 'L') {
                gb->moveEnityLEFT(myText.substr(0, myText.length() - 1));
            }
            else if (myText[myText.length() - 1] == 'R') {
                gb->moveEnityRIGHT(myText.substr(0, myText.length() - 1));
            }
            else if (myText[myText.length() - 1] == 'F') {
                gb->attack(myText.substr(0, myText.length() - 1));
            }
            else {
                std::cout << "MISMATCH ERROR: COMMAND " << myText[myText.length() - 1] << "is not valid" << std::endl; 
            }
        }

    }
    
    // Close the file
    MyReadFile.close();
    std::cout << endl;
    gb->gameResults();
    std::cout <<"FINAL BOARD: "<< std::endl;
    gb->paint();

    //GameBoard gb;
    //Enity test("PA", "0000");
    //test.showDetails();

    //unordered_map<string, unique_ptr<Enity>> testMap;
    //unique_ptr<Enity> test2(new Enity("EA0", "0001"));
    //testMap.insert({"A0E", make_unique<Enity>("EA0", "0001")});
    //unique_ptr<Enity> test2 (new Enity("EA0", "0001"));
    //test2->showDetails();
    //testMap["A0E"] -> showDetails();
    
    /*
    unique_ptr<GameBoard> gb(new GameBoard());
    gb->addEnity("E0", "EA0", 101);
    gb->addEnity("P", "PA", 201);
    gb->addEnity("R", "R", 202);
    gb->addEnity("QW", "QAW", 0);
    gb->paint();
    */
    /*
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
    
    gb->paint();

    std::cout << " MOVE LEFT " << std::endl;
    gb-> moveEnityLEFT("E0");
    gb->paint(); 

    std::cout << " Attack " << std::endl;
    gb->attack("E0");
    gb->paint();

    std::cout << " TRY MOVE DOWN " << std::endl;
    gb->moveEnityDOWN("E0");
    gb->paint();

    std::cout << " MOVE LEFT " << std::endl;
    gb->moveEnityLEFT("E0");
    gb->paint();

    std::cout << " MOVE UP " << std::endl;
    gb->moveEnityUP("E0");
    gb->paint();

    std::cout << " MOVE UP " << std::endl;
    gb->moveEnityUP("E0");
    gb->paint();
    std::cout << " MOVE UP - ILLEGAL " << std::endl;
    gb->moveEnityUP("E0");
    gb->paint();

    std::cout << " ATTACK " << std::endl;
    gb->attack("E1");
    gb->paint();

    std::cout << " TRY MOVING DEAD PLAYER " << std::endl;
    gb->moveEnityRIGHT("E0");
    gb->paint();
    */
    /*
    unique_ptr<GameBoard> gb(new GameBoard());
    gb->addEnity("E0", "EH0", 301);
    gb->addEnity("E1", "EH1", 300);
    gb->addEnity("P", "PH", 303);
    gb->addEnity("R", "R", 302);
    gb->paint();
    gb->attack("E0");
    gb->paint();
    gb->gameResults();
    */

    //std::cout << std::endl << "Hello World!\n";

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
