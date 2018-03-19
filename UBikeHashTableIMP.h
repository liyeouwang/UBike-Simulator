#ifndef UBikeHashTableIMP_h
#define UBikeHashTableIMP_h

#include "readonly/UBikeHashTableADT.h"

#include <string>
using namespace std;

class UBikeHashTableIMP : public UBikeHashTableADT
{
public:
    // Add your code here

    //=================================================================
    // add the ubike pointer to the hash table
    //=================================================================
    void addUBikePtr(UBike* ubptr);
    
    //=================================================================
    // find the ubike pointer in the hash table given ubike license
    // if toRemove is true, remove the the pointer from the hash table
    // return the ubike pointer that points to the ubike "license"
    //=================================================================
    UBike* findUBikePtr(std::string license, bool toRemove);
    
    
    //change from license to address(using hashing function)
    int calcLicense(string x);
};

#endif
