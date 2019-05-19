#include <stdio.h>
#include <Math.h>
#include <string.h>
#include <stdlib.h>
#include "metrosys.h"
int minDistance=1000;
int equals(MetroStation s1,MetroStation s2){
    return strcmp(s1.name,s2.name)==0;
}
void addStation(MetroLine* metroLine,MetroStation metroStation){
    if(metroLine->MetroStations[0].name[0]!= 0){
        printf("The Line is full.Can not add new station\n");
        return;
    }else if(metroLine->MetroStations[SIZE-1].name[0]==0){
        metroLine->MetroStations[SIZE-1] = metroStation;
        return;
    }
    int i = 1;
    while(i<SIZE){
       if(metroLine->MetroStations[SIZE-i].name[0]!=0)
           i++;
       else
           break;
    }
    metroLine->MetroStations[SIZE-i]=metroStation;
}
int hasStation(MetroLine metroLine,MetroStation metroStation){
    int i = 0;

    for(i;i<SIZE;i++){
        if(metroLine.MetroStations[i].name == metroStation.name)
            return 1;
    }
    return 0;

}
int hasStationIn(MetroStation metroStationArray[],MetroStation metroStation){
    int i = 0;

    for(i;i<SIZE;i++){
        if(equals(metroStationArray[i] , metroStation) )
            return 1;
    }
    return 0;

}
MetroStation getFirstStop(MetroLine metroLine){
    MetroStation gonnaReturnThis={'\0'};
    if(metroLine.MetroStations[SIZE-1].name[0] == 0)
        return gonnaReturnThis;
    else {
        gonnaReturnThis = metroLine.MetroStations[SIZE - 1];
        return gonnaReturnThis;
    }
}
MetroStation getPriorStop(MetroLine metroLine,MetroStation metroStation){
    MetroStation priorStation = {'\0'};
    int i;

    if(equals(metroLine.MetroStations[SIZE-1],metroStation))
        return priorStation;
    else{
        for(i = 2 ; i <= SIZE ; i++){
            if(equals(metroLine.MetroStations[SIZE-i],metroStation))
                priorStation = metroLine.MetroStations[SIZE-i+1];
        }
        return priorStation;
    }
}
int getLastStationLoc(MetroStations metroStations[]){
    int i=1;
    while(metroStations[SIZE-i].name[0]!=0)
        i++;
    return i;
}
MetroStation getNextStop(MetroLine metroLine,MetroStation metroStation){
    MetroStation nextStation= {'\0'};
    int i;
    int lastStationLoc = getLastStationLoc(metroLine.MetroStations);
    if(equals(metroLine.MetroStations[lastStationLoc-1],metroStation))
        return nextStation;
    else{
        for(i = 1 ; i < SIZE ; i++){
            if(equals(metroLine.MetroStations[SIZE-i],metroStation))
                nextStation = metroLine.MetroStations[SIZE-i-1];
        }
        return nextStation;
    }
}
void addLine(MetroSystem* metroSystem,MetroLine metroLine){
    if(metroSystem->MetroLines[0].color[0] != 0){
        printf("The metro system is full.Can not add new line\n");
        return;
    }else if(metroSystem->MetroLines[SIZE-1].color[0] == 0){
        metroSystem->MetroLines[SIZE-1]=metroLine;
        return;
    }

    int i = 0;
    while(i<SIZE){
        if(metroSystem->MetroLines[i].color[0]== 0)
            i++;
        else
            break;
    }
    metroSystem->MetroLines[i-1]=metroLine;
}
void printLine(MetroLine metroLine){
    if(metroLine.MetroStations[SIZE-1].name[0]==0)
        printf("This metro line empty");
    else{
        int i = 1;
        printf("Metro line %s : ",metroLine.color);
        while(i<=SIZE && metroLine.MetroStations[SIZE-i].name[0] != 0){
            printf("%s, ",metroLine.MetroStations[SIZE-i].name);
            i++;
        }
        printf("\n");
    }
}
void printPath(MetroStation metroStations[]) {
    int i = 1;
    while (i <= SIZE && metroStations[SIZE - i].name[0] != 0) {
        printf("%d.%s\n", i, metroStations[SIZE - i].name);
        i++;
    }
}
double getDistanceTravelled(MetroStation metroStations[]) {
    double totalDistance=0;
    if (metroStations[SIZE - 1].name[0] == 0) {
        printf("The given station array is empty\n");
        return 0;
    }else if (metroStations[SIZE - 2].name[0] == 0) {
        printf(" The given station array has only 1 station\n");
        return 0;
    }else{
        int i = 1;
        while(i<SIZE-1 && metroStations[SIZE-i].name[0]!= 0 && metroStations[SIZE-i-1].name[0]!= 0){
            totalDistance += pow(pow((metroStations[SIZE-i].x - metroStations[SIZE-i-1].x),2) + pow((metroStations[SIZE-i].y - metroStations[SIZE-i-1].y),2),0.5);
            i++;
        }
        return totalDistance;
    }

}
MetroStation findNearestStation(MetroSystem metroSystem,double x,double y){
    MetroStation nearestStation = metroSystem.MetroLines[SIZE-1].MetroStations[SIZE-1];
    MetroStation temp = nearestStation;
    double distance =  pow(pow((temp.x - x),2) + pow((temp.y - y),2),0.5),tempDistance;
    for(int i = 1; (i <= SIZE) && (metroSystem.MetroLines[SIZE-i].color[0]!=0);i++){
        for(int k = 1; (k <= SIZE) && (metroSystem.MetroLines[SIZE-i].MetroStations[SIZE-k].name[0]!=0);k++){
            temp = metroSystem.MetroLines[SIZE-i].MetroStations[SIZE-k];
            tempDistance = pow(pow((temp.x - x),2) + pow((temp.y - y),2),0.5);
            if(distance > tempDistance   ) {
                nearestStation = temp;
                distance = tempDistance;
            }
        }
    }
    return nearestStation;
}
void getNeighboringStations(MetroSystem metroSystem ,MetroStation metroStation,MetroStation metroStationArray[]){
    MetroStation temp;
    int iter = 1;
    for(int i = 1; (i <= SIZE) && (metroSystem.MetroLines[SIZE-i].color[0] != 0);i++) {
        for (int k = 1; (k <= SIZE) && (metroSystem.MetroLines[SIZE - i].MetroStations[SIZE - k].name[0] != 0); k++) {

                temp = metroSystem.MetroLines[SIZE-i].MetroStations[SIZE-k];

                if(equals(temp,metroStation)) {
                    if( !hasStationIn(metroStationArray,getPriorStop(metroSystem.MetroLines[SIZE-i],temp)) && (getPriorStop(metroSystem.MetroLines[SIZE-i],temp).name[0]!=0) ) {
                        metroStationArray[SIZE-iter] = getPriorStop(metroSystem.MetroLines[SIZE - i], temp);
                        iter++;
                    }
                    if(!hasStationIn(metroStationArray,getNextStop(metroSystem.MetroLines[SIZE-i],temp)) && (getNextStop(metroSystem.MetroLines[SIZE-i],temp).name[0]!=0) ) {
                        metroStationArray[SIZE - iter] = getNextStop(metroSystem.MetroLines[SIZE - i], temp);
                        iter++;
                    }
                }
        }
    }
 }

