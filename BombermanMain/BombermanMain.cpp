// BombermanMain.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>

#include <fstream>
using namespace std;

class Entity { //The Entity Class creates Enitity object. These can be rocks, player or enemies
private:
    string id; //full name of the enitity ie EH0 or PA 
    char weapon; //A,H or V
    char type;  // R, E, P 
    int position; // (x,y) = (position%100, posiiton/100)
    bool alive = true;
public:
    Entity(string newE, int pos) {
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
    void printEntity() {
        std::cout <<"ID" << id << "Type: " << type << " Wepon: " << weapon << " y-> " << position / 100 << " pos: x-> " << position%100  <<  std::endl;
    }
    void playerKilled() {
        alive = false;
    }
    bool isPlayerAlive() {
        return alive; 
    }
    ~Entity(){}
};
class GameBoard { //The GameBoard Class constructs the gameboard object 
private: 
    int mapSize = 20, enemyPop = 0; 
    bool playerWin = false, playerAdded = false, playerDead = false; 
    unordered_map<string, unique_ptr<Entity>> characterList; //maps entity name to the entity 
    unordered_map<int, string> map; //maps  position to the entity name 
public: 
    GameBoard() {}
    void addEntity(string name, string newE, int pos) {
        if (name[0] == 'R') {
            map.insert({ pos, name });
        }else if(name[0] == 'E'){
            characterList.insert({ name, make_unique<Entity>(newE, pos) });
            //characterList[name]->printEntity();
            enemyPop++;
            map.insert({ pos, name });
        }
        else if (name[0] == 'P' && !playerAdded) {
            characterList.insert({ name, make_unique<Entity>(newE, pos) });
            //characterList[name]->printEntity();
            playerAdded= true;
            map.insert({ pos, name });
        }
        else {
            std::cout << "ERROR: Entity MISMATCH! Unknown Entity: " << newE << std::endl;
        }

        //std::cout << "\n" << map[pos];
        //characterList[map[pos]]->printEntity();
    }
    
    void moveEntityUP(string name) {
        int x, y, newPos; 
        if (characterList[name] != NULL){
            x = (characterList[name]->getPosition()) % 100;
            y = (characterList[name]->getPosition()) / 100;
            if (y > 0) {
                newPos = (100 * (y - 1) + x);
                if (isSpaceEmpty(newPos) && characterList[name]->isPlayerAlive()) {
                    map.erase(characterList[name]->getPosition());
                    map[newPos] = name;
                    characterList[name]->setPosition(newPos);
                    //characterList[name]->printEntity();
                }
            }
        }
    }
    void moveEntityDOWN(string name) {
        int x, y, newPos;
        if (characterList[name] != NULL) {
            x = (characterList[name]->getPosition()) % 100;
            y = (characterList[name]->getPosition()) / 100;
            if (y < 19) {
                newPos = (100 * (y + 1) + x);

                if (isSpaceEmpty(newPos) && characterList[name]->isPlayerAlive()) {
                    map.erase(characterList[name]->getPosition());
                    map[newPos] = name;
                    characterList[name]->setPosition(newPos);
                    //characterList[name]->printEntity();
                }
            }
        }
    }
    void moveEntityLEFT(string name) {
        int x, y, newPos;
        if (characterList[name] != NULL) {
            x = (characterList[name]->getPosition()) % 100;
            y = (characterList[name]->getPosition()) / 100;
            if (x > 0) {
                newPos = (100 * y + (x - 1));

                if (isSpaceEmpty(newPos) && characterList[name]->isPlayerAlive()) {
                    map.erase(characterList[name]->getPosition());
                    map[newPos] = name;
                    characterList[name]->setPosition(newPos);
                    //characterList[name]->printEntity();
                }
            }
        }
    }
    void moveEntityRIGHT(string name) {
        int x, y, newPos;
        if (characterList[name] != NULL) {
            x = (characterList[name]->getPosition()) % 100;
            y = (characterList[name]->getPosition()) / 100;
            if (x < 19) {
                newPos = (100 * y + (x + 1));

                if (isSpaceEmpty(newPos) && characterList[name]->isPlayerAlive()) {
                    map.erase(characterList[name]->getPosition());
                    map[newPos] = name;
                    characterList[name]->setPosition(newPos);
                    //characterList[name]->printEntity();
                }
            }
        }
    }
    
