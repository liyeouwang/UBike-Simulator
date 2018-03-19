#include "UBikeSystemIMP.h"
#include<iostream>
#include<fstream>
using namespace std;

// Add your code here
void UBikeSystemIMP::InitDistTable
(std::string MapFile)
{
    this->priceTable.calcAllPairsShortestPath(MapFile);
}

void UBikeSystemIMP::NewBike
(std::string classType, std::string license, int mileage, std::string station)
{
    // initial
    UBike* newUbike = new UBike();
    newUbike->isRented = false;
    newUbike->mileage = mileage;
    newUbike->license = license;
    newUbike->station = station;
    newUbike->classType = classType;


    // add to hash table
    ubHashTable.addUBikePtr(newUbike);

    // add to the station's heap
    ubStations[station][classType].addUBikePtr(newUbike);


}

void UBikeSystemIMP::JunkIt
(std::string license)
{
    //find the Ubike but not delete
    UBike* bike = ubHashTable.findUBikePtr(license, false);

    if(bike==NULL || bike->isRented)return;
    else
    {
        bike = ubStations[bike->station][bike->classType].removeUBikePtr(bike->heapIndex);
        bike = ubHashTable.findUBikePtr(license, true);
        if(bike != NULL)
        delete bike;
    }


}

void UBikeSystemIMP::Rent
(std::string classType, std::string station)
{
    if(ubStations[station][classType].isEmpty() == true)
        return;
    UBike* bike = ubStations[station][classType].removeUBikePtr(1);
    if(bike==NULL)return;
    else
    {
        bike->isRented=true;
        ubStations[station]["Rented"].addUBikePtr(bike);
    }

}

void UBikeSystemIMP::Return
(std::string station, std::string license, int returnMile)
{
    UBike* bike = ubHashTable.findUBikePtr(license, false);
    if(bike == NULL || bike->isRented == false)
        return;
    bike = ubStations[bike->station]["Rented"].removeUBikePtr(bike->heapIndex);
    if(bike == NULL)
        return;
    else
    {
        net += priceTable.calcPrice(returnMile-bike->mileage,  bike->classType,  bike->station,  station);
        bike->mileage = returnMile;
        bike->isRented = false;
        ubStations[bike->station][bike->classType].addUBikePtr(bike);
    }

}

void UBikeSystemIMP::Trans
(std::string station, std::string license)
{
    UBike* bike = ubHashTable.findUBikePtr(license, false);
    if(bike == NULL || bike->isRented == true)
        return;
    bike = ubStations[bike->station][bike->classType].removeUBikePtr(bike->heapIndex);
    if(bike == NULL)
        return;
    else
    {
        bike->station = station;
        ubStations[bike->station][bike->classType].addUBikePtr(bike);
    }

}

void UBikeSystemIMP::ShutDown()
{
    for(int i=0 ; i < 256 ; i++)
    {
        if(ubHashTable[i].empty())
            continue;
        for(auto iter = ubHashTable[i].begin() ; iter != ubHashTable[i].end() ; iter++)
            if(*iter != NULL)
                delete *iter;
    }

}
