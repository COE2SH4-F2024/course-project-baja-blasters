#include "objPos.h"
#include "objPosArrayList.h"
#define FOOD_SPAWN_CAP = 5;
class Food
{
    private:
        objPosArrayList* foodXYS;
    public:
        Food();
        //Constructors
        ~Food();
        //Destructor
        Food(const Food &food);
        Food& operator=(const Food &food); 
        //Copy and copy assignment

        void generateFood(objPos playpos);
        objPos getFoodpos() const;
};