void findPath(MetroStation start,MetroStation finish,MetroStation path[],MetroSystem ms){
    MetroStation  partialPath[SIZE] = {'\0'};

    recursiveFindPath(start,finish,partialPath,path,ms,path);

}
void addStationS(MetroStation* metroStationA,MetroStation metroStation){
    for(int i =1 ; i<=SIZE;i++)
        if(metroStationA[SIZE-i].name[0]==0) {
            metroStationA[SIZE - i] = metroStation;
            return;
        }
}
void copyArray(MetroStation a1[],MetroStation a2[]){
    for(int i = 1; i <= SIZE; i++){
        a1[SIZE-i]=a2[SIZE-i];
    }
    return;
}
void recursiveFindPath(MetroStation start,MetroStation finish,MetroStation partialPath[],MetroStation bestPath[],MetroSystem ms,MetroStation returnA[]) {
    MetroStation neighbors[SIZE]  ={'\0'};
    MetroStation duplicatedPath[SIZE];
    double minTemp=0;
    if (equals(start, finish) ) {
        addStationS(partialPath,finish);
        minTemp=getDistanceTravelled(partialPath);
        if(minTemp<minDistance) {
            copyArray(returnA,partialPath);
            return;
        }
    }
    if(hasStationIn(partialPath,start)) {
        return;
    }

    getNeighboringStations(ms, start, neighbors);

    for (int i = 1; i <= SIZE; i++) {
        if (neighbors[SIZE - i].name[0] != 0   ) {
             copyArray(duplicatedPath,partialPath);
              if(!hasStationIn(duplicatedPath,neighbors[SIZE - i])) {
                  addStationS(duplicatedPath, start);
                  recursiveFindPath(neighbors[SIZE - i], finish, duplicatedPath, partialPath, ms,returnA);
              }else
                  continue;

        }

    }




}
