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
int PointsForWinning;
int PointsForLosing;
int PointsForDraw;

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
void ReadMatchFromKeyboard(Team MainStruct[]){
    printf("Maclari tek tek girin cikmak icin N yazin.");
    char initial[7];
    while(1){
        scanf("%c",initial);
        if(initial == "N"){
            break;
        }
        char HomeTeam = initial[0];
        int HomeTeamScore = initial[2];
        char GuestTeam = initial[4];
        int GuestTeamScore = initial[6];
        for(int i = 0;i <= NumberOfTeams; i++){

            if(HomeTeam == MainStruct[i].sname){
                for(int a = 0; a <= NumberOfTeams; a++){

                    if(GuestTeam == MainStruct[a].sname){
                        MainStruct[i].pscore += HomeTeamScore;
                        MainStruct[i].nscore += GuestTeamScore;
                        MainStruct[a].pscore += GuestTeamScore;
                        MainStruct[a].nscore += HomeTeamScore;
                        if(HomeTeamScore > GuestTeamScore){
                            MainStruct[i].won += 1;
                            MainStruct[a].lost += 1;
                        }
                        if(HomeTeamScore < GuestTeamScore){
                            MainStruct[a].won += 1;
                            MainStruct[i].lost += 1;
                        }
                        if(HomeTeamScore == GuestTeamScore){
                            MainStruct[i].draw += 1;
                            MainStruct[a].draw += 1;
                        }
                    }
                }
            }
        }
    }
}

int main(){
    /*ReadFromSettings(AddressOfNumberOfTeams);
    Team team[NumberOfTeams];
    BuildTeams(NumberOfTeams , team);*/
    Team* adres = malloc(sizeof(Team)* 4000);
    (adres + (sizeof(Team)*40))->points = 10;
    printf("a");
    return 0;
}