#include <stdio.h>
#include <stdlib.h>

typedef unsigned int uint;

typedef struct teams{
    char lname[13];
    char sname;
    uint played;
    uint won;
    uint lost;
    uint draw;
    uint pscore;
    uint nscore;
    int difference;
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
                        MoveStruct(i)->difference += HomeTeamScore - GuestTeamScore;
                        MoveStruct(a)->difference += GuestTeamScore - HomeTeamScore;
                        MoveStruct(i)->played += 1;
                        MoveStruct(a)->played += 1;

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

void ReadMatchesFromFile(){
    FILE* fp = fopen("maclar.txt", "r");
    char HomeTeam = 0;
    int HomeTeamScore = 0;
    char GuestTeam = 0;
    int GuestTeamScore = 0;
    int checkVariable = 0;
    while (1){
        checkVariable += 1;
        if(fscanf(fp , "%c %d %c %d",&HomeTeam, &HomeTeamScore, &GuestTeam, &GuestTeamScore) == EOF){
            break;
        }

        if (((int)(HomeTeam)-65) >= NumberOfTeams || ((int)(GuestTeam)-65) >= NumberOfTeams){
            printf("%d'inci satirdaki mac gecersiz.\n", checkVariable);
            HomeTeam = 0;
            GuestTeam = 0;
            continue;
        }

        for (int i = 0; i < NumberOfTeams; i++){

            if (HomeTeam == MoveStruct(i)->sname){                                  //Structlar icinden takimi buluyor

                for (int a = 0; a < NumberOfTeams; a++){

                    if (GuestTeam == MoveStruct(a)->sname){                         //Structlar icinden takimi buluyor

                        if (a == i){
                            printf("%d'inci satirda hata: Ayni takim kendiyle mac yapamaz.\n" , checkVariable);
                            break;
                        }

                        if (MoveStruct(i)->mchart[a] == '\0'){
                            printf("%d'inci satirda hata: Bu ev sahibi takim bu deplasmandaki takimla zaten mac yapmis.\n" , checkVariable);
                            break;
                        }

                        MoveStruct(i)->mchart[a] = '\0';

                        MoveStruct(i)->pscore += HomeTeamScore;                     //Kodun bu kisimi atilan ve
                        MoveStruct(i)->nscore += GuestTeamScore;                    //yenilen gollerin structlara
                        MoveStruct(a)->pscore += GuestTeamScore;                    //veri olarak girilmesini sagliyor
                        MoveStruct(a)->nscore += HomeTeamScore;
                        MoveStruct(i)->difference += HomeTeamScore - GuestTeamScore;
                        MoveStruct(a)->difference += GuestTeamScore - HomeTeamScore;
                        MoveStruct(i)->played += 1;
                        MoveStruct(a)->played += 1;

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
        MoveStruct(fV.a)->difference = 0;
        for (int i = 0; i <= TeamCount; i++){
            MoveStruct(fV.a)->mchart[i] = 65 + i;
        }
        MoveStruct(fV.a)->mchart[fV.a] = '\0';
    }
    for(int i = 0; i < NumberOfTeams; i++){
        PointArray[i] = i;
    }
}
void AlphabeticOrder(int integer, int start){
    if(MoveStruct(PointArray[integer])->lname[start] == '\0'){
        int temp = PointArray[integer-1];
        PointArray[integer-1] = PointArray[integer];
        PointArray[integer] = temp;
        return;
    }
    if(MoveStruct(PointArray[integer - 1])->lname[start] == '\0'){
        return;
    }
    if((int)(MoveStruct(PointArray[integer])->lname[start]) < (int)(MoveStruct(PointArray[integer - 1])->lname[start])){
        int temp = PointArray[integer-1];
        PointArray[integer-1] = PointArray[integer];
        PointArray[integer] = temp;
    }
    if((int)(MoveStruct(PointArray[integer])->lname[start]) == (int)(MoveStruct(PointArray[integer - 1])->lname[start])){
        AlphabeticOrder(integer , start+1);
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
            if(MoveStruct(PointArray[a])->points == MoveStruct(PointArray[a-1])->points){
                if(MoveStruct(PointArray[a])->difference > MoveStruct(PointArray[a-1])->difference){
                    temp = PointArray[a-1];
                    PointArray[a-1] = PointArray[a];
                    PointArray[a] = temp;
                }
                if(MoveStruct(PointArray[a])->difference == MoveStruct(PointArray[a-1])->difference){
                    AlphabeticOrder(a , 0);
                }
            }
        }
    }
}

void ConstructTable(){
    printf("%-5s",  "SH");
    printf("%-30s", "TEAM NAME");
    printf("%-5s",  "P");
    printf("%-5s",  "W");
    printf("%-5s",  "L");
    printf("%-5s",  "D");
    printf("%-5s",  "POS");
    printf("%-5s",  "NEG");
    printf("%-5s",  "DIFF");
    printf("%-5s",  "PTS");
    printf("\n");
}

void DestructTable(){
    printf("%s", "SH = Short Name, ");
    printf("%s", "P = Played, ");
    printf("%s", "W = Games Won, ");
    printf("%s", "L = Games Lost, ");
    printf("%s", "D = Draw, ");
    printf("%s", "POS = Positive Score, ");
    printf("%s", "NEG = Negative Score, ");
    printf("%s", "DIFF = Difference, \n");
}

void PrintTableByPoint(){
    ConstructTable();

    for(int i = 0; i < NumberOfTeams; i++){
        printf("%-5c",  MoveStruct(PointArray[i])->sname);
        printf("%-30s", MoveStruct(PointArray[i])->lname);
        printf("%-5d",  MoveStruct(PointArray[i])->played);
        printf("%-5d",  MoveStruct(PointArray[i])->won);
        printf("%-5d",  MoveStruct(PointArray[i])->lost);
        printf("%-5d",  MoveStruct(PointArray[i])->draw);
        printf("%-5d",  MoveStruct(PointArray[i])->pscore);
        printf("%-5d",  MoveStruct(PointArray[i])->nscore);
        printf("%-5d",  MoveStruct(PointArray[i])->difference);
        printf("%-5d\n",MoveStruct(PointArray[i])->points);
    }

    DestructTable();
}

void PrintTableByAlias(){
    ConstructTable();

    for(int i = 0; i < NumberOfTeams; i++){
        printf("%-5c",  MoveStruct(i)->sname);
        printf("%-30s", MoveStruct(i)->lname);
        printf("%-5d",  MoveStruct(i)->played);
        printf("%-5d",  MoveStruct(i)->won);
        printf("%-5d",  MoveStruct(i)->lost);
        printf("%-5d",  MoveStruct(i)->draw);
        printf("%-5d",  MoveStruct(i)->pscore);
        printf("%-5d",  MoveStruct(i)->nscore);
        printf("%-5d",  MoveStruct(i)->difference);
        printf("%-5d\n",MoveStruct(i)->points);
    }

    DestructTable();
}

void GetTeamLongName(){
    FILE* fp = fopen("takimlar.txt" , "r+");
    for(int i = 0; i < NumberOfTeams; i++){
        char array[59];
        fscanf(fp, "%s" , array);
        for(int a = 0; a < 13; a++){
            MoveStruct(i)->lname[a] = array[a];
        }
        MoveStruct(i)->lname[12] = '\0';
    }
}

int main(){
    ReadTeamNumberFromConsole(AddressOfNumberOfTeams);
    AllocateMemory(NumberOfTeams);
    BuildTeams(NumberOfTeams);
    GetTeamLongName();
    PrintTableByAlias();
    ReadMatchesFromFile();
    SortTeamsByPoint();
    PrintTableByPoint();
    return 0;
}
