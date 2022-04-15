// BombermanMain.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string.h>
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
    void showDetails() {
        std::cout << "Type: " << type << " Wepon: " << weapon << " pos " << position << std::endl; 
    }
    ~Enity(){}
};

class GameBoard {
private: 
    unordered_map<string, unique_ptr<Enity>> testMap;
public: 
    GameBoard() {
        
    }
    void addEnity(string newE, string pos) {
        testMap.insert({ pos, make_unique<Enity>(newE, pos)});
        testMap[pos]->showDetails();

    }
    bool detectEnity(string pos) {
        if (testMap[pos] != NULL) {
            std::cout << "space used";
            return true; 
        }
        else {
            return false; 
        }
    }
    unique_ptr<Enity> getEnity(string pos) {
        if (testMap[pos] != NULL) {
            return testMap[pos];
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
    gb->addEnity("EA0", "1919");
    gb->detectEnity("1919");
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
