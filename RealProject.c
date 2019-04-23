#include <stdio.h>
#include <stdlib.h>
typedef unsigned int uint;
typedef struct teams{
    char lname[12];
    char sname;
    uint played;
    uint won;
    uint lost;
    uint draw;
    uint pscore;
    uint nscore;
    uint average;
    uint points;
}Team;

int NumberOfTeams;                                                  //Takim sayisini tutan degisken
int* AddressOfNumberOfTeams = &NumberOfTeams;                       //Takim sayisinin pointeri

void ReadFromSettings(int* address){                                //Takim sayisi verisini almaak icin ornek fonksiyon
    printf("Kac tane takim olacak?");
    scanf("%d",address);
}


void BuildTeams(int TeamCount , Team MainStruct[]){
    for(struct {char i; int a;}  fV = {65 , 0};
                                fV.a < TeamCount;
                                fV.a++ , fV.i++){
        MainStruct[fV.a].sname = fV.i;
        MainStruct[fV.a].points = 0;
        MainStruct[fV.a].played = 0;
        MainStruct[fV.a].won = 0;
        MainStruct[fV.a].lost = 0;
        MainStruct[fV.a].draw = 0;
        MainStruct[fV.a].points = 0;
        MainStruct[fV.a].pscore = 0;
        MainStruct[fV.a].nscore = 0;
        MainStruct[fV.a].average = 0;
    }
}



int main(){
    ReadFromSettings(AddressOfNumberOfTeams);
    Team team[NumberOfTeams];
    BuildTeams(NumberOfTeams , team);
    return 0;
}
