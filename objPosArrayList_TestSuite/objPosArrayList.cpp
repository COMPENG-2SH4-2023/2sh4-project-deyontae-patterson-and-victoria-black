#include "objPosArrayList.h"

objPosArrayList::objPosArrayList()
{
    sizeArray = 0;
    aList = new objPos[ARRAY_MAX_CAP];
}

objPosArrayList::~objPosArrayList()
{
    for(int i = 0; i < sizeArray; i++)
    {
        removeTail();
    }

    delete[] aList;
}

int objPosArrayList::getSize()
{
    return sizeArray;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    int i;

    for(i=sizeArray; i>0; i--)
    {
        aList[i-1].getObjPos(aList[i]);
    }

    thisPos.getObjPos(aList[0]);

    sizeArray++;
}

void objPosArrayList::insertTail(objPos thisPos)
{
    thisPos.getObjPos(aList[sizeArray]);

    sizeArray++;
}

void objPosArrayList::removeHead()
{
    int i;

    for(i=0; i<sizeArray-1; i++)
    {
        aList[i+1].getObjPos(aList[i]);
    }

    removeTail();
}

void objPosArrayList::removeTail()
{
    aList[sizeArray-1].setObjPos(0, 0, 0);

    sizeArray--;
}
        
void objPosArrayList::getHeadElement(objPos &returnPos)
{
    aList[0].getObjPos(returnPos);
}

void objPosArrayList::getTailElement(objPos &returnPos)
{
    aList[sizeArray-1].getObjPos(returnPos);
}

void objPosArrayList::getElement(objPos &returnPos, int index)
{
    aList[index].getObjPos(returnPos);
}

// Paste your CUTE Tested implementation here.
// Paste your CUTE Tested implementation here.
// Paste your CUTE Tested implementation here.
