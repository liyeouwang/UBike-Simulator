#include "UBikeHashTableIMP.h"
#include <string>
#include <bitset>
#include <iostream>
using namespace std;

//=================================================================
// add the ubike pointer to the hash table
//=================================================================
void UBikeHashTableIMP::addUBikePtr(UBike* ubptr)
{
	if(ubptr == NULL)
        return;
    (this->at(calcLicense(ubptr->license))).push_front(ubptr);
}


UBike* UBikeHashTableIMP::findUBikePtr(std::string license, bool toRemove)
{
	int address = calcLicense(license);
	if(this->at(address).empty())  //empty
		return NULL;
	forward_list <UBike*> :: iterator it;	
	for(it = (this->at(address)).begin(); it != (this->at(address)).end() ; it++)
	{
		if((*it)->license == license )
		{
			if(toRemove == true)
			(this->at(address)).remove(*it);
			return *it;
		}
	}
	
    return NULL; //not found
}


//change from license to address(using hashing function)
int UBikeHashTableIMP::calcLicense(string x)
{
	int s[5];
	if(isdigit(x[0]))		//number
		s[0] = x[0]-'0';
	else					//．A・~・Z・
		s[0] = x[0]-55;
		
	for(int i = 1;i<5;i++)
	{
		if(isdigit(x[i]))      //number
			s[i] = s[i-1]*29 + x[i]-'0';
		else					//．A・~・Z・
			s[i] = s[i-1]*29 + x[i]-55;	
	}
	
	bitset<40> b(s[4]);
  	bitset<8> address;
	for(int i=5 ; i <13 ; i++)
	 	address[i-5] = b[i];		//address in binary form
	return address.to_ulong();   //convert from binary to decimal
	
}
