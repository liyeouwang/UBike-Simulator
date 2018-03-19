#include "PriceTableIMP.h"
using namespace std;

// Add your code here
void PriceTableIMP::calcAllPairsShortestPath(std::string mapFile)
{
    int i, j, k, n;
    char sta1[100], sta2[100];
    for(i=0 ; i<StationNum ; i++)
        for(j = 0 ; j<StationNum ; j++)
            this->distTable[StationNames[i]][StationNames[j]] = 1000;
    for(i=0 ; i<StationNum ; i++)
        distTable[StationNames[i]][StationNames[i]] = 0;

    FILE * in;
    in = fopen(mapFile.c_str(), "r");
    while(fscanf(in, "%s %s %d",sta1,sta2,&n) != EOF)
    {
        string a(sta1);
        string b(sta2);
        distTable[a][b] = min(n, distTable[a][b]);
        distTable[b][a] = min(n, distTable[b][a]);
    }
    fclose(in);

    for(i = 0 ; i < StationNum ; i++){
        for(j = 0 ; j < StationNum ; j++){
            for(k=0 ; k < StationNum ; k++){
                int present = distTable[StationNames[j]][StationNames[k]];
                int now = distTable[StationNames[j]][StationNames[i]] + distTable[StationNames[i]][StationNames[k]];
                if( now < present )
                   distTable[StationNames[j]][StationNames[k]] = now;
            }
        }
    }
}

int PriceTableIMP::calcPrice
(int milageDiff, std::string bClass, std::string from, std::string toStation)
{
    if(milageDiff <= distTable[from][toStation])
        return milageDiff * dscntRates.at(bClass);
    else
        return milageDiff * oriRates.at(bClass);
}
