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
    public:
        Food();
        //Constructors
        ~Food();
        //Destructor
        Food(const Food &food);
        Food& operator=(const Food &food); 
        //Copy and copy assignment

        void generateFood(objPos playpos, int xrange, int yrange);
        objPos getFoodpos(int index) const;

        int getBinsize();
};


// Proposition: include a GameMechs pointer so we can change up
// the dimensions of availablepos[]. 

#endif
