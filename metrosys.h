#ifndef metrosys
#define metrosys
#define SIZE 10


struct MetroStation{
    char name[20];
    double x,y;
}typedef MetroStation;

struct MetroLine{
    char color[20];
    MetroStation MetroStations[SIZE];

}typedef MetroLine;

struct MetroSystem{
    char name[20];
    MetroLine MetroLines[SIZE];

}typedef MetroSystem;

int equals(MetroStation,MetroStation);
void addStation(MetroLine*,MetroStation);
int hasStation(MetroLine,MetroStation);
MetroStation getFirstStop(MetroLine);
MetroStation getPriorStop(MetroLine,MetroStation);
MetroStation getNextStop(MetroLine,MetroStation);
void addLine(MetroSystem*,MetroLine);
void printLine(MetroLine);
void printPath(MetroStation[]);
double getDistanceTravelled(MetroStation[]);
MetroStation findNearestStation(MetroSystem,double,double);
void getNeighboringStations(MetroSystem,MetroStation,MetroStation[]);
void findPath(MetroStation,MetroStation,MetroStation[],MetroSystem);
void recursiveFindPath(MetroStation,MetroStation,MetroStation[],MetroStation[],MetroSystem,MetroStation[]);

#endif