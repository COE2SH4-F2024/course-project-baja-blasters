#ifndef FOOD_H
#define FOOD_H

#include "objPos.h"
#include "objPosArrayList.h"
#include <time.h>
#include <stdlib.h>
#define FOOD_SPAWN_CAP 5

class Food
{
    private:
        objPos* foodXYS;
        int binsize;
        bool foodoscillator;
        bool specialfood;
        char normalfoodsym;
        char specialfoodsym;

    public:
        //Constructors
        Food();
        //Destructor
        ~Food();
        //Copy and copy assignment
        Food(const Food &food);
        Food& operator=(const Food &food); 

        // Generate food
        void generateFood(objPosArrayList playpos, int xrange, int yrange);

        // Getting food position
        objPos getFoodpos(int index) const;
        objPos getFoodpos(int x, int y) const;

        // Check for special food
        bool specialfoodcheck();
        char getnormal();
        char getspecial();
        
        // oscilator functions
        void switchoscillator();
        bool getfoodoscillator();

        
};
#endif