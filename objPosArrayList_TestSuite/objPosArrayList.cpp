#include "objPosArrayList.h"

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

#include "objPosArrayList.h"

// Paste your Tested implementation here.
// Paste your Tested implementation here.
// Paste your Tested implementation here.
objPosArrayList::objPosArrayList()
{
    arrayCapacity= ARRAY_MAX_CAP;
    listSize=0;
    aList= new objPos[ARRAY_MAX_CAP];     
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}

objPosArrayList::objPosArrayList(const objPosArrayList &array)
{
    arrayCapacity=ARRAY_MAX_CAP;
    aList= new objPos[ARRAY_MAX_CAP];
    listSize=array.getSize();
    for (int i = 0; i < listSize; i++)
    {
        aList[i]=array.aList[i];
    }
}

objPosArrayList& objPosArrayList::operator =(const objPosArrayList&array)
{
    if (this!=&array)
    {
        this->listSize=array.getSize();
        for (int i = 0; i < this->listSize; i++)
        {
            this->aList[i]=array.aList[i];
        }
    }
    return *this;
}


int objPosArrayList::getSize() const
{
    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    if(listSize>=arrayCapacity) return;

    for (int i = listSize; i > 0 ; i--)
    {
        aList[i]=aList[i-1];
    }
    aList[0]=thisPos;
    listSize++;

}

void objPosArrayList::insertTail(objPos thisPos)
{
    if(listSize>=arrayCapacity) return;

    aList[listSize]=thisPos;
    listSize++;
}

void objPosArrayList::removeHead()
{
    if(listSize==0) return;

    for (int i = 0; i < listSize-1; i++)
    {
        aList[i]=aList[i+1];
    }
     listSize--;
}

void objPosArrayList::removeTail()
{
    if(listSize==0) return;
    listSize--;
}

objPos objPosArrayList::getHeadElement() const
{
    return aList[0];
}

objPos objPosArrayList::getTailElement() const
{
    return aList[listSize-1];
}

objPos objPosArrayList::getElement(int index) const
{
    if(listSize==0)
    {
        return aList[0];
    }
    else if(index<=0)
    {
        index = 0;
    }
    else if(index>listSize)
    {
        index=listSize-1;
    }

    return aList[index];
}