    void attack(string name) {
        int x, y, atkPos;
        if (characterList[name] != NULL) {
            x = (characterList[name]->getPosition()) % 100;
            y = (characterList[name]->getPosition()) / 100;
            if (characterList[name]->getWeapon() == 'A') {
                for (int j = y - 1; j <= y + 1; j++) {
                    for (int i = x - 1; i <= x + 1; i++) {
                        atkPos = (100 * (j) + i);
                        if (!map[atkPos].empty() && atkPos != (characterList[name]->getPosition())) {
                            if (map[atkPos][0] == 'E') {
                                deleteEntity(map[atkPos]);
                                enemyPop--; 
                            }
                            else if(map[atkPos][0] == 'P'){
                                playerDead = true;
                                characterList[map[atkPos]]->playerKilled();
                            }
                        }
                    }
                }
            }
            else if (characterList[name]->getWeapon() == 'V') {
                int y = characterList[name]->getPosition() / 100; 
                for (int j = y; j < mapSize; j++) { //starting at the attacking entity going down 
                    atkPos = (100 * (j)+x);
                    if (!map[atkPos].empty() && atkPos != (characterList[name]->getPosition())) {
                        if (map[atkPos][0] == 'E') {
                            deleteEntity(map[atkPos]);
                            enemyPop--;
                        }
                        else if (map[atkPos][0] == 'P') {
                            playerDead = true;
                            characterList[map[atkPos]]->playerKilled();
                        }
                        else if (map[atkPos][0] == 'R') {
                            break; //stop if there is a rock 
                        }
                    }
                }
                for (int j = y; j >= 0; j--) { //starting at the attacking entity going up 
                    atkPos = (100 * (j)+x);
                    if (!map[atkPos].empty() && atkPos != (characterList[name]->getPosition())) {
                        if (map[atkPos][0] == 'E') {
                            deleteEntity(map[atkPos]);
                            enemyPop--;
                        }
                        else if (map[atkPos][0] == 'P') {
                            playerDead = true;
                            characterList[map[atkPos]]->playerKilled();
                        }
                        else if (map[atkPos][0] == 'R') {
                            break;
                        }
                    }
                }
            }
            else if (characterList[name]->getWeapon() == 'H') {
                int x = characterList[name]->getPosition() % 100;
                for (int i = x; i < mapSize; i++) {  //starting at the attacking entity going right 
                    atkPos = (100 * (y)+i);
                    if (!map[atkPos].empty() && atkPos != (characterList[name]->getPosition())) {
                        if (map[atkPos][0] == 'E') {
                            deleteEntity(map[atkPos]);
                            enemyPop--;
                        }
                        else if (map[atkPos][0] == 'P') {
                            playerDead = true;
                            characterList[map[atkPos]]->playerKilled();
                        }
                        else if (map[atkPos][0] == 'R') {
                            break;
                        }
                    }
                }
                for (int i = x; i >= 0; i--) {  //starting at the attacking entity going left 
                    atkPos = (100 * (y)+i);
                    if (!map[atkPos].empty() && atkPos != (characterList[name]->getPosition())) {
                        if (map[atkPos][0] == 'E') {
                            deleteEntity(map[atkPos]);
                            enemyPop--;
                        }
                        else if (map[atkPos][0] == 'P') {
                            playerDead = true;
                            characterList[map[atkPos]]->playerKilled();
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
    void deleteEntity(string name) {
        //std::cout << "\n" << "DELETING: " << name << "\n";

        map.erase(characterList[name]->getPosition());
        if (map[characterList[name]->getPosition()].empty()) {
            //std::cout << "DID " << map[characterList[name]->getPosition()] << std::endl;
        }
        characterList[name]->~Entity();
        characterList.erase(name);

        if (characterList[name] <= 0) {
            //std::cout << "DID it" << characterList[name] << std::endl;
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

    int y = 0, x=0;
    int entities = 0; 
    string textInput;

    unique_ptr<GameBoard> gb(new GameBoard());
    ifstream MyReadFile("input.txt");

    while (getline(MyReadFile, textInput)) {
        if (y < 20) { //READ in GAMEBOARD
            remove(textInput.begin(), textInput.end(), ' ');
            while (entities < 20) {
                if (textInput[x] != 'O') {
                    if (textInput[x] == 'R') {
                        gb->addEntity("R", "R", (100*y+ entities));
                        entities++;
                        x++;
                    }
                    else if (textInput[x] == 'E'){
                        gb->addEntity(textInput.substr(x, 1) + textInput.substr(x+2, 1), textInput.substr(x, 3), (100 * y + entities));
                        entities++;
                        x+=3;
                    }
                    else if (textInput[x] == 'P') {
                        gb->addEntity(textInput.substr(x, 1), textInput.substr(x, 2), (100 * y + entities));
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
        else { //READING IN COMMANDS
            if (textInput[textInput.length() - 1] == 'U') {
                gb->moveEntityUP(textInput.substr(0, textInput.length() - 1));
            }
            else if (textInput[textInput.length() - 1] == 'D') {
                gb->moveEntityDOWN(textInput.substr(0, textInput.length() - 1));
            }
            else if (textInput[textInput.length() - 1] == 'L') {
                gb->moveEntityLEFT(textInput.substr(0, textInput.length() - 1));
            }
            else if (textInput[textInput.length() - 1] == 'R') {
                gb->moveEntityRIGHT(textInput.substr(0, textInput.length() - 1));
            }
            else if (textInput[textInput.length() - 1] == 'F') {
                gb->attack(textInput.substr(0, textInput.length() - 1));
            }
            else {
                std::cout << "MISMATCH ERROR: COMMAND " << textInput[textInput.length() - 1] << "is not valid" << std::endl; 
            }
        }

    }
    
    // Close the file
    MyReadFile.close();
    std::cout << endl;
    gb->gameResults();
    std::cout <<"FINAL BOARD: "<< std::endl;
    gb->paint();
}

//-------------------------------------TESTING CODE-----------------------------------------------
    //GameBoard gb;
    //Entity test("PA", "0000");
    //test.showDetails();

    //unordered_map<string, unique_ptr<Entity>> testMap;
    //unique_ptr<Entity> test2(new Entity("EA0", "0001"));
    //testMap.insert({"A0E", make_unique<Entity>("EA0", "0001")});
    //unique_ptr<Entity> test2 (new Entity("EA0", "0001"));
    //test2->showDetails();
    //testMap["A0E"] -> showDetails();

    /*
    unique_ptr<GameBoard> gb(new GameBoard());
    gb->addEntity("E0", "EA0", 101);
    gb->addEntity("P", "PA", 201);
    gb->addEntity("R", "R", 202);
    gb->addEntity("QW", "QAW", 0);
    gb->paint();
    */
    /*
    gb->addEntity("E0","EA0", 101);
    gb->addEntity("E1", "EH1", 3);
    gb->addEntity("E2", "EV2", 2);
    gb->addEntity("E3", "EV3", 1);
    gb->addEntity("E4","EV4", 103);
    gb->addEntity("R", "R", 202);

    //std::cout << gb->isSpaceEmpty(1919) << std::endl;
    //gb->deleteEntity("E0");
    //gb->moveEntityUP("E0");
    //gb->moveEntityDOWN("E0");
    //gb->moveEntityLEFT("E0");
    //gb->moveEntityRIGHT("E0");

    //gb->attack("E0");

    gb->paint();

    std::cout << " MOVE LEFT " << std::endl;
    gb-> moveEntityLEFT("E0");
    gb->paint();

    std::cout << " Attack " << std::endl;
    gb->attack("E0");
    gb->paint();

    std::cout << " TRY MOVE DOWN " << std::endl;
    gb->moveEntityDOWN("E0");
    gb->paint();

    std::cout << " MOVE LEFT " << std::endl;
    gb->moveEntityLEFT("E0");
    gb->paint();

    std::cout << " MOVE UP " << std::endl;
    gb->moveEntityUP("E0");
    gb->paint();

    std::cout << " MOVE UP " << std::endl;
    gb->moveEntityUP("E0");
    gb->paint();
    std::cout << " MOVE UP - ILLEGAL " << std::endl;
    gb->moveEntityUP("E0");
    gb->paint();

    std::cout << " ATTACK " << std::endl;
    gb->attack("E1");
    gb->paint();

    std::cout << " TRY MOVING DEAD PLAYER " << std::endl;
    gb->moveEntityRIGHT("E0");
    gb->paint();
    */
    /*
    unique_ptr<GameBoard> gb(new GameBoard());
    gb->addEntity("E0", "EH0", 301);
    gb->addEntity("E1", "EH1", 300);
    gb->addEntity("P", "PH", 303);
    gb->addEntity("R", "R", 302);
    gb->paint();
    gb->attack("E0");
    gb->paint();
    gb->gameResults();
    */
    //std::cout << std::endl << "Hello World!\n";