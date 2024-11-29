#include "Food.h"
#include <time.h>
//Constructors
Food::Food()
{
    binsize= FOOD_SPAWN_CAP;
    foodXYS= new objPos[FOOD_SPAWN_CAP];
    foodoscillator =true;
    specialfood = false;
    normalfoodsym = 'o';
    specialfoodsym = 'O';
}

//Destructor        
Food::~Food()
{
    delete[] foodXYS;
}

//Copy       
Food::Food(const Food &food)
{
    foodXYS= new objPos[binsize];
    for (int i = 0; i< binsize; i++)
    {
        foodXYS[i]=food.foodXYS[i];
    }
    foodoscillator = food.foodoscillator;
    specialfood = food.specialfood;
    normalfoodsym = food.normalfoodsym;
    specialfoodsym = food.specialfoodsym;
}
// Copy Assignment operator
Food& Food::operator=(const Food &food)
{
    if (this!=&food)
    {
        for (int i = 0; i < binsize; i++)
        {
            this->foodXYS[i]=food.foodXYS[i];
        }
        this->foodoscillator = food.foodoscillator;
        this->specialfood = food.specialfood;
        this->normalfoodsym = food.normalfoodsym;
        this->specialfoodsym = food.specialfoodsym;
    }
    return *this;
}

// Generate food function
void Food:: generateFood(objPosArrayList playpos, int xrange, int yrange)
{
    srand(time(NULL));
    // array that shows where the snake is
    int availablepos[yrange][xrange] = {0};
    for(int i = 0; i < playpos.getSize(); i++){
        availablepos[playpos.getElement(i).pos->y][playpos.getElement(i).pos->x] = 1; 
    }
    // generating food
    int i;
    for (i = 0; i < binsize; i++)
    {
        int j;
        do
        {
            foodXYS[i].pos->x = rand() % (xrange-2) + 1;
            foodXYS[i].pos->y = rand() % (yrange-2) + 1; 
            //On the third food selection, there is a fifty percent chance to spawn 
            //a special character. 
            if(i==3)
            {
                bool cointoss = rand()%2;
                if(cointoss)
                {
                    foodXYS[i].symbol=specialfoodsym;
                    specialfood = true;
                }
                else
                {
                    foodXYS[i].symbol=normalfoodsym;
                    specialfood = false;
                }
            }
            // Normal symbol generation
            else
            {
                foodXYS[i].symbol=normalfoodsym;
            }

        } while ((availablepos[foodXYS[i].pos->y][foodXYS[i].pos->x] != 0));

        // stores the positions of the food generated so it duplicate next time 
        availablepos[foodXYS[i].pos->y][foodXYS[i].pos->x]=1;
    }
}

// Returns objPos of a food given an index (called if using a list or an array)
objPos Food:: getFoodpos(int index) const
{
    objPos returnobj;
    if (index>=0 || index < binsize)
    {
        returnobj=foodXYS[index];
    }
    // If index is less than 0, return the first generated food
    else if(index<0)
    {
        returnobj=foodXYS[0];
    }
    // Returns the last generated food if all else fails
    else
    {
        returnobj=foodXYS[binsize-1];
    } 
    return returnobj; 
}

// Returns the objPos of a food given coordinates
// (called when checking if a spot on the board has a food or not)
objPos Food ::getFoodpos(int x, int y) const
{
    for (int i = 0; i < binsize; i++)
    {
        if(x==getFoodpos(i).pos->x && y==getFoodpos(i).pos->y)
        {
            return getFoodpos(i);
        }
    }
    return objPos(0,0,0);
}

//Used to turn on and off the blinking food feature 
bool Food::switchoscillator()
{
    if(foodoscillator)
    {
        foodoscillator = false;
    }
    else
    {
        foodoscillator = true;
    }
}

// The next four are pretty self explanatory
bool Food:: specialfoodcheck()
{
    return specialfood;
}

bool Food:: getfoodoscillator()
{
    return foodoscillator;
}

char Food:: getnormal()
{
    return normalfoodsym;
}

char Food:: getspecial()
{
    return specialfoodsym;
}