#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "Food.h"
#include <iostream>

class Player
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    
    public:
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};  // This is the direction state

        // constructors
        Player(); 
        Player(GameMechs* thisGMRef,Food*thisFood);
        // destructors
        ~Player();
        // Copy assignment and copy assignment editor
        Player(const Player &pp);
        Player& operator=(const Player&pp);

        // functions to involving the player
        objPosArrayList* getPlayerPos() const;      
        void updatePlayerDir();
        void movePlayer();
        bool checkFoodconsumption(); 
        void increasePlayerlength();
        bool checkselfcollision();
        int getSpeed(); 
        void setSpeed(int s);        

        // functions involving food
        Food* getFoodlist()const;

    private:
        objPosArrayList* player;
        char headsymbol;
        char bodysymbol;       
        enum Dir myDir;
        Food* foodlist;
        // Need a reference to the Main Game Mechanisms
        GameMechs* mainGameMechsRef;
        int rowNums; 
        int colNums; 
        int speed; 

};

#endif