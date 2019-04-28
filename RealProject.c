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
    int average;
    int points;
}Team;

int NumberOfTeams;                                                  //Takim sayisini tutan degisken
int* AddressOfNumberOfTeams = &NumberOfTeams;                       //Takim sayisinin pointeri
Team* AdressToStartOfTeams;

void CopyString(char from[] , char to[]){
    uint i = 0;
    for(;from[i] != '\0';i++){
        to[i] = from[i];
    }
    to[i] = '\0';
}

void AllocateMemory(int TeamCount){
    AdressToStartOfTeams = calloc(sizeof(Team) , TeamCount);
}

Team* MoveStruct(int shift){
    return (AdressToStartOfTeams + shift);
}

void ReadTeamNumberFromConsole(int* address){                                //Takim sayisi verisini almaak icin ornek fonksiyon
    printf("Kac tane takim olacak?");
    scanf("%d",address);
}

void ReadMatchFromKeyboard(){
    printf("Maclari tek tek girin cikmak icin N yazin.");
    char HomeTeam;
    int HomeTeamScore;
    char GuestTeam;
    int GuestTeamScore;
    while(1){
        scanf("%c",HomeTeam);
        if(HomeTeam == 'N'){
            break;
        }
        scanf("%d %c %d", &HomeTeamScore , &GuestTeam , &GuestTeamScore);
        for(int i = 0;i <= NumberOfTeams; i++){

            if(HomeTeam == MoveStruct(i)->sname){

                for(int a = 0; a <= NumberOfTeams; a++){

                    if(GuestTeam == MoveStruct(a)->sname){
                        MoveStruct(i)->pscore += HomeTeamScore;
                        MoveStruct(i)->nscore += GuestTeamScore;
                        MoveStruct(a)->pscore += GuestTeamScore;
                        MoveStruct(a)->nscore += HomeTeamScore;
                        MoveStruct(i)->average += HomeTeamScore - GuestTeamScore;
                        MoveStruct(a)->average += GuestTeamScore - HomeTeamScore;
                        if(HomeTeamScore > GuestTeamScore){
                            MoveStruct(i)->won += 1;
                            MoveStruct(a)->lost += 1;
                        }
                        if(HomeTeamScore < GuestTeamScore){
                            MoveStruct(a)->won += 1;
                            MoveStruct(i)->lost += 1;
                        }
                        if(HomeTeamScore == GuestTeamScore){
                            MoveStruct(i)->draw += 1;
                            MoveStruct(a)->draw += 1;
                        }
                    }
                }
            }
        }
    }
}

void BuildTeams(int TeamCount){
    for(struct {char i; int a;}  fV = {65 , 0};
                                fV.a < TeamCount;
                                fV.a++ , fV.i++){
        MoveStruct(fV.a)->sname = fV.i;
        MoveStruct(fV.a)->points = 0;
        MoveStruct(fV.a)->played = 0;
        MoveStruct(fV.a)->won = 0;
        MoveStruct(fV.a)->lost = 0;
        MoveStruct(fV.a)->draw = 0;
        MoveStruct(fV.a)->points = 0;
        MoveStruct(fV.a)->pscore = 0;
        MoveStruct(fV.a)->nscore = 0;
        MoveStruct(fV.a)->average = 0;
    }
}



int main(){
    
    return 0;
}
