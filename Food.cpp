#include "Food.h"
#include <time.h>
//Constructors
Food::Food()
{
    foodXYS= new objPos[FOOD_SPAWN_CAP];
}

//Destructor        
Food::~Food()
{
    delete[] foodXYS;
}

//Copy and copy assignment       
Food::Food(const Food &food)
{
    foodXYS= new objPos[FOOD_SPAWN_CAP];
    for (int i = 0; i< FOOD_SPAWN_CAP; i++)
    {
        foodXYS[i]=food.foodXYS[i];
    }
    
}

Food& Food::operator=(const Food &food)
{
    if (this!=&food)
    {
        for (int i = 0; i < FOOD_SPAWN_CAP; i++)
        {
            this->foodXYS[i]=food.foodXYS[i];
        }
        
    }
    return *this;
}


void Food:: generateFood(objPos playpos)
{
    srand(time(NULL));
    int availablepos[10][20] = {0};
    availablepos[playpos.pos->x][playpos.pos->y] = 1;
    int i;
    for (i = 0; i < FOOD_SPAWN_CAP; i++)
    {
        int j;
        do
        {
            foodXYS[i].pos->x = rand() % 18 + 1;
            foodXYS[i].pos->x = rand() % 8 + 1; 
            //symbol selection here
            
        } while ((availablepos[foodXYS[i].pos->y][foodXYS[i].pos->x] != 0));
        availablepos[foodXYS[i].pos->y][foodXYS[i].pos->x]=1;
    }
}
objPos Food:: getFoodpos(int index) const
{
    objPos returnobj;
    if (index>=0 || index < FOOD_SPAWN_CAP)
    {
        returnobj=foodXYS[index];
    }
    else if(index<0)
    {
        returnobj=foodXYS[0];
    }
    else
    {
        returnobj=foodXYS[ARRAY_MAX_CAP-1];
    } 
    return returnobj; 
}