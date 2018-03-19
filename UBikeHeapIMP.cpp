#include "UBikeHeapIMP.h"
#include <algorithm>
using namespace std;
// Add your code here

void UBikeHeapIMP::addUBikePtr(UBike* ubptr)
{
	int currentNode = ++number;  //currentNode =(number+1)
	while(currentNode > 1 && ubptr->mileage < this->at(currentNode/2)->mileage)
	{
		this->at(currentNode) = this->at(currentNode/2);
		this->at(currentNode)->heapIndex=currentNode;
        currentNode/=2;
	}
	this->at(currentNode) = ubptr;
	ubptr->heapIndex = currentNode;
}

UBike* UBikeHeapIMP::removeUBikePtr(int heapIndex)
{
	if(number==0 || heapIndex>number)  //empty or out of range
		return NULL;
	UBike* last = this->at(number);
	number--;
	UBike* bike = this->at(heapIndex);
	int currentNode = heapIndex;
	int child = currentNode*2;
	
	while(child <= number)
	{
		if(child+1 <= number && this->at(child)->mileage > this->at(child+1)->mileage)
		child++;
		if(last->mileage <= this->at(child)->mileage)
		break;
		
		this->at(currentNode) = this->at(child);
		this->at(currentNode)->heapIndex = currentNode;
		currentNode = child;
		child *=2;
	}
	this->at(currentNode) = last;
	this->at(currentNode)->heapIndex = currentNode;
	return bike; 
}

/*
UBike* UBikeHeapIMP::removeUBikePtr(int heapIndex)
{
    UBike* bike=this->at(heapIndex);
    UBike* ubptr=this->at(number);
    int mil=this->at(number)->mileage;
    int currentNode =heapIndex;
    this->at(currentNode) = this->at(number);
    this->at(currentNode)->heapIndex=currentNode;
    this->at(number)=NULL;
    number--;
    if(currentNode > 1 && this->at(currentNode)->mileage<this->at(currentNode/2)->mileage)
    {
        while(currentNode > 1 && mil < this->at(currentNode/2)->mileage)
        {
            this->at(currentNode) = this->at(currentNode/2);
            this->at(currentNode)->heapIndex=currentNode;
            currentNode/=2;
        }
        this->at(currentNode) = ubptr;
        ubptr->heapIndex = currentNode;
    }
    else
    {
        while(1)
        {
            if(currentNode*2+1 <= number)
            {
                int leftMil=this->at(currentNode*2)->mileage;
                int rightMil=this->at(currentNode*2+1)->mileage;
                if(leftMil<mil && rightMil<mil)
                {
                    if(leftMil<=rightMil)
                    {
                        this->at(currentNode)=this->at(currentNode*2);
                        this->at(currentNode)->heapIndex=currentNode;
                        currentNode*=2;
                    }
                    else
                    {
                        this->at(currentNode)=this->at(currentNode*2+1);
                        this->at(currentNode)->heapIndex=currentNode;
                        currentNode=currentNode*2+1;

                    }

                }
                else if(leftMil<mil)
                {
                    this->at(currentNode)=this->at(currentNode*2);
                    this->at(currentNode)->heapIndex=currentNode;
                    currentNode*=2;
                }
                else if(rightMil<mil)
                {
                    this->at(currentNode)=this->at(currentNode*2+1);
                    this->at(currentNode)->heapIndex=currentNode;
                    currentNode=currentNode*2+1;
                }
                else break;

            }
            else if(currentNode*2 <= number)
            {
                int leftMil=this->at(currentNode*2)->mileage;
                if(leftMil<mil)
                {
                    this->at(currentNode)=this->at(currentNode*2);
                    this->at(currentNode)->heapIndex=currentNode;
                    currentNode*=2;
                }
                else break;
            }
            else break;
        }
        this->at(currentNode) = ubptr;
        ubptr->heapIndex = currentNode;
    }
    return bike;
}
*/
