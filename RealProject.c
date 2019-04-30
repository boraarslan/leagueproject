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
    char* mchart;
} Team;

int NumberOfTeams;                                      //Takim sayisini tutan degisken
int *AddressOfNumberOfTeams = &NumberOfTeams;           //Takim sayisinin pointeri
Team *AdressToStartOfTeams;
int* PointArray;
int PointsForWin = 3;
int PointsForLose = -1;
int PointsForDraw = 1;
void CopyString(char from[], char to[]){
    uint i = 0;
    for (; from[i] != '\0'; i++){
        to[i] = from[i];
    }
    to[i] = '\0';
}

Team *MoveStruct(int shift){
    return (AdressToStartOfTeams + shift);
}

void AllocateMemory(int TeamCount){
    AdressToStartOfTeams = calloc(sizeof(Team), TeamCount);
    for (int i = 0; i <= TeamCount; i++){
        MoveStruct(i)->mchart = (char *)calloc(sizeof(char), TeamCount);
    }
    PointArray = calloc(sizeof(int) , TeamCount);
}

void ReadTeamNumberFromConsole(int *address){                       //Takim sayisi verisini almaak icin ornek fonksiyon
    printf("Kac tane takim olacak?");
    scanf("%d", address);
}

void ReadMatchFromKeyboard(){
    printf("Maclari tek tek girin cikmak icin ! yazin.");
    char HomeTeam = 0;
    int HomeTeamScore = 0;
    char GuestTeam = 0;
    int GuestTeamScore = 0;
    while (1){
        scanf("%c", &HomeTeam);
        if (HomeTeam == '!'){
            break;
        }

        scanf("%d %c %d", &HomeTeamScore, &GuestTeam, &GuestTeamScore);

        if (((int)(HomeTeam)-65) >= NumberOfTeams || ((int)(GuestTeam)-65) >= NumberOfTeams){
            printf("Lutfen gecerli takim adi girin.\n");
            HomeTeam = 0;
            GuestTeam = 0;
            continue;
        }

        for (int i = 0; i < NumberOfTeams; i++){

            if (HomeTeam == MoveStruct(i)->sname){                                  //Structlar icinden takimi buluyor

                for (int a = 0; a < NumberOfTeams; a++){

                    if (GuestTeam == MoveStruct(a)->sname){                         //Structlar icinden takimi buluyor

                        if (a == i){
                            printf("Ayni takim kendiyle mac yapamaz.\n");
                            break;
                        }

                        if (MoveStruct(i)->mchart[a] == '\0'){
                            printf("Bu ev sahibi takim bu deplasmandaki takimla zaten mac yapmis.\n");
                            break;
                        }

                        MoveStruct(i)->mchart[a] = '\0';

                        MoveStruct(i)->pscore += HomeTeamScore;                     //Kodun bu kisimi atilan ve
                        MoveStruct(i)->nscore += GuestTeamScore;                    //yenilen gollerin structlara
                        MoveStruct(a)->pscore += GuestTeamScore;                    //veri olarak girilmesini sagliyor
                        MoveStruct(a)->nscore += HomeTeamScore;
                        MoveStruct(i)->average += HomeTeamScore - GuestTeamScore;
                        MoveStruct(a)->average += GuestTeamScore - HomeTeamScore;

                        if (HomeTeamScore > GuestTeamScore){                        //Ev sahibi kazanirsa
                            MoveStruct(i)->won += 1;
                            MoveStruct(a)->lost += 1;
                            MoveStruct(i)->points += PointsForWin;
                            MoveStruct(a)->points += PointsForLose;
                        }

                        if (HomeTeamScore < GuestTeamScore){                        //Deplasman takimi kazanirsa
                            MoveStruct(a)->won += 1;
                            MoveStruct(i)->lost += 1;
                            MoveStruct(a)->points += PointsForWin;
                            MoveStruct(i)->points += PointsForLose;
                        }

                        if (HomeTeamScore == GuestTeamScore){                       //Berabere kalinirsa
                            MoveStruct(i)->draw += 1;
                            MoveStruct(a)->draw += 1;
                            MoveStruct(i)->points += PointsForDraw;
                            MoveStruct(a)->points += PointsForDraw;
                        }
                    }
                }
            }
        }
    }
}

void BuildTeams(int TeamCount){
    for (struct{char i; int a; } fV ={65, 0};
                                fV.a < TeamCount;
                                fV.a++, fV.i++){
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
        for (int i = 0; i <= TeamCount; i++){
            MoveStruct(fV.a)->mchart[i] = 65 + i;
        }
        MoveStruct(fV.a)->mchart[fV.a] = '\0';
    }
    for(int i = 0; i < NumberOfTeams; i++){
        PointArray[i] = i;
    }
    
}

void SortTeamsByPoint(){
    for(int i = 0; i < NumberOfTeams; i++){
        for(int a = i; a > 0 ; a--){
            int temp;
            if(MoveStruct(PointArray[a])->points > MoveStruct(PointArray[a-1])->points){
                temp = PointArray[a-1];
                PointArray[a-1] = PointArray[a];
                PointArray[a] = temp;
            }
        }
    }
}

void PrintTableByPoint(){
    for(int i = 0; i < NumberOfTeams; i++){
        printf("%c: %d\n", MoveStruct(PointArray[i])->sname , MoveStruct(PointArray[i])->points);
    }
}

int main(){
    ReadTeamNumberFromConsole(AddressOfNumberOfTeams);
    AllocateMemory(NumberOfTeams);
    BuildTeams(NumberOfTeams);
    for (int i = 0; i < NumberOfTeams; i++){
        for (int a = 0; a < NumberOfTeams; a++){
            printf("%c ", MoveStruct(i)->mchart[a]);
        }
        printf("\n");
    }
    ReadMatchFromKeyboard();
    for (int i = 0; i < NumberOfTeams; i++){
        for (int a = 0; a < NumberOfTeams; a++){
            printf("%c ", MoveStruct(i)->mchart[a]);
        }
        printf("\n");
    }
    SortTeamsByPoint();
    PrintTableByPoint();
    return 0;
}